#include "IStepper.h"
#include "ISwitch.h"

#include "LimitedLinearActuator.h"

LimitedLinearActuator::LimitedLinearActuator(IStepper* stepperPtr, ISwitch* limitSwitchPtr) : LinearActuator(stepperPtr) {
    _limitSwitchPtr = limitSwitchPtr;
};

void LimitedLinearActuator::forward() {
    if (_limitSwitchPtr->isOpen()) {
        LinearActuator::forward();
    }
};