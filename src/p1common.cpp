#include "p1common.h"

Freenove_ESP32_WS2812 strip =
    Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, LEDS_CHANNEL, TYPE_GRB);

P1Common::P1Common() {}

void P1Common::begin() {
  strip.begin();
  strip.setBrightness(100);
}

void P1Common::report(bool ok, String data) {
  if (ok) {
    setColor('G');
    delay(10);
    setColor('X');
  } else {
    setColor('R');
  }
}

void P1Common::setColor(char color) {
  switch (color) {
    case 'R':
      strip.setLedColor(0, 255, 0, 0);
      break;
    case 'G':
      strip.setLedColor(0, 0, 255, 0);
      break;
    case 'B':
      strip.setLedColor(0, 0, 0, 255);
      break;
    case 'X':
      strip.setLedColor(0, 0, 0, 0);
      break;
  }
}