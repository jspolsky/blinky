//
// button
//
// logic for the button.
//
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
        uint64_t tmStart = esp_timer_get_time();
        bool fInLongPress = false;

        gpio_set_direction(PIN_BUTTON, gpio_mode_t(GPIO_MODE_DEF_INPUT));
        gpio_set_pull_mode(PIN_BUTTON, GPIO_PULLDOWN_ONLY);

        while (gpio_get_level(PIN_BUTTON))
        {
            if (!fInLongPress &&
                esp_timer_get_time() > (tmStart + pdMS_TO_TICKS(1000)))
            {
                ESP_LOGI(TAG, "Start Long Press");
                fInLongPress = true;
            }

            // this kinda helps reduce bounces:
            vTaskDelay(pdMS_TO_TICKS(100));
        }

        if (fInLongPress)
        {
            ESP_LOGI(TAG, "End Long Press");
        }
        else
        {
            ESP_LOGI(TAG, "Short Press");
            rgbled::setup();
            rgbled::show_rainbow();
        }
    }
}