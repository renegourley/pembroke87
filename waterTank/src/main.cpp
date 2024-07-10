#include <Arduino.h>
//#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "ESPBoard.h"
#include "Stepper.h"
// #include "DFPlayer.h"

void moveSteps(bool,int,int);
void moveOneStep(bool);

#define MP3_RX_PIN              5     //GPIO4/D2 to DFPlayer Mini TX
#define MP3_TX_PIN              4     //GPIO5/D1 to DFPlayer Mini RX
#define MP3_SERIAL_SPEED        9600  //DFPlayer Mini suport only 9600-baud
#define MP3_SERIAL_BUFFER_SIZE  32    //software serial buffer size in bytes, to send 8-bytes you need 11-bytes buffer (start byte+8-data bytes+parity-byte+stop-byte=11-bytes)
#define MP3_SERIAL_TIMEOUT      350   //average DFPlayer response timeout 200msec..300msec for YX5200/AAxxxx chip & 350msec..500msec for GD3200B/MH2024K chip

static const uint8_t PIN_MP3_TX = 17; // Connects to module's RX 
static const uint8_t PIN_MP3_RX = 16; // Connects to module's TX 
//SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);

// Create the Player object
DFRobotDFPlayerMini player;

//SoftwareSerial mp3Serial;
//DFPlayer       mp3;


const int onboardLedPin = 2;
const int betweenStepMs = 10;
const int delayMs = 500;
const int stepCount = 4*60;

ESPBoard* espBoardPtr;
//Stepper* stepperPtr;

int motorPorts[] = {26,25,33,32};

void setup() {

  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  //softwareSerial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, PIN_MP3_RX, PIN_MP3_TX);

  Serial.println("Starting...............");
  // Start communication with DFPlayer Mini
  if (player.begin(Serial2)) {
   Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(5);
    // Play the first MP3 file on the SD card
    player.play(2);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
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