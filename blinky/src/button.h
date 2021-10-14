// Button - handles the push button!

#pragma once

namespace Button
{
    void setup();
    void loop();
    void sleep();
    bool can_sleep();

    void fnSwitch();    // called to switch display
    void fnStartSwap(); // called to start swap with friend
    void fnEndSwap();   // calle to end swap
}