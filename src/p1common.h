#ifndef P1COMMON_H
#define P1COMMON_H

#include <Arduino.h>

#include "Freenove_WS2812_Lib_for_ESP32.h"
#define LEDS_COUNT 1
#define LEDS_PIN 18
#define LEDS_CHANNEL 0

class P1Common {
 public:
  P1Common();
  void begin();
  void report(bool ok, String data);

 private:
  void setColor(char);
};

#endif