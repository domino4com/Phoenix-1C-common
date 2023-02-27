#include "p1common.h"

P1Common common("TEST");

void setup() {
  common.begin();
}

void loop() {
  delay(100);
  common.setStatus(P1C_FLAG, false);
  delay(100);
  common.setStatus(P1C_ALL_OK, true);
  common.sendStatus();
}