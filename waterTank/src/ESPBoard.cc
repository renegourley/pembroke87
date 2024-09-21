#include <HardwareSerial.h>
#include "Board.h"
#include "ESPBoard.h"
#include "Arduino.h"

void ESPBoard::setupMotor(const int motorPorts[]) {
  _motorPorts = motorPorts;
  for (int i = 0; i<MOTOR_PIN_COUNT; i++) {
     pinMode(_motorPorts[i],OUTPUT);
  }
}

void ESPBoard::writeMotor(int pinValues[]) {
  for (int i=0; i<MOTOR_PIN_COUNT; i++) {
    digitalWrite(_motorPorts[i],pinValues[i]);

#ifdef _DEBUG
    Serial.print(pinValues[i]);
#endif
  }

#ifdef _DEBUG
  Serial.println(" written to motor pins");
#endif
}

void ESPBoard::setupMp3(int mp3Tx, int mp3Rx) {
  Serial2.begin(9600,SERIAL_8N1,mp3Rx,mp3Tx);
  if (!_mp3.begin(Serial2)) throw "Failed to initialize mp3";
}

void ESPBoard::mp3Play(uint track) {
#ifdef _DEBUG
  Serial.print("Starting track...");
  Serial.println(track);
#endif

  _mp3.loop(track);
}

void ESPBoard::mp3Stop() {
  _mp3.stop();
}

void ESPBoard::mp3Volume(uint volume) {
  // This read from the mp3 player seems to resolve some
  // timing issue that emerged when the player was connected
  // to the board. Remove at your peril!
  uint8_t messageType = _mp3.readType();

#ifdef _DEBUG
  Serial.print("Set volume: ");
  Serial.println(volume);
  uint16_t messageValue = _mp3.read();
  this->mp3PrintDetail(_mp3.readType(), _mp3.read());
#endif

  _mp3.volume(volume);
}

void ESPBoard::setupValveSwitchInput(uint8_t pin) {
  _valveSwitchPin = pin;
  pinMode(pin,INPUT_PULLUP);
}

bool ESPBoard::valveSwitchIsClosed() {
  return(digitalRead(_valveSwitchPin) == LOW);
}

void ESPBoard::setupLimitSwitchInput(uint8_t pin) {
  _limitSwitchPin = pin;
  pinMode(pin,INPUT_PULLUP);
}

bool ESPBoard::limitSwitchIsClosed() {
  return(digitalRead(_limitSwitchPin) == LOW);
}

void ESPBoard::delayMilliseconds(int milliseconds){
  delay(milliseconds);
}

unsigned long ESPBoard::millisecondsSinceBoot(){
  return millis();
}

#ifdef _DEBUG
void ESPBoard::mp3PrintDetail(uint8_t type, int value){
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }
}
#endif
