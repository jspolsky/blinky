// IR - handles animation swapping via infrared

#pragma once

namespace IR
{
    void setup();

    void run_protocol();

    void loop();
    bool can_sleep();
    void sleep();

}