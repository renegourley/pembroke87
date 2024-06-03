#ifndef ESPBOARD_H
#define ESPBOARD_H

#include "Board.h"
#include "Constants.h"

class ESPBoard: public Board {

private:
    int* _motorPorts;
    int _motorPinValues[MOTOR_PIN_COUNT];
public:
    ESPBoard(int[4]); //MotorPorts
    void writeMotor(int[4]);
};

#endif