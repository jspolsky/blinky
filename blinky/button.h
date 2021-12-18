#pragma once
typedef void(CALLBACK)(void);

namespace Button
{
  void setup(CALLBACK *fnLongPressStart, CALLBACK *fnLongPressEnd, CALLBACK *fnShortPress);
  void loop();
}