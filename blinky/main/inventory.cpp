//
// inventory
//
// Keep track of which animations we have
//

[[maybe_unused]] static const char *TAG = "inventory";

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"
}
#include <cstring>

#include "inventory.h"
#include "animations.h"

#define MAX_ANIMATION 512 /* animations that can be stored in inventory are 0-511 */

namespace inventory
{
    // Data type to be stored in flash with non-volatile everything:
    struct inventory_t
    {
        uint16_t myAnimation;                     // The personal animation associated with this blinky.
        uint8_t rgbitUnlocked[MAX_ANIMATION / 8]; // Packed bits indicating which animations (up to 512) are unlocked by this blinky
    };

    RTC_DATA_ATTR uint16_t myAnimation = 0;
    RTC_DATA_ATTR uint16_t currentAnimation = 0;
    RTC_DATA_ATTR inventory_t inventory;

    const char NVS_NAMESPACE[] = "blinky";
    const char NVS_KEY[] = "inventory";

    void setup()
    {
        memset(&inventory, 0, sizeof(inventory));

        esp_err_t err = nvs_flash_init();
        if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            ESP_LOGI(TAG, "no NVS yet");

            // NVS partition was truncated and needs to be erased
            // Retry nvs_flash_init
            ESP_ERROR_CHECK(nvs_flash_erase());
            err = nvs_flash_init();
        }
        ESP_ERROR_CHECK(err);

        nvs_handle_t hnvs;
        ESP_ERROR_CHECK(nvs_open(NVS_NAMESPACE, NVS_READWRITE, &hnvs));

        size_t cb = 0;
        err = nvs_get_blob(hnvs, NVS_KEY, NULL, &cb);

        if (err == ESP_ERR_NVS_NOT_FOUND)
        {
            ESP_LOGI(TAG, "Nothing stored yet.");

            // first time waking up after a flash. Pick a random animation
            // to be our animation.
            currentAnimation = inventory.myAnimation = esp_random() % (animations::getAnimationCount() - 1) + 1;
            inventory.rgbitUnlocked[currentAnimation / 8] |= (1 << (currentAnimation % 8));

            ESP_LOGI(TAG, "My animation will be %d (there are %d animations on the system excluding #0)",
                     inventory.myAnimation,
                     animations::getAnimationCount() - 1);

            cb = sizeof(inventory);
            ESP_ERROR_CHECK(nvs_set_blob(hnvs, NVS_KEY, &inventory, cb));
            ESP_ERROR_CHECK(nvs_commit(hnvs));
        }
        else if (err == ESP_OK)
        {

            if (cb == sizeof(inventory))
            {
                ESP_ERROR_CHECK(nvs_get_blob(hnvs, NVS_KEY, &inventory, &cb));
                currentAnimation = inventory.myAnimation;
                ESP_LOGI(TAG, "Inventory found, my animation is %d", currentAnimation);
            }
            else
            {
                ESP_LOGE(TAG, "Wrong size blob?");
            }
        }
        else
        {
            ESP_LOGE(TAG, "error in nvs_get_blob %d", err);
        }

        nvs_close(hnvs);
    }

    uint16_t getMyAnimation() { return myAnimation; }
    uint16_t getCurrentAnimation() { return currentAnimation; }

    bool isAnimationInInventory(uint16_t animation)
    {
        return (animation < MAX_ANIMATION) &&
               !!(inventory.rgbitUnlocked[animation / 8] & (1 << (animation % 8)));
    }

    uint16_t nextAnimation()
    {
        uint16_t animation = (currentAnimation + 1) % MAX_ANIMATION;
        while (animation != currentAnimation)
        {
            if (isAnimationInInventory(animation))
            {
                break;
            }
            animation = ((animation + 1) % MAX_ANIMATION);
        }

        currentAnimation = animation;
        ESP_LOGI(TAG, "Next animation is %d", currentAnimation);
        return (currentAnimation);
    }

    void addToInventory(uint16_t animation)
    {
        if (animation < MAX_ANIMATION)
        {
            inventory.rgbitUnlocked[animation / 8] |= (1 << (animation % 8));
            currentAnimation = animation;

            nvs_handle_t hnvs;
            ESP_ERROR_CHECK(nvs_open(NVS_NAMESPACE, NVS_READWRITE, &hnvs));
            size_t cb = sizeof(inventory);
            ESP_ERROR_CHECK(nvs_set_blob(hnvs, NVS_KEY, &inventory, cb));
            ESP_ERROR_CHECK(nvs_commit(hnvs));
            nvs_close(hnvs);
        }
    }

}
