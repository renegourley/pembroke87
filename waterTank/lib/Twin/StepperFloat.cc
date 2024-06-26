#include "StepperFloat.h"

#include "Constants.h"

StepperFloat::StepperFloat(IStepper* stepperPtr){
    _stepperPtr = stepperPtr;
    for (int i=0;i<STEPPER_MAX_STEPS;i++)
        _stepperPtr->step(true);
}

void StepperFloat::tick() {
    
}