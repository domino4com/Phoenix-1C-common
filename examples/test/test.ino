#include "p1common.h"

P1Common common("TEST");

void setup() {
  common.begin();
}

void loop() {
  delay(100);
  common.setStatus(1, false);
  delay(100);
  common.setStatus(2, true);
  common.sendStatus();
}