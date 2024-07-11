#ifndef ESPBOARD_H
#define ESPBOARD_H

#include <DFRobotDFPlayerMini.h>
#include "Board.h"
#include "Constants.h"

class ESPBoard: public Board {

private:
    int* _motorPorts;
    int _motorPinValues[MOTOR_PIN_COUNT];
    DFRobotDFPlayerMini _mp3;
public:
    ESPBoard(int motorPorts[4], int mp3Tx, int mp3Rx);
    void writeMotor(int motorValues[4]);
    void mp3Play(uint track);
    void mp3Stop();
    void mp3Volume(uint level);
};

#endif