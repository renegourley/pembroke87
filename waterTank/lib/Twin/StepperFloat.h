#ifndef STEPPERFLOAT_H
#define STEPPERFLOAT_H

#include "WaterGauge.h"
#include "IStepper.h"

class StepperFloat : public WaterGauge {

private:
    IStepper* _stepperPtr = 0;
    int _level = 0;

public:
    StepperFloat(IStepper* stepperPtr);
    void tick();
};

#endif