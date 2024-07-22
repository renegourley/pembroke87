#include <HardwareSerial.h>
#include "Board.h"
#include "ESPBoard.h"
#include "Arduino.h"

void ESPBoard::setupMotor(int motorPorts[]) {
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

void ESPBoard::setupMp3(int mp3Tx, int mp3Rx) {
  Serial2.begin(9600,SERIAL_8N1,mp3Rx,mp3Tx);
  if (!_mp3.begin(Serial2)) throw "Failed to initialize mp3";
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

void ESPBoard::setupValveSwitchInput(uint8_t pin) {
  _valveSwitchPin = pin;
  pinMode(pin,INPUT);
}

bool ESPBoard::valveSwitchIsClosed() {
  return(digitalRead(_valveSwitchPin) == HIGH);
}

void ESPBoard::setupLimitSwitchInput(uint8_t pin) {
  _limitSwitchPin = pin;
  pinMode(pin,INPUT);
}

bool ESPBoard::limitSwitchIsClosed() {
  return(digitalRead(_limitSwitchPin) == HIGH);
}

void ESPBoard::delayMilliseconds(int milliseconds){
  delay(milliseconds);
}

unsigned long ESPBoard::millisecondsSinceBoot(){
  return millis();
}
