#include "p1common.h"

#define LEDS_COUNT 1
#define LEDS_PIN 18
#define LEDS_CHANNEL 0

Freenove_ESP32_WS2812 strip =
    Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, LEDS_CHANNEL, TYPE_GRB);

P1Common::P1Common(String s) { s.toCharArray(CANpayloadID, 4); }

void P1Common::begin() {
  strip.begin();
  strip.setBrightness(5);

  CAN.setPins(2, 4);
  if (CAN.begin(250E3))
    CANok = true;
  else
    CANok = false;
}

void P1Common::setStatus(int bitno, bool ok) { bitWrite(CANstatus, bitno, ok); }

void P1Common::sendStatus() {
  if (bitRead(CANstatus, 7)) {
    setColor('G');
  } else {
    setColor('R');
  }
  for (int i = 0; i < 10; i++) {
    CAN.beginPacket(0x21);
    CAN.write(CANpayloadID, 4);
    CAN.write(CANstatus);
    if (CAN.endPacket()) break;  // Packet sent, lets move
    delay(random(20));  // Packet not sent, wait a little random bit of time not
                        // to collide with other messages and try again.
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