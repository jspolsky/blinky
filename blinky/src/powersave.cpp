#include <Arduino.h>
#include <RTCZero.h>
#include "powersave.h"
#include "matrix.h"
#include "util.h"

#define WAKEUP_MINUTES 5
#define WAKEUP_SECONDS 0
#define NUMBER_OF_WAKEUPS 24 /* 5 minutes * 24 wakeups = 2 hours */

namespace PowerSave
{

    static bool alarmMatched = false;
    static uint32_t alarmCount = 0;
    static RTCZero rtc;

    void alarmMatch(void)
    {
        alarmMatched = true;
    }

    void setAlarm()
    {
        rtc.disableAlarm();
        rtc.setTime(0, 0, 0);
        rtc.setDate(1, 1, 5);
        rtc.setAlarmTime(0, WAKEUP_MINUTES, WAKEUP_SECONDS); // ten seconds right now
        rtc.enableAlarm(rtc.MATCH_HHMMSS);
    }

    void reset()
    {
        // user pressed a button
        alarmCount = 0;

        Matrix::power(true);

        setAlarm();
    }

    void setup()
    {
        alarmCount = 0;

        rtc.begin();
        rtc.attachInterrupt(alarmMatch);

        setAlarm();
    }

    void loop()
    {
        if (alarmMatched)
        {
            alarmMatched = false;
            alarmCount++;

            if (alarmCount >= NUMBER_OF_WAKEUPS)
            {

                Matrix::power(false);
                alarmCount = 0;
            }

            setAlarm();
        }
    }
}