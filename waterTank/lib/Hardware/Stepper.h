  #ifndef STEPPER_H
  #define STEPPER_H

#include "Board.h"

class Stepper {
private:
    int _pinCount;
    int* _pins;
    Board* _boardPtr;
    int _out;
public:
    Stepper(int, Board*);
    void step(bool = true);
};

#endif