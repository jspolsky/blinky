#include <Arduino.h>
#include <RTCZero.h>
#include "powersave.h"
#include "matrix.h"
#include "util.h"

namespace PowerSave
{

    // how long the matrix stays on until
    // power save mode kicks in
    const uint8_t hours = 0;
    const uint8_t minutes = 0;
    const uint8_t seconds = 10;

    volatile bool bClockFired = false;
    RTCZero rtc;

    void isrClock()
    {
        bClockFired = true;
    }

    void setup()
    {
        bClockFired = false;
        rtc.begin();
        rtc.attachInterrupt(isrClock);
    }

    bool loop()
    {
        bool bHandled = false;

        if (bClockFired)
        {
            bClockFired = false;
            Matrix::power(false);
            bHandled = true;
        }

        rtc.setTime(0, 0, 0);
        rtc.setDate(1, 9, 22);
        rtc.setAlarmTime(hours, minutes, seconds);
        rtc.enableAlarm(rtc.MATCH_HHMMSS);

        return bHandled;
    }
}