#include <Arduino.h>

void moveSteps(bool,int,int);
void moveOneStep(bool);

const int onboardLedPin = 2;
const int betweenStepMs = 100;
const int delayMs = 1000;
const int stepCount = 4*60;

int outports[] = {26,25,33,32};

void setup() {
  Serial.begin(921600);
  Serial.println("hello from setup");
  for (int i = 0; i<4; i++) {
    pinMode(outports[i],OUTPUT);
  }
}

void loop() {
  delay(delayMs);
  moveSteps(true,stepCount,betweenStepMs);
  delay(delayMs);
  moveSteps(false,stepCount,betweenStepMs);
}

void moveSteps(bool forward,int steps,int ms) {
  for (int i=0; i<steps; i++) {
    moveOneStep(forward);
    delay(ms);
  }
}

void moveOneStep(bool forward) {
  static byte out = 0x01;
  if (forward) {
    out != 0x08 ? out = out << 1 : out = 0x01;
  } 
  else {
    out != 0x01 ? out = out >> 1 : out = 0x08;
  }
  for (int i=0; i<4; i++) {
    int value = (out & (0x01 << i)) ? HIGH : LOW;
    digitalWrite(outports[i],value);
    Serial.print(value);
  }
  Serial.println();
}
