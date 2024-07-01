#ifndef LINEARACTUATOR_H
#define LINEARACTUATOR_H

#include "WaterGauge.h"
#include "IStepper.h"

class LinearActuator : public WaterGauge {

private:
    IStepper* _stepperPtr = 0;
    int _level = 0;

public:
    LinearActuator(IStepper* stepperPtr);
    void initialize();
    void tick();
};

#endif