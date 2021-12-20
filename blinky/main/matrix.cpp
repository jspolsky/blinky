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
    }

    void displayAnimation()
    {
        ESP_LOGI(TAG, "Display initial animation");
    }
}