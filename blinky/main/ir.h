#pragma once

namespace ir
{
    void transmit(uint32_t addr, uint32_t cmd);
    void receive();

    void exchange_protocol(uint16_t myAnimation);
}