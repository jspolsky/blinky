/*
  To help debug IR codes, this is a simple sketch for a simple device
  that receives the IR codes and displays them.
 */


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     A1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DECODE_NEC
#define IR_RECEIVE_PIN A0
#include <IRremote.h>

#include <Adafruit_NeoPixel.h>

// create a pixel strand with 1 pixel on PIN_NEOPIXEL
Adafruit_NeoPixel pixels(1, PIN_NEOPIXEL);


void setup() {

  delay(1000);


  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(800); // Pause for .8 seconds

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  display.clearDisplay();
  display.display();

  display.setTextSize(1);

  pixels.begin();
}

void loop() {

  static uint32_t lastmessage = 0;


  if (IrReceiver.decode())
  {

    if (IrReceiver.decodedIRData.address != 0 ||
        IrReceiver.decodedIRData.command != 0) {

       lastmessage = millis();
    
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(SSD1306_WHITE);
      display.cp437(true);
      
      display.setCursor(0,0);
      display.println("Message:");
      
      display.setTextSize(1);
      display.println(IrReceiver.decodedIRData.address, HEX);
      display.println(IrReceiver.decodedIRData.command, HEX);
      display.display();

      // flash the built in neopixel
      pixels.setPixelColor(0, pixels.Color(0x65, 0x43, 0x21));
      pixels.show();
      delay(10);
      pixels.clear();
      pixels.show();

    }
    
    IrReceiver.resume();
  }

  if (millis() > lastmessage + 3000)
  {
      display.clearDisplay();
      display.display();
  }


}
