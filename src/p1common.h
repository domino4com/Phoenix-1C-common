#ifndef P1COMMON_H
#define P1COMMON_H

#include <Arduino.h>
#include <Freenove_WS2812_Lib_for_ESP32.h>
#include <CAN.h>

#define P1C_ALL_OK    7
#define P1C_SD1       6
#define P1C_SD2       5
#define P1C_FLAG      4
#define P1C_SENSOR_1  3
#define P1C_SENSOR_2  2
#define P1C_SENSOR_3  1
#define P1C_SENSOR_4  0

class P1Common {
 public:
  P1Common(String);
  void begin();
  void setStatus(int,bool);
  void sendStatus();

 private:
  void setColor(char);
  bool CANok;
  const uint8_t CANpayloadID[4];
  byte CANstatus;
};

#endif