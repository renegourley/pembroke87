#ifndef STEPPER_H
#define STEPPER_H

#include "IStepper.h"
#include "Board.h"

class Stepper : public IStepper {
private:
    int _pinCount;
    int* _pins;
    Board* _boardPtr;
    int _out;
public:
    Stepper(int, Board*);
    void step(bool = true) override;
};

#endif