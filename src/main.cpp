#include <Arduino.h>

#define X_STEP 3 // Was pumpPin=2, now X-stepper step pin
#define X_DIR 4  // X-stepper direction pin
#define Z_STEP 5 // Z-stepper step pin
#define Z_DIR 6  // Z-stepper direction pin
#define PUMP_PIN 2

#define X_STEPS 2000    // Steps for horizontal movement
#define Z_STEPS 1000    // Steps for vertical movement
#define STEP_DELAY 1000 // Speed (microseconds) - lower = faster
#define PUMP_TIME 10000 // Pump time in milliseconds (10 seconds)
#define PAUSE_TIME 1000 // Pause between movements (milliseconds)

void setup()
{
  // Initialize all pins
  pinMode(X_STEP, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(Z_STEP, OUTPUT);
  pinMode(Z_DIR, OUTPUT);
  pinMode(PUMP_PIN, OUTPUT);

  // Start with everything OFF
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(X_STEP, LOW);
  digitalWrite(Z_STEP, LOW);

  // Optional: Status LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH); // LED ON = system active

  // Wait 2 seconds after plugging in before starting
  delay(2000);

  // Run the complete automatic sequence
  runCompleteSequence();

  // Turn off LED when done
  digitalWrite(LED_BUILTIN, LOW);
}

void loop()
{
  // Empty - runs once and stops
  // (To run continuously, move runCompleteSequence() here)
}

void runCompleteSequence()
{
  // === STEP 1: X-AXIS MOVE HORIZONTALLY ===
  moveStepper(X_STEP, X_DIR, HIGH, X_STEPS); // Move forward
  delay(PAUSE_TIME);

  // === STEP 2: Z-AXIS MOVE DOWN ===
  moveStepper(Z_STEP, Z_DIR, LOW, Z_STEPS); // Move down
  delay(PAUSE_TIME);

  // === STEP 3: PUMP FOR 10 SECONDS ===
  digitalWrite(PUMP_PIN, HIGH); // Turn pump ON
  delay(PUMP_TIME);             // Wait 10 seconds
  digitalWrite(PUMP_PIN, LOW);  // Turn pump OFF
  delay(PAUSE_TIME);

  // === STEP 4: Z-AXIS MOVE UP ===
  moveStepper(Z_STEP, Z_DIR, HIGH, Z_STEPS); // Move up
  delay(PAUSE_TIME);

  // === STEP 5: X-AXIS RETURN HOME ===
  moveStepper(X_STEP, X_DIR, LOW, X_STEPS); // Move backward
  // Sequence complete!
}

void moveStepper(int stepPin, int dirPin, bool direction, int steps)
{
  // Set direction (HIGH = one way, LOW = opposite way)
  digitalWrite(dirPin, direction ? HIGH : LOW);

  // Generate step pulses
  for (int i = 0; i < steps; i++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(STEP_DELAY);
  }
}