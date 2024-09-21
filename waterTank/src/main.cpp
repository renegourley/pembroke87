#include <Arduino.h>
#include <HardwareSerial.h>
#include "ESPBoard.h"
#include "Stepper.h"
#include "LimitSwitch.h"
#include "ValveSwitch.h"
#include "LimitedLinearActuator.h"
#include "WaterGauge.h"
#include "OutflowPipe.h"
#include "WaterTower.h"

static const uint8_t mp3TransmitPin = 17; // Connects to module's RX 
static const uint8_t mp3ReceivePin = 16; // Connects to module's TX 
static const uint8_t limitSwitchPin = 4;
static const uint8_t valveSwitchPin = 15;
static const int motorPins[] = {26,25,33,32};

static const int delayMs = 500;
static const int stepCount = 4*60;
static const int maxVolume = 10;
static const int volumeSteps = 5;
static const int volumeStepDelay = 25;
static const int probabilityOfEasterEgg = 100;

static ESPBoard* boardPtr;
static WaterTower* waterTowerPtr;
static ValveSwitch* valveSwitchPtr;
static LimitSwitch* limitSwitchPtr;

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  Serial.println("Starting...............");

  boardPtr = new ESPBoard();
  boardPtr->setupLimitSwitchInput(limitSwitchPin);
  boardPtr->setupValveSwitchInput(valveSwitchPin);
  boardPtr->setupMotor(motorPins);

  valveSwitchPtr = new ValveSwitch(boardPtr);
  limitSwitchPtr = new LimitSwitch(boardPtr);

  try {
    boardPtr->setupMp3(mp3TransmitPin,mp3ReceivePin);
  } 
  catch(char* message) {
    Serial.print("Failed to start Mp3: ");
    Serial.println(message);
  }

  waterTowerPtr = new WaterTower(
    new WaterGauge(
      boardPtr, 
      new LimitedLinearActuator(
        new Stepper(4, boardPtr),
        limitSwitchPtr),
      STEPPER_MAX_STEPS), 
    valveSwitchPtr,
    new OutflowPipe(boardPtr, maxVolume, volumeSteps, 
      volumeStepDelay, probabilityOfEasterEgg));

  waterTowerPtr->initialize();
}

void loop() {
  
#ifdef _DEBUG
  Serial.print(lPtr->isClosed() ? "limit closed " : "limit open   ");
  Serial.println(vPtr->isClosed() ? "valve closed" : "valve open");
#endif

  waterTowerPtr->tick();
  delay(delayMs);
}