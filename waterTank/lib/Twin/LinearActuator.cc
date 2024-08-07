#include "LinearActuator.h"

#include "Constants.h"

LinearActuator::LinearActuator(IStepper* stepperPtr) : ILinearActuator() {
    _stepperPtr = stepperPtr;
}

void LinearActuator::initialize() {
    for (int i=0;i<STEPPER_MAX_STEPS;i++)
        _stepperPtr->step(true);
}

void LinearActuator::forward() {
    _stepperPtr->step(true);
}

void LinearActuator::backward() {
    _stepperPtr->step(false);
}