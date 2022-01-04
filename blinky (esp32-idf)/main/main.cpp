//
// blinky
//
// a burning man 2022 project
//
static const char *TAG = "main";

extern "C"
{
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_sleep.h"
#include "nvs_flash.h"
#include "nvs.h"
}

#include "rgbled.h"
#include "pins.h"
#include "button.h"
#include "matrix.h"
#include "ir.h"
#include "inventory.h"

void ShortPress(void);
void LongPress(void);

RTC_DATA_ATTR bool fWasAsleep = false;

extern "C" void app_main(void)
{

    ir::setup();
    matrix::setup();

    esp_sleep_wakeup_cause_t wakeup_cause = esp_sleep_get_wakeup_cause();

    switch (wakeup_cause)
    {
    case ESP_SLEEP_WAKEUP_GPIO:
        button::wakeup(ShortPress, LongPress);
        break;

    case ESP_SLEEP_WAKEUP_TIMER:
        ESP_LOGI(TAG, "time up!");
        fWasAsleep = true;
        matrix::powerOff();
        break;

    default: /* initial power up */

        inventory::setup();

        // TODO remove rgbled in final product
        rgbled::setup();
        rgbled::show_rainbow();

        // show the first animation
        matrix::displayAnimation(inventory::getCurrentAnimation(), true);
        break;
    }

    if (wakeup_cause != ESP_SLEEP_WAKEUP_TIMER)
    {
        //  don't wake up more than once from timer
        esp_sleep_enable_timer_wakeup(2ULL * 60ULL * 60ULL * 1000ULL * 1000ULL);
    }

    esp_deep_sleep_enable_gpio_wakeup(BIT(PIN_BUTTON), ESP_GPIO_WAKEUP_GPIO_HIGH);
    esp_deep_sleep_start();
}

void ShortPress()
{
    ESP_LOGI(TAG, "Short Press");

    // short press on wakeup from sleep should not advance to the next
    // animation
    if (fWasAsleep)
    {
        fWasAsleep = false;
        matrix::displayAnimation(inventory::getCurrentAnimation());
    }
    else
    {
        matrix::displayAnimation(inventory::nextAnimation());
    }
}

void LongPress()
{
    ESP_LOGI(TAG, "Long Press Start");
    ir::exchange_protocol(inventory::getMyAnimation());
}
