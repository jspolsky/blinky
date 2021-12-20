#pragma once

namespace matrix
{
    void setup();
    void displayAnimation();

    const uint8_t ISSI_COMMANDREGISTER = 0xFD;
    const uint8_t ISSI_BANK_FUNCTIONREG = 0x0B;
    const uint8_t ISSI_REG_SHUTDOWN = 0x0A;
    const uint8_t ISSI_REG_CONFIG = 0x00;
    const uint8_t ISSI_REG_CONFIG_PICTUREMODE = 0x00;
    const uint8_t ISSI_REG_PICTUREFRAME = 0x01;
    const uint8_t ISSI_REG_AUDIOSYNC = 0x06;
}
