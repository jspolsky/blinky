#include <Arduino.h>
#include <FlashStorage.h>

#include "inventory.h"
#include "matrix.h"
#include "pins.h"
#include "util.h"

#define MAX_ANIMATION 512 /* animations that can be stored in inventory are 0-511 */

namespace Inventory
{
    // Data type to be stored in flash with non-volatile everything:
    struct inventory_t
    {
        char header[2];                           // "OK" if data is here. Will be zeros if flash has been erased
        uint16_t myAnimation;                     // The personal animation associated with this blinky.
        uint8_t rgbitUnlocked[MAX_ANIMATION / 8]; // Packed bits indicating which animations (up to 512) are unlocked by this blinky
    };

    FlashStorage(flash_inventory, inventory_t);

    uint16_t myAnimation = 0;
    uint16_t currentAnimation = 0;
    inventory_t inventory;

    void setup()
    {
        pinMode(RESET_INVENTORY_PIN, INPUT_PULLUP);
        delay(10);
        bool bResetInventory = (digitalRead(RESET_INVENTORY_PIN) == LOW);

        if (!bResetInventory)
        {
            inventory = flash_inventory.read();
            if (inventory.header[0] == 'O' && inventory.header[1] == 'K')
            {
                myAnimation = inventory.myAnimation;
            }
            else
            {
                bResetInventory = true;
            }
        }

        if (bResetInventory)
        {
            Matrix::testPattern();

            memset(&inventory, 0, sizeof(inventory));

            // Oh hai. First time waking up after a flash.
            // We need to pick a random animation to be OUR animation.
            //
            pinMode(A6, INPUT);
            randomSeed(analogRead(RANDOM_NOISE_PIN)); // this pin is floating so it generates just
                                                      // enough noise to be different every time
            myAnimation = inventory.myAnimation = random(Matrix::getAnimationCount());
            inventory.header[0] = 'O';
            inventory.header[1] = 'K';

            addToInventory(myAnimation);

            flash_inventory.write(inventory);
        }
        currentAnimation = myAnimation;
    }

    uint16_t getMyAnimation() { return myAnimation; }
    uint16_t getCurrentAnimation() { return currentAnimation; }

    bool isAnimationInInventory(uint16_t animation)
    {
        return (animation < Matrix::getAnimationCount()) &&
               !!(inventory.rgbitUnlocked[animation / 8] & (1 << (animation % 8)));
    }

    uint16_t nextAnimation()
    {
        uint16_t animation = (currentAnimation + 1) % Matrix::getAnimationCount();
        while (animation != currentAnimation)
        {
            if (isAnimationInInventory(animation))
            {
                break;
            }
            animation = ((animation + 1) % Matrix::getAnimationCount());
        }

        currentAnimation = animation;
        return (currentAnimation);
    }

    void addToInventory(uint16_t animation)
    {
        if (animation < Matrix::getAnimationCount())
        {
            inventory.rgbitUnlocked[animation / 8] |= (1 << (animation % 8));
            flash_inventory.write(inventory);
            currentAnimation = animation;
        }
    }
}
