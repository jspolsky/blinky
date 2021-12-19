// blinky for the ESP32C3

#include "util.h"
#include "pins.h"
#include "button.h"

RTC_DATA_ATTR uint8_t hue = 0;

void setup()
{

  Util::setup();

  // SLEEP MANAGEMENT
  //

  Util::setColorHSV(hue, 255, 255);

  if (esp_sleep_get_wakeup_cause() == ESP_SLEEP_WAKEUP_GPIO)
  {
    Util::setColorHSV(hue, 255, 255);
    hue = (hue + 40) % 255;
  }

  esp_deep_sleep_enable_gpio_wakeup( BIT(PIN_BUTTON), ESP_GPIO_WAKEUP_GPIO_HIGH );
  esp_deep_sleep_start();
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