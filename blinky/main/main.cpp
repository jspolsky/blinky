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
}

#include "rgbled.h"
#include "pins.h"
#include "button.h"
#include "matrix.h"
#include "ir.h"

void ShortPress(void);
void LongPressStart(void);
void LongPressEnd(void);

extern "C" void app_main(void)
{
    matrix::setup();

    switch (esp_sleep_get_wakeup_cause())
    {
    case ESP_SLEEP_WAKEUP_GPIO:
        button::wakeup(ShortPress, LongPressStart, LongPressEnd);
        break;

    default: /* initial power up */

        // TODO remove rgbled in final product
        rgbled::setup();
        rgbled::show_rainbow();

        // show the first animation
        matrix::displayAnimation(1);

        ir::ir_transmit(0xCFFE, 0x13);
        ir::ir_receive();

        break;
    }

    esp_deep_sleep_enable_gpio_wakeup(BIT(PIN_BUTTON), ESP_GPIO_WAKEUP_GPIO_HIGH);
    esp_deep_sleep_start();
}

void ShortPress()
{
    ESP_LOGI(TAG, "Short Press");
}

void LongPressStart()
{
    ESP_LOGI(TAG, "Long Press Start");
}

void LongPressEnd()
{
    ESP_LOGI(TAG, "Long Press End");
}
