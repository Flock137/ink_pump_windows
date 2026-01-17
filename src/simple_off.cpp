#include <Arduino.h>

const int pumpPin = 3
;  // Pin connected to relay IN

void setup() {
  // Set pump control pin as output
  pinMode(pumpPin, OUTPUT);
  

  digitalWrite(pumpPin, LOW); // Turn pump OFF
}

void loop() {
  // Empty loop - pump stays ON forever
  // (or until you upload new code or reset Arduino)
}