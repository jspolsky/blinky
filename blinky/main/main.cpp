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

extern "C" void app_main(void)
{
    matrix::setup();

    switch (esp_sleep_get_wakeup_cause())
    {
    case ESP_SLEEP_WAKEUP_GPIO:
        button::wakeup(ShortPress, LongPress);
        break;

    default: /* initial power up */

        inventory::setup();

        // TODO remove rgbled in final product
        rgbled::setup();
        rgbled::show_rainbow();

        // show the first animation
        matrix::displayAnimation(inventory::getCurrentAnimation());

        break;
    }

    esp_deep_sleep_enable_gpio_wakeup(BIT(PIN_BUTTON), ESP_GPIO_WAKEUP_GPIO_HIGH);
    esp_deep_sleep_start();
}

void ShortPress()
{
    ESP_LOGI(TAG, "Short Press");
    matrix::displayAnimation(inventory::nextAnimation());
}

void LongPress()
{
    ESP_LOGI(TAG, "Long Press Start");
    matrix::displayAnimation(0);
    ir::exchange_protocol(inventory::getMyAnimation());
    matrix::displayAnimation(inventory::getCurrentAnimation());
}
