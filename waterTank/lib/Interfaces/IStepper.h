#ifndef ISTEPPER_H
#define ISTEPPER_H

#include "Board.h"

class IStepper {
public:
    virtual void step(bool = true) {};
};

#endif