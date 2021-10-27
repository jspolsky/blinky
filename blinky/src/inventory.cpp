#include <Arduino.h>

#include "inventory.h"

namespace Inventory
{
    uint16_t currentAnimation = 0;

    void setup()
    {
        currentAnimation = getMyAnimation();
    }

    uint16_t getMyAnimation() { return 0; }
    uint16_t getCurrentAnimation() { return currentAnimation; }
    uint16_t getNextAnimation() { return 0; }
    void addToInventory(uint16_t) {}
}