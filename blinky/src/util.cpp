#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#include "util.h"

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);

namespace Util
{
    void setup()
    {
        pixels.begin();
    }

    void setColorRGB(uint8_t red, uint8_t green, uint8_t blue)
    {
        pixels.setPixelColor(0, pixels.Color(red, green, blue));
        pixels.show();
    }

    void setColorHSV(uint8_t hue, uint8_t saturation, uint8_t brightness)
    {
        pixels.setPixelColor(0, pixels.ColorHSV(hue << 8, saturation, brightness));
        pixels.show();
    }

}