#include <Arduino.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "ESPBoard.h"
#include "Stepper.h"
#include "LimitSwitch.h"
#include "ValveSwitch.h"
#include "LimitedLinearActuator.h"
#include "WaterGauge.h"
#include "OutflowPipe.h"
#include "WaterTower.h"

static const uint8_t PIN_MP3_TX = 17; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 16; // Connects to module's TX 
static const uint8_t PIN_LIMIT_SWITCH = 36;
static const uint8_t PIN_VALVE_SWITCH = 34;
int motorPorts[] = {26,25,33,32};


const int onboardLedPin = 2;
const int betweenStepMs = 10;
const int delayMs = 500;
const int stepCount = 4*60;
const int maxVolume = 10;
const int volumeSteps = 5;
const int volumeStepDelay = 50;
const int probabilityOfEasterEgg = 100;

ESPBoard* board;
WaterTower* waterTower;

void setup() {
  // Init USB serial port for debugging
  Serial.begin(9600);
  Serial.println("Starting...............");

  board = new ESPBoard();
  board->setupLimitSwitchInput(PIN_LIMIT_SWITCH);
  board->setupValveSwitchInput(PIN_VALVE_SWITCH);
  board->setupMotor(motorPorts);

  pinMode(onboardLedPin,OUTPUT);

  try {
    board->setupMp3(PIN_MP3_TX,PIN_MP3_RX);
  } 
  catch(char* message) {
    Serial.print("Failed to start Mp3: ");
    Serial.println(message);
  }

  waterTower = new WaterTower(
    new WaterGauge(
      board, 
      new LimitedLinearActuator(
        new Stepper(4, board),
        new LimitSwitch(board)), 
      STEPPER_MAX_STEPS), 
    new ValveSwitch(board), 
    new OutflowPipe(board, maxVolume, volumeSteps, 
      volumeStepDelay, probabilityOfEasterEgg));

  waterTower->initialize();
}

void loop() {
  waterTower->tick();
  delay(delayMs);
}