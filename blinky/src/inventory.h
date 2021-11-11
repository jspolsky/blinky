#pragma once
#include <Arduino.h>

// Track inventory of which animations this device has access to

namespace Inventory
{
    void setup();

    // returns the animation that permanently belongs
    // to this device
    uint16_t getMyAnimation();

    // returns the animation that is currently showing
    uint16_t getCurrentAnimation();

    // returns the next animation that we also own,
    // round-robin
    uint16_t nextAnimation();

    // receives an animation from a friend and adds
    // it to the inventory of animations we own
    void addToInventory(uint16_t);
}