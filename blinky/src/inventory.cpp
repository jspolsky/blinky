#include <Arduino.h>
#include <FlashStorage.h>

#include "inventory.h"

namespace Inventory
{
    // Data type to be stored in flash with non-volatile everything:
    struct inventory_t
    {
        char header[2];            // "OK" if data is here. Will be zeros if flash has been erased
        uint16_t myAnimation;      // The personal animation associated with this blinky.
        uint8_t rgbitUnlocked[64]; // Packed bits indicating which animations (up to 512) are unlocked by this blinky
    };

    FlashStorage(flash_inventory, inventory_t);

    uint16_t myAnimation = 0;
    uint16_t currentAnimation = 0;

    void setup()
    {
        inventory_t inventory = flash_inventory.read();
        myAnimation = inventory.myAnimation++;
        flash_inventory.write(inventory);

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