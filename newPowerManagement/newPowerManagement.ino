#include <Adafruit_NeoPixel.h>
#include <ArduinoLowPower.h>
#include <RTCZero.h>

Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);
RTCZero rtc;

#define BUTTON_PIN A0

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

  pinMode( BUTTON_PIN, INPUT_PULLUP );

  rtc.begin();
  rtc.attachInterrupt(isrClock); 
  LowPower.attachInterruptWakeup( digitalPinToInterrupt(BUTTON_PIN), isrPin, CHANGE ); 
}

void isrClock() {

  bClockFired = true;

}

void isrPin() {

    fDown = (digitalRead(BUTTON_PIN) == LOW);
 
}

void loop() {

  if (bClockFired) {
    
    // Power saving timeout
    
    bClockFired = false;

    // TODO TURN OFF THE MATRIX
    showColor(0, 0, 0);
    
  }

  else if (fDown) {
    
    fDown = false;

    unsigned long tmStart = millis();
    bool fLongPressDetected = false;

    // wait for up
    while (digitalRead(BUTTON_PIN) == LOW)
    {

      if (tmStart + 500L < millis()) {
      
        fLongPressDetected = true;

        while (digitalRead(BUTTON_PIN) == LOW) {
          
          // TODO RUN IR::start()
          // TODO run IR::loop() in a loop until it is "idle"
          //      -- modify IR::loop() to be told the button state
      
          showColor(0, 0, millis() % 255);

        }

        // end of long press
        
        showColor(0, 0, 64);
        
      }
    }

    if (!fLongPressDetected) {

      //it's a short press
      showColor(0, 32, 0);
      
      // TODO show next animation
      
    
    }    
       
  }

  rtc.setTime(0,0,0);
  rtc.setDate(1,9,2022);
  rtc.setAlarmTime(0, 0, 10);
  rtc.enableAlarm(rtc.MATCH_HHMMSS);
  LowPower.sleep();

}
