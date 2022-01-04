#pragma once

namespace ir
{
    void setup();
    void transmit(void *arg);
    void receive(void *arg);

    void exchange_protocol(uint16_t myAnimation);
}