//
// button
//
// logic for the button.
//
// very short click - nothing. This is just to debounce.
// short click - switch animation (on button up)
// long click - start animation exchange.
//
static const char *TAG = "button";

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/rmt.h"
}

#include "pins.h"
#include "rgbled.h"
#include "button.h"

namespace button
{
    void wakeup()
    {
        gpio_set_direction(PIN_BUTTON, gpio_mode_t(GPIO_MODE_DEF_INPUT));
        gpio_set_pull_mode(PIN_BUTTON, GPIO_PULLDOWN_ONLY);

        ESP_LOGI(TAG, "Looking at the button");
        while (gpio_get_level(PIN_BUTTON))
        {
            ESP_LOGI(TAG, "Button is still down");
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        ESP_LOGI(TAG, "Button just went up!");

        ESP_LOGI(TAG, "LED Rainbow Chase Start");
        rgbled::setup();
        rgbled::show_rainbow();
    }
}