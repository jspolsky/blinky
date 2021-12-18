// blinky for the ESP32C3

#include "util.h"
#include "pins.h"
#include "button.h"

void setup()
{

  Util::setup();

  // SLEEP MANAGEMENT
  //

  Util::setColorRGB(255,255,255);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO)
  {
    Util::setColorRGB(255,0,0);
  }
  else 
  {
    esp_deep_sleep_enable_gpio_wakeup( BIT(PIN_BUTTON), ESP_GPIO_WAKEUP_GPIO_HIGH );
    esp_deep_sleep_start();
  }

  // ok yeah we just woke up
  //Button::setup(LongPressStart, LongPressEnd, ShortPress);

}

void loop()
{
  //Button::loop();
}

void LongPressStart()
{
}

void LongPressEnd()
{
}

void ShortPress()
{
}