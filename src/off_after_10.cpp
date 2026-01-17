#include <Arduino.h>

const int pumpPin = 2;  // Pin connected to relay IN

void setup() {
  // Set pump control pin as output
  pinMode(pumpPin, OUTPUT);
  
  // Turn pump ON immediately
  digitalWrite(pumpPin, HIGH);


  //UNCOMMENT THE LINES BELOW TO ADD TURN-OFF CONDITION
  // Example 1: Turn off after 10 seconds
  delay(10000);             // Wait 10 seconds
  digitalWrite(pumpPin, LOW); // Turn pump OFF
}

void loop() {
  // Empty loop - pump stays ON forever
  // (or until you upload new code or reset Arduino)
}