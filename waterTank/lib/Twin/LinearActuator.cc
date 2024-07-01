#include "LinearActuator.h"

#include "Constants.h"

LinearActuator::LinearActuator(IStepper* stepperPtr){
    _stepperPtr = stepperPtr;
}

void LinearActuator::initialize() {
    for (int i=0;i<STEPPER_MAX_STEPS;i++)
        _stepperPtr->step(true);
}

void LinearActuator::tick() {
    
}