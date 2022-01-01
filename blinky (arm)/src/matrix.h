// LED Matrix Code
//
// Everything to do with the IL31FL3731 based charliplex
// array of 9x16 individual LEDs

#pragma once
#include <Adafruit_IS31FL3731.h>

#define EXCHANGE_ANIMATION 0xFFFF

namespace Matrix
{
    void setup();
    void displayAnimation(uint8_t cframes, uint16_t delay, uint8_t const *bitmap);
    void displayAnimation(uint16_t code);
    void power(bool bOn); // turn the matrix on and off
    size_t getAnimationCount(); // total number of animations (not including _exchange)
}