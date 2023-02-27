#ifndef P1COMMON_H
#define P1COMMON_H

#include <Arduino.h>
#include <Freenove_WS2812_Lib_for_ESP32.h>
#include <CAN.h>

class P1Common {
 public:
  P1Common(String);
  void begin();
  void setStatus(int,bool);
  void sendStatus();

 private:
  void setColor(char);
  bool CANok;
  char CANpayloadID[4];
};

#endif