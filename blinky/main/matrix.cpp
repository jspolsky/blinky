//
// matrix
//
// displays animations on the 9x16 matrix.
//
static const char *TAG = "matrix";

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
}

#include "matrix.h"

namespace matrix
{
    void setup()
    {
        ESP_LOGI(TAG, "Setting up matrix");

        // TODO set up the power enable pin and make sure it stays in "on" mode
        // whatever that is, and survives deep sleep

        // TODO configure i2c (i2c_param_config)
        // TODO install i2c driver (i2c_driver_install)

        // TODO all of the things from Adafruit_IS31FL3731::begin, including
        // clear()
    }

    void displayAnimation()
    {
        // TODO this is basically the code from old matrix.cpp::displayAnimation

        ESP_LOGI(TAG, "Display initial animation");

        // TODO get animation pixels, number of frames, and speed

        // TODO load all the frames

        // TODO start autoplay
    }
}