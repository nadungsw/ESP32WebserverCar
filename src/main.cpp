#include "main.h"

void setup() {
  Serial.begin(115200);
  WebInit();
}

void loop() {
  WebCtrl();
}