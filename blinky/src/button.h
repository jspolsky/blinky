// Button - handles the push button!

#pragma once
typedef void(CALLBACK)(void);

namespace Button
{
    void setup(CALLBACK *fnLongPressStart, CALLBACK *fnLongPressEnd, CALLBACK *fnShortPress);
    void loop();
    void sleep();
    bool can_sleep();

    void fnSwitch();    // called to switch display
    void fnStartSwap(); // called to start swap with friend
    void fnEndSwap();   // calle to end swap
}