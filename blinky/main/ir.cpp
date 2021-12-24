//
// ir
//
// send and receive IR remote control messages
//
[[maybe_unused]] static const char *TAG = "ir";

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "ir_tools.h"
#include "nvs_flash.h"
#include "nvs.h"
}

#include "pins.h"
#include "ir.h"
#include "button.h"
#include "inventory.h"
#include "matrix.h"

#define LOCAL_RMT_DEFAULT_CONFIG_TX(gpio, channel_id)          \
    {                                                          \
        .rmt_mode = RMT_MODE_TX,                               \
        .channel = channel_id,                                 \
        .gpio_num = gpio,                                      \
        .clk_div = 80,                                         \
        .mem_block_num = 1,                                    \
        .flags = 0,                                            \
        .tx_config = {.carrier_freq_hz = 38000,                \
                      .carrier_level = RMT_CARRIER_LEVEL_HIGH, \
                      .idle_level = RMT_IDLE_LEVEL_LOW,        \
                      .carrier_duty_percent = 33,              \
                      .loop_count = 0,                         \
                      .carrier_en = false,                     \
                      .loop_en = false,                        \
                      .idle_output_en = true,                  \
        }                                                      \
    }

#define LOCAL_RMT_DEFAULT_CONFIG_RX(gpio, channel_id)         \
    {                                                         \
        .rmt_mode = RMT_MODE_RX,                              \
        .channel = channel_id,                                \
        .gpio_num = gpio,                                     \
        .clk_div = 80,                                        \
        .mem_block_num = 1,                                   \
        .flags = 0,                                           \
        .rx_config = {.idle_threshold = 12000,                \
                      .filter_ticks_thresh = 100,             \
                      .filter_en = true,                      \
                      .rm_carrier = 0,                        \
                      .carrier_freq_hz = 0,                   \
                      .carrier_duty_percent = 0,              \
                      .carrier_level = (rmt_carrier_level_t)0 \
        }                                                     \
    }

namespace ir
{
    static rmt_channel_t tx_channel = RMT_CHANNEL_1;
    static rmt_channel_t rx_channel = RMT_CHANNEL_2;

    static uint16_t myAnimation;

    void transmit(void *arg)
    {
        uint16_t *pcmd = (uint16_t *)arg;

        uint32_t addr = NEC_ADDRESS_BLINKY;
        uint32_t cmd = (uint32_t)*pcmd;

        rmt_item32_t *items = NULL;
        size_t length = 0;
        ir_builder_t *ir_builder = NULL;

        rmt_config_t rmt_tx_config = LOCAL_RMT_DEFAULT_CONFIG_TX(PIN_IR_TX, tx_channel);
        rmt_tx_config.tx_config.carrier_en = true;
        rmt_config(&rmt_tx_config);
        rmt_driver_install(tx_channel, 0, 0);

        ir_builder_config_t ir_builder_config = IR_BUILDER_DEFAULT_CONFIG((ir_dev_t)tx_channel);
        ir_builder_config.flags |= IR_TOOLS_FLAGS_PROTO_EXT; // Using extended IR protocols (both NEC and RC5 have extended version)
        ir_builder = ir_builder_rmt_new_nec(&ir_builder_config);

        ESP_LOGI(TAG, "Send command 0x%x to address 0x%x", cmd, addr);
        // Send new key code
        ESP_ERROR_CHECK(ir_builder->build_frame(ir_builder, addr, cmd));
        ESP_ERROR_CHECK(ir_builder->get_result(ir_builder, &items, &length));

        while (1)
        {
            rmt_write_items(tx_channel, items, length, 1);

            // Wait a random amount of time to avoid collisions
            uint32_t msToWait = 100 + esp_random() % 500;
            vTaskDelay(pdMS_TO_TICKS(msToWait));
        }

        ir_builder->del(ir_builder);
        rmt_driver_uninstall(tx_channel);
        vTaskDelete(NULL);
    }

    void receive(void *arg)
    {
        uint16_t *pcmd = (uint16_t *)arg;

        uint32_t addr = 0;
        uint32_t cmd = 0;
        size_t length = 0;
        bool repeat = false;
        RingbufHandle_t rb = NULL;
        rmt_item32_t *items = NULL;

        rmt_config_t rmt_rx_config = LOCAL_RMT_DEFAULT_CONFIG_RX(PIN_IR_RX, rx_channel);
        rmt_config(&rmt_rx_config);
        rmt_driver_install(rx_channel, 1000, 0);
        ir_parser_config_t ir_parser_config = IR_PARSER_DEFAULT_CONFIG((ir_dev_t)rx_channel);
        //        ir_parser_config.flags |= IR_TOOLS_FLAGS_PROTO_EXT; // Using extended IR protocols (both NEC and RC5 have extended version)
        ir_parser_t *ir_parser = NULL;
        ir_parser = ir_parser_rmt_new_nec(&ir_parser_config);

        //get RMT RX ringbuffer
        rmt_get_ringbuf_handle(rx_channel, &rb);
        assert(rb != NULL);
        // Start receive
        rmt_rx_start(rx_channel, true);
        bool fReceived = false;
        while (!fReceived)
        {
            items = (rmt_item32_t *)xRingbufferReceive(rb, &length, portMAX_DELAY);
            if (items)
            {
                length /= 4; // one RMT = 4 Bytes
                if (ir_parser->input(ir_parser, items, length) == ESP_OK)
                {
                    if (ir_parser->get_scan_code(ir_parser, &addr, &cmd, &repeat) == ESP_OK)
                    {
                        // ignore my own animation -- I sent it myself
                        if (addr == NEC_ADDRESS_BLINKY && *pcmd != cmd && !fReceived)
                        {
                            ESP_LOGI(TAG, "Received animation %d", cmd);

                            ESP_ERROR_CHECK(nvs_flash_init());
                            matrix::displayAnimation(inventory::addToInventory(cmd));

                            fReceived = true;
                        }
                    }
                }
                //after parsing the data, return spaces to ringbuffer.
                vRingbufferReturnItem(rb, (void *)items);
            }
        }
        ir_parser->del(ir_parser);
        rmt_driver_uninstall(rx_channel);
        vTaskDelete(NULL);
    }

    // the exchange protocol consists of sending our animation to peer, then
    // listening for a random amount of time (100-600 ms) to see if they have
    // send us one
    //
    // it ends about five seconds after the button is released.
    //
    // don't bother listening if we already got their animation.
    // never run more than 15 seconds.
    //
    //
    void exchange_protocol(uint16_t _myAnimation)
    {
        ESP_LOGI(TAG, "Exchange protocol starting");
        uint64_t tmStart = esp_timer_get_time();
        uint64_t tmButtonUp = 0;

        myAnimation = _myAnimation; // can't be in the stack according to task rules

        xTaskCreate(receive, "ir_rx_task", 2048, &myAnimation, 10, NULL);
        xTaskCreate(transmit, "ir_tx_task", 2048, &myAnimation, 10, NULL);

        while (true)
        {
            if (tmStart + 15000000 < esp_timer_get_time())
            {
                ESP_LOGI(TAG, "Exchange protocol timeout");
                break;
            }

            if (tmButtonUp == 0 && !button::buttonDown())
            {
                ESP_LOGI(TAG, "Exchange protocol detected button came up");
                tmButtonUp = esp_timer_get_time();
            }

            if (tmButtonUp && tmButtonUp + 3000000 < esp_timer_get_time())
            {
                ESP_LOGI(TAG, "Button came up 3 seconds ago");
                break;
            }

            vTaskDelay(10);
        }

        ESP_LOGI(TAG, "Exchange protocol ending");

        // when this function we go into deep sleep again.
        // That will kill both tasks.
    }

}
