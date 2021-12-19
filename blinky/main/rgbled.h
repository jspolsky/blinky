#pragma once

namespace rgbled
{
    void setup();

    void show_rainbow();
    void show_color(uint16_t hue);
    void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b);
}