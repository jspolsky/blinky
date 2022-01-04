#pragma once

typedef void(CALLBACK)(void);

namespace button
{
    void wakeup(CALLBACK *fnShortPress, CALLBACK *fnLongPress);
    bool buttonDown();
}