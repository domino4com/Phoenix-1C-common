#include "p1common.h"

P1Common common("TSTA");

void setup() {
  Serial.begin(115200);
  common.begin();
}

void loop() {
  Serial.println(common.getTime());
  delay(100);
  common.setStatus(P1C_FLAG, true);
  delay(100);
  common.setStatus(P1C_ALL_OK, true);
  common.sendStatus();
  delay(random(30)*100);
}