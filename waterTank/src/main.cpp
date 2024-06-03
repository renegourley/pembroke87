#include <Arduino.h>
#include "ESPBoard.h"
#include "Stepper.h"

void moveSteps(bool,int,int);
void moveOneStep(bool);

const int onboardLedPin = 2;
const int betweenStepMs = 50;
const int delayMs = 500;
const int stepCount = 4*60;

ESPBoard* espBoardPtr;
Stepper* stepperPtr;

int motorPorts[] = {26,25,33,32};

void setup() {
  espBoardPtr = new ESPBoard(motorPorts);
  stepperPtr = new Stepper(MOTOR_PIN_COUNT,espBoardPtr);
}

void loop() {
  delay(delayMs);
  moveSteps(true,stepCount,betweenStepMs);
  delay(delayMs);
  moveSteps(false,stepCount,betweenStepMs);
}

void moveSteps(bool forward,int steps,int ms) {
  for (int i=0; i<steps; i++) {
    stepperPtr->step(forward);
    delay(ms);
  }
}