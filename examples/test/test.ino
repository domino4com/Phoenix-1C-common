#include "p1common.h"

P1Common common;

void setup() {
  common.begin();
}

void loop() {
  delay(100);
  common.report(false, "Something is wrong");
  delay(100);
  common.report(true, "All good");
}