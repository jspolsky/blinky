#include <Arduino.h>
#include <RTCZero.h>
#include "powersave.h"
#include "util.h"

#define WAKEUP_MINUTES 0
#define WAKEUP_SECONDS 2
#define NUMBER_OF_WAKEUPS 5

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
        rtc.attachInterrupt(alarmMatch);
    }

    void reset()
    {
        // user pressed a button
        alarmCount = 0;
        setAlarm();
    }

    void setup()
    {
        alarmCount = 0;
        rtc.begin();
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
                Util::setColorRGB(255, 255, 255);
                delay(200);
                Util::setColorRGB(0, 0, 0);
                alarmCount = 0;
            }

            setAlarm();
        }
    }
}