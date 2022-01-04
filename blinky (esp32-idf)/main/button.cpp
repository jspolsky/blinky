//
// button
//
// logic for the button.
//
// short click - switch animation (on button up)
// long click - start animation exchange.
//

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/rmt.h"
}

#include "pins.h"
#include "button.h"

namespace button
{
    void wakeup(CALLBACK *fnShortPress, CALLBACK *fnLongPress)
    {
        uint64_t tmStart = esp_timer_get_time();
        bool fInLongPress = false;

        gpio_set_direction(PIN_BUTTON, gpio_mode_t(GPIO_MODE_DEF_INPUT));
        gpio_set_pull_mode(PIN_BUTTON, GPIO_PULLDOWN_ONLY);

        while (buttonDown())
        {
            if (!fInLongPress &&
                esp_timer_get_time() > (tmStart + pdMS_TO_TICKS(700)))
            {
                fnLongPress();
                fInLongPress = true;
            }

            // this kinda helps reduce bounces:
            vTaskDelay(pdMS_TO_TICKS(100));
        }

        if (!fInLongPress)
        {
            fnShortPress();
        }
    }

    bool buttonDown()
    {
        return gpio_get_level(PIN_BUTTON);
    }
}