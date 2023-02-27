#include "p1common.h"

#define LEDS_COUNT 1
#define LEDS_PIN 18
#define LEDS_CHANNEL 0

Freenove_ESP32_WS2812 strip =
    Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, LEDS_CHANNEL, TYPE_GRB);

struct  {
  char pid[4];
  bool AllOK : 1;
  bool SDerr1 : 1;
  bool SDerr2 : 1;
  bool Flag : 1;
  bool Sensor1 : 1;
  bool Sensor2 : 1;
  bool Sensor3 : 1;
  bool Sensor4 : 1;
} sReport;

P1Common::P1Common(String s) {
  sprintf(CANpayloadID,"%4s",s);
  // strcpyn(CANpayloadID,s,4);
}

void P1Common::begin() {
  strip.begin();
  strip.setBrightness(5);

  CAN.setPins(2, 4);
  if (CAN.begin(250E3))
    CANok = true;
  else
    CANok = false;
}

void P1Common::setStatus(int bitno,bool ok) {
  Serial.printf( "Memory size occupied by status1 : %d\n", sizeof(sReport));
  if (ok) {
    setColor('G');
  } else {
    setColor('R');
  }
}

void P1Common::sendStatus() {
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