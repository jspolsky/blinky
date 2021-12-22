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
}

#include "pins.h"
#include "ir.h"

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

namespace ir
{
    static rmt_channel_t example_tx_channel = RMT_CHANNEL_1;
    // static rmt_channel_t example_rx_channel = RMT_CHANNEL_2;

    void example_ir_tx_task(uint32_t addr, uint32_t cmd)
    {

        rmt_item32_t *items = NULL;
        size_t length = 0;
        ir_builder_t *ir_builder = NULL;

        rmt_config_t rmt_tx_config = LOCAL_RMT_DEFAULT_CONFIG_TX(PIN_IR_TX, example_tx_channel);
        rmt_tx_config.tx_config.carrier_en = true;
        rmt_config(&rmt_tx_config);
        rmt_driver_install(example_tx_channel, 0, 0);
        ir_builder_config_t ir_builder_config = IR_BUILDER_DEFAULT_CONFIG((ir_dev_t)example_tx_channel);
        ir_builder_config.flags |= IR_TOOLS_FLAGS_PROTO_EXT; // Using extended IR protocols (both NEC and RC5 have extended version)
        ir_builder = ir_builder_rmt_new_nec(&ir_builder_config);

        ESP_LOGI(TAG, "Send command 0x%x to address 0x%x", cmd, addr);
        // Send new key code
        ESP_ERROR_CHECK(ir_builder->build_frame(ir_builder, addr, cmd));
        ESP_ERROR_CHECK(ir_builder->get_result(ir_builder, &items, &length));
        //To send data according to the waveform items.
        rmt_write_items(example_tx_channel, items, length, 1);
        // Send repeat code

        ir_builder->del(ir_builder);
        rmt_driver_uninstall(example_tx_channel);
    }

}
