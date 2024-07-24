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

void moveSteps(bool,int,int);
// void moveOneStep(bool);

static const uint8_t PIN_MP3_TX = 17; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 16; // Connects to module's TX 
int motorPorts[] = {26,25,33,32};

static const uint8_t PIN_LIMIT_SWITCH = 36;
static const uint8_t PIN_VALVE_SWITCH = 34;

const int onboardLedPin = 2;
const int betweenStepMs = 10;
const int delayMs = 500;
const int stepCount = 4*60;

//Stepper* stepperPtr;


WaterTower* waterTower;
ValveSwitch* valveSwitch;
LimitSwitch* limitSwitch;
ESPBoard* board;
LinearActuator* linearActuator;
WaterGauge* waterGauge;
//Stepper* stepper;
//LimitedLinearActuator* linearActuator;

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

  limitSwitch = new LimitSwitch(board);
  Stepper* stepper = new Stepper(4, board);
  //linearActuator = new LinearActuator(stepper);
  linearActuator = new LimitedLinearActuator(stepper,limitSwitch);
  // LimitedLinearActuator* linearActuator = new LimitedLinearActuator(stepper,limitSwitch);
  waterGauge = new WaterGauge(board, linearActuator, STEPPER_MAX_STEPS);
  valveSwitch = new ValveSwitch(board);
  // ValveSwitch* valveSwitch = new ValveSwitch(board);
  OutflowPipe* outflowPipe = new OutflowPipe(board, 10, 5, 50, 100);
  waterTower = new WaterTower(waterGauge, valveSwitch, outflowPipe);
  Serial.println("initializing...");
  waterGauge->initialize();
  //waterTower->initialize();
  Serial.println("finished");

  // delay(delayMs);

  // moveSteps(true,stepCount,betweenStepMs);
  // delay(delayMs);
  // moveSteps(false,stepCount,betweenStepMs);

}

bool initialized = false;
// static const int delayMs = 100;
void loop() {

  // if (!initialized) {
  //   waterTower->initialize();
  //   for (int i=0;i<STEPPER_MAX_STEPS;i++) linearActuator->forward();
  //   initialized=true;
  // } 

  // if (limitSwitch->isClosed()) {
  //   digitalWrite(onboardLedPin,HIGH);
  // } else {
  //   digitalWrite(onboardLedPin,LOW);
  // }

  waterTower->tick();
  delay(delayMs);

  // moveSteps(true,stepCount,betweenStepMs);
  // delay(delayMs);
  // moveSteps(false,stepCount,betweenStepMs);

}

void moveSteps(bool forward,int steps,int ms) {
  for (int i=0; i<steps; i++) {
    (forward) ? waterGauge->tick(false) : waterGauge->tick(true);
    // (forward) ? linearActuator->forward() : linearActuator->backward();
    delay(ms);
  }
}