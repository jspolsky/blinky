#include <Adafruit_NeoPixel.h>
#include <ArduinoLowPower.h>
#include <RTCZero.h>

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);
RTCZero rtc;

volatile bool bClockFired;
volatile bool fDown = false;


void showColor(uint8_t r, uint8_t g, uint8_t b)
{
  pixels.setPixelColor(0, pixels.Color(r,g,b));
  pixels.show();
}

void setup() {

  bClockFired = false;
  fDown = false;

  pixels.begin();
  showColor(32, 32, 32);

  pinMode( A0, INPUT_PULLUP );

  rtc.begin();
  rtc.attachInterrupt(isrClock); 
  LowPower.attachInterruptWakeup( digitalPinToInterrupt(A0), isrPin, CHANGE ); 
}

void isrClock() {

  bClockFired = true;

}

void isrPin() {

    int state = digitalRead(A0);
    fDown = (!fDown && state == LOW);
 
}

void loop() {

  if (bClockFired) {
    
    // Power saving timeout. Simulate this
    // by turning off the LED, in reality we would turn off
    // the digital display
    
    bClockFired = false;
    showColor(0, 0, 0);
    
  }

  else if (fDown) {
    
    fDown = false;

    unsigned long tmStart = millis();
    bool fLongPressDetected = false;

    // wait for up
    while (digitalRead(A0) == LOW)
    {

      if (tmStart + 750L < millis()) {
      
        fLongPressDetected = true;

        while (digitalRead(A0) == LOW) {
          
          // long press action
          showColor(0, 0, millis() % 255);

        }

        // end of long press
        showColor(0, 0, 64);
        
      }
    }

    if (!fLongPressDetected) {

      //it's a short press
      showColor(0, 32, 0);
    
    }    
       
  }

  rtc.setTime(0,0,0);
  rtc.setDate(1,9,2022);
  rtc.setAlarmTime(0, 0, 10);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  LowPower.sleep();

}
