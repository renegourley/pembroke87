#ifndef LINEARACTUATOR_H
#define LINEARACTUATOR_H

#include "ILinearActuator.h"
#include "IStepper.h"

class LinearActuator : public ILinearActuator {

private:
    IStepper* _stepperPtr = 0;

public:
    LinearActuator(IStepper* stepperPtr);
    void initialize();
    virtual void forward();
    void backward();
};

#endif