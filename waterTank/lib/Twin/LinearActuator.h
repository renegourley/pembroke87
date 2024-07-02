#ifndef LINEARACTUATOR_H
#define LINEARACTUATOR_H

#include "WaterGauge.h"
#include "IStepper.h"

class LinearActuator : public WaterGauge {

private:
    IStepper* _stepperPtr = 0;

public:
    LinearActuator(IStepper* stepperPtr);
    void initialize();
    virtual void forward();
    void backward();
};

#endif