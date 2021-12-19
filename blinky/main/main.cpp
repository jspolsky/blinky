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

void setup()
{
    rgbled::setup();
}

extern "C" void app_main(void)
{
    setup();

    // Show simple rainbow chasing pattern
    ESP_LOGI(TAG, "LED Rainbow Chase Start");
    rgbled::show_rainbow();

    esp_deep_sleep_enable_gpio_wakeup(BIT(GPIO_NUM_2), ESP_GPIO_WAKEUP_GPIO_HIGH);
    esp_deep_sleep_start();
}
