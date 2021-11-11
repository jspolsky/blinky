#include <Arduino.h>

#include "inventory.h"

namespace Inventory
{
    uint16_t myAnimation = 0; // UNDONE no
    uint16_t currentAnimation = 0;

    void setup()
    {
        currentAnimation = myAnimation;
    }

    uint16_t getMyAnimation() { return myAnimation; }
    uint16_t getCurrentAnimation() { return currentAnimation; }
    uint16_t nextAnimation()
    {
        currentAnimation = (currentAnimation + 1) % 26;
        return currentAnimation;
    }
    void addToInventory(uint16_t) {}
}