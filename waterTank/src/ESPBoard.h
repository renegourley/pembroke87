#ifndef ESPBOARD_H
#define ESPBOARD_H

#include <DFRobotDFPlayerMini.h>
#include "Board.h"
#include "Constants.h"

class ESPBoard: public Board {

private:
    const int* _motorPorts;
    int _motorPinValues[MOTOR_PIN_COUNT];
    uint8_t _valveSwitchPin;
    uint8_t _limitSwitchPin;
    DFRobotDFPlayerMini _mp3;

#ifdef _DEBUG
    void mp3PrintDetail(uint8_t type, int value);
#endif

public:
    void setupValveSwitchInput(uint8_t valveSwitchPin);
    bool valveSwitchIsClosed() override;
    void setupLimitSwitchInput(uint8_t limitSwitchPin);
    bool limitSwitchIsClosed() override;
    void setupMotor(const int motorPorts[4]);
    void writeMotor(int motorValues[4]);

    void setupMp3(int mp3Tx, int mp3Rx);
    void mp3Play(uint track) override;
    void mp3Stop() override;
    void mp3Volume(uint level) override;
    void delayMilliseconds(int millis);
    unsigned long millisecondsSinceBoot();
};

#endif