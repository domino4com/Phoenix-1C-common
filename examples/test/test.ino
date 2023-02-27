#include "p1common.h"

P1Common common("TSTC");

void setup() {
  common.begin();
}

void loop() {
  delay(100);
  common.setStatus(P1C_FLAG, true);
  delay(100);
  common.setStatus(P1C_ALL_OK, true);
  common.sendStatus();
  delay(2000);
}