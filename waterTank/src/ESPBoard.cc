#include <HardwareSerial.h>
#include "Board.h"
#include "ESPBoard.h"
#include "Arduino.h"

ESPBoard::ESPBoard(int motorPorts[], int mp3Tx, int mp3Rx) {
  _motorPorts = motorPorts;
  for (int i = 0; i<MOTOR_PIN_COUNT; i++) {
     pinMode(_motorPorts[i],OUTPUT);
  }

  Serial2.begin(9600,SERIAL_8N1,mp3Rx,mp3Tx);
  if (!_mp3.begin(Serial2)) throw "Failed to initialize mp3";
}

void ESPBoard::writeMotor(int pinValues[]) {
  for (int i=0; i<MOTOR_PIN_COUNT; i++) {
    digitalWrite(_motorPorts[i],pinValues[i]);
  }
}

void ESPBoard::mp3Play(uint track) {
  _mp3.loop(track);
}

void ESPBoard::mp3Stop() {
  _mp3.stop();
}

void ESPBoard::mp3Volume(uint volume) {
  _mp3.volume(volume);
}