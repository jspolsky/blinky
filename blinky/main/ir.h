#pragma once

namespace ir
{
    void transmit(void *arg);
    void receive(void *arg);

    void exchange_protocol(uint16_t myAnimation);
}