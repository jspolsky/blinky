//
// rgbled
//
// simple utilities to use the RGB LED on a development board for debugging
// ... not really used in production Blinky, because it doesn't have one
static const char *TAG = "rgbled";

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "led_strip.h"
}

#include "rgbled.h"

#define RMT_TX_CHANNEL RMT_CHANNEL_0
#define EXAMPLE_CHASE_SPEED_MS (60)

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

namespace rgbled
{
    static led_strip_t *strip;

    void setup()
    {
        rmt_config_t config = LOCAL_RMT_DEFAULT_CONFIG_TX((gpio_num_t)CONFIG_EXAMPLE_RMT_TX_GPIO, RMT_TX_CHANNEL);

        // set counter clock to 40MHz
        config.clk_div = 2;

        ESP_ERROR_CHECK(rmt_config(&config));
        ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

        // install ws2812 driver
        led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(CONFIG_EXAMPLE_STRIP_LED_NUMBER, (led_strip_dev_t)config.channel);
        strip = led_strip_new_rmt_ws2812(&strip_config);

        if (!strip)
        {
            ESP_LOGE(TAG, "install WS2812 driver failed");
        }
    }

    void show_rainbow()
    {
        for (int i = 0; i < 360; i += 20)
        {
            show_color(i);
            vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
        }

        strip->set_pixel(strip, 0, 0, 0, 0);
        strip->refresh(strip, 100);
    }

    void show_color(uint16_t hue)
    {

        uint32_t red = 0;
        uint32_t green = 0;
        uint32_t blue = 0;
        led_strip_hsv2rgb(hue, 100, 25, &red, &green, &blue);
        // Write RGB values to strip driver
        ESP_ERROR_CHECK(strip->set_pixel(strip, 0, red, green, blue));
        ESP_ERROR_CHECK(strip->refresh(strip, 100));
    }

    void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b)
    {
        h %= 360; // h -> [0,360]
        uint32_t rgb_max = v * 2.55f;
        uint32_t rgb_min = rgb_max * (100 - s) / 100.0f;

        uint32_t i = h / 60;
        uint32_t diff = h % 60;

        // RGB adjustment amount by hue
        uint32_t rgb_adj = (rgb_max - rgb_min) * diff / 60;

        switch (i)
        {
        case 0:
            *r = rgb_max;
            *g = rgb_min + rgb_adj;
            *b = rgb_min;
            break;
        case 1:
            *r = rgb_max - rgb_adj;
            *g = rgb_max;
            *b = rgb_min;
            break;
        case 2:
            *r = rgb_min;
            *g = rgb_max;
            *b = rgb_min + rgb_adj;
            break;
        case 3:
            *r = rgb_min;
            *g = rgb_max - rgb_adj;
            *b = rgb_max;
            break;
        case 4:
            *r = rgb_min + rgb_adj;
            *g = rgb_min;
            *b = rgb_max;
            break;
        default:
            *r = rgb_max;
            *g = rgb_min;
            *b = rgb_max - rgb_adj;
            break;
        }
    }
}