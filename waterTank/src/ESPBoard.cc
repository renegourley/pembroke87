#include "Board.h"
#include "ESPBoard.h"
#include "Arduino.h"

ESPBoard::ESPBoard(int motorPorts[]) {
  _motorPorts = motorPorts;
  for (int i = 0; i<MOTOR_PIN_COUNT; i++) {
     pinMode(_motorPorts[i],OUTPUT);
  }
}

void ESPBoard::writeMotor(int pinValues[]) {
  for (int i=0; i<MOTOR_PIN_COUNT; i++) {
    digitalWrite(_motorPorts[i],pinValues[i]);
  }
}