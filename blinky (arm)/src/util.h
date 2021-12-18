#pragma once
#include <Arduino.h>

// Utility functions used by multiple modules

namespace Util
{

    void setup();

    void setColorRGB(uint8_t red, uint8_t green, uint8_t blue);
    void setColorHSV(uint8_t hue, uint8_t saturation = 0xFF, uint8_t brightness = 0xFF);

}