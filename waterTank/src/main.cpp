#include <Arduino.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "ESPBoard.h"
#include "Stepper.h"

void moveSteps(bool,int,int);
void moveOneStep(bool);

static const uint8_t PIN_MP3_TX = 17; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 16; // Connects to module's TX 

// const int onboardLedPin = 2;
// const int betweenStepMs = 10;
// const int delayMs = 500;
// const int stepCount = 4*60;

ESPBoard* espBoardPtr;
//Stepper* stepperPtr;

int motorPorts[] = {26,25,33,32};

void setup() {

  // Init USB serial port for debugging
  Serial.begin(9600);
  Serial.println("Starting...............");

  try {
    espBoardPtr = new ESPBoard(motorPorts, PIN_MP3_TX, PIN_MP3_RX);
    Serial.println("OK");
    espBoardPtr->mp3Volume(10);
    espBoardPtr->mp3Play(1);
  } 
  catch(char* message) {
    Serial.print("Failed to start: ");
    Serial.println(message);
  }
}

void loop() {
//  delay(delayMs);
//  moveSteps(true,stepCount,betweenStepMs);
//  delay(delayMs);
//  moveSteps(false,stepCount,betweenStepMs);

}

// void moveSteps(bool forward,int steps,int ms) {
//   for (int i=0; i<steps; i++) {
//     stepperPtr->step(forward);
//     delay(ms);
//   }
// }