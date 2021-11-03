// IR - handles animation swapping via infrared

#pragma once

namespace IR
{
    void setup();
    void loop();
    bool can_sleep();
    void sleep();

    void start();
    void end();
}