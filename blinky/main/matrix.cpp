//
// matrix
//
// displays animations on the 9x16 matrix.
//
static const char *TAG = "matrix";

extern "C"
{
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "driver/i2c.h"
}
#include <cstring>

#include "pins.h"
#include "matrix.h"
#include "animations.h"

namespace matrix
{

    esp_err_t i2c_setup()
    {
        int i2c_master_port = 0;

        i2c_config_t conf;

        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = PIN_SDA;
        conf.scl_io_num = PIN_SCL;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = 400000;
        conf.clk_flags = 0;

        i2c_param_config(i2c_master_port, &conf);

        return i2c_driver_install(i2c_master_port, conf.mode, 0, 0, 0);
    }

    void setup()
    {
        ESP_LOGI(TAG, "Setting up matrix");

        // TODO set up the power enable pin and make sure it stays in "on" mode
        // whatever that is, and survives deep sleep

        ESP_ERROR_CHECK(i2c_setup());
        ESP_LOGI(TAG, "i2c initialized correctly");
    }

    // i2c_master_write_to_device is not yet a part of the i2c API, but
    // it is on the esp32 master branch, so we'll go ahead and use it
    // as it is a lot better than doing everything manually.

    esp_err_t i2c_master_write_to_device(i2c_port_t i2c_num, uint8_t device_address,
                                         const uint8_t *write_buffer, size_t write_size,
                                         TickType_t ticks_to_wait)
    {
        esp_err_t err = ESP_OK;

        i2c_cmd_handle_t handle = i2c_cmd_link_create();
        assert(handle != NULL);

        err = i2c_master_start(handle);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "err %d", err);
            goto end;
        }

        err = i2c_master_write_byte(handle, device_address << 1 | I2C_MASTER_WRITE, true);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "err %d", err);
            goto end;
        }

        err = i2c_master_write(handle, write_buffer, write_size, true);
        if (err != ESP_OK)
        {
            ESP_LOGE(TAG, "err %d", err);
            goto end;
        }

        i2c_master_stop(handle);
        err = i2c_master_cmd_begin(i2c_num, handle, ticks_to_wait);

    end:
        i2c_cmd_link_delete(handle);
        return err;
    }

    void charlieplex_write_buf(uint8_t *buf, size_t cb)
    {
        i2c_master_write_to_device(0, I2C_ADDR_CHARLIEPLEXER, buf, cb, pdMS_TO_TICKS(500));
    }

    void charlieplex_select_bank(uint8_t bank)
    {
        uint8_t cmd[2] = {ISSI_COMMANDREGISTER, bank};
        charlieplex_write_buf(cmd, 2);
    }

    void charlieplex_write_register_byte(uint8_t bank,
                                         uint8_t reg,
                                         uint8_t data)
    {
        charlieplex_select_bank(bank);
        uint8_t cmd[2] = {reg, data};
        charlieplex_write_buf(cmd, 2);
    }

    void charlieplex_write_register_144(uint8_t bank,
                                        uint8_t reg,
                                        const uint8_t *data)
    {
        charlieplex_select_bank(bank);

        uint8_t cmd[145];
        cmd[0] = reg;
        memcpy((&cmd[1]), data, 144);
        charlieplex_write_buf(cmd, 145);
    }

    void charlieplex_set_led_pwm_144(uint8_t *pwm, uint8_t bank)
    {
        charlieplex_write_register_144(bank, 0x24, pwm);
    }

    void displayAnimation(uint16_t animationNumber)
    {

        charlieplex_write_register_byte(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 0);
        charlieplex_write_register_byte(ISSI_BANK_FUNCTIONREG, ISSI_REG_AUDIOSYNC, 0); // not doing audio sync ever

        const uint8_t cFrames = animations::getAnimationFrameCount(animationNumber);
        uint16_t delay = animations::getAnimationDelayMs(animationNumber);

        if (delay < 11)
            delay = 11;
        if (delay > 693)
            delay = 0;

        uint8_t matrix[144];
        for (uint8_t framenum = 0; framenum < cFrames; framenum++)
        {
            animations::getAnimationFrame(animationNumber, framenum, matrix);
            charlieplex_set_led_pwm_144(matrix, framenum);
        }

        charlieplex_write_register_byte(ISSI_BANK_FUNCTIONREG,
                                        ISSI_REG_AUTOPLAY_WAY_OF_DISPLAY,
                                        cFrames & 7); // datasheet page 12 table 10)
        charlieplex_write_register_byte(ISSI_BANK_FUNCTIONREG,
                                        ISSI_REG_AUTOPLAY_DELAY_TIME,
                                        delay / 11);
        charlieplex_write_register_byte(ISSI_BANK_FUNCTIONREG,
                                        ISSI_REG_CONFIG,
                                        ISSI_REG_CONFIG_AUTOPLAYMODE);

        // Turn the matrix back on
        charlieplex_write_register_byte(ISSI_BANK_FUNCTIONREG, ISSI_REG_SHUTDOWN, 1);
    }
}
