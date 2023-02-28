#include "p1common.h"

#define LEDS_COUNT 1
#define LEDS_PIN 18
#define LEDS_CHANNEL 0
char cstr[16];
Freenove_ESP32_WS2812 strip =
    Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, LEDS_CHANNEL, TYPE_GRB);

ESP32Time ESPrtc(7200);  // offset in seconds GMT+1

P1Common::P1Common(String s) { s.toCharArray((char*)CANpayloadID, 5); }

void P1Common::setTime() {}

String P1Common::getTime() { return ESPrtc.getTime(); }

void P1Common::begin() {
  strip.begin();
  strip.setBrightness(5);

  CAN.setPins(2, 4);
  if (CAN.begin(100E3))
    CANok = true;
  else {
    ESP_LOGE("P1Common", "CAN bus failure!");
    CANok = false;
    return;
  }

  // Get epoch time from server try every second for 10 second
  uint8_t epochbytes[4] = {0, 0, 0, 0};
  CAN.filter(0x30);
  for (int i = 0; i < 10; i++) {
    int packetSize = CAN.parsePacket();
    if (packetSize || CAN.packetId() != -1) {
      ESP_LOGD("P1Common", "Parcel Arrived");
      for (int j = 0; j < 5; j++) {
        while (!CAN.available())
          ;
        epochbytes[j] = CAN.read();
        ESP_LOGD("P1Common", "Byte %i = %i", j, epochbytes[j]);
      }
      break;
    }
    delay(1000);
  }
  uint32_t epoch = epochbytes[0] | (epochbytes[1] << 8) |
                   (epochbytes[2] << 16) | (epochbytes[3] << 24);
  ESP_LOGD("P1Common", "Epoch %ld", epoch);
  if (epoch) {
    ESPrtc.setTime(epoch);
    ESP_LOGD("P1Common", "Local Time is %s", getTime());
  } else ESP_LOGE("P1Common", "CAN bus failed to transmit time!");
}

void P1Common::setStatus(int bitno, bool ok) { bitWrite(CANstatus, bitno, ok); }

void P1Common::sendStatus() {
  if (bitRead(CANstatus, 7)) {
    setColor('G');
  } else {
    setColor('R');
  }

  if (CANok) {
      bool _success = false;
  for (int i = 0; i < 10; i++) {
    CAN.beginPacket(0x21);
    CAN.write(CANpayloadID, 4);
    CAN.write(CANstatus);
    if (CAN.endPacket()) {
      break;  // Packet sent, lets move
      _success = true;
    }
    setColor('B');
    delay(random(20));  // Packet not sent, wait a little random bit of time not
                        // to collide with other messages and try again.
  }
  if (!_success) ESP_LOGE("P1Common", "CAN bus transmit failure!");
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