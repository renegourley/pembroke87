#ifndef LIMITEDLINEARACTUATOR_H
#define LIMITEDLINEARACTUATOR_H

#include "LinearActuator.h"
#include "ISwitch.h"
#include "IStepper.h"

class LimitedLinearActuator : public LinearActuator {

private:
    ISwitch* _limitSwitchPtr;
public:
    LimitedLinearActuator(IStepper* stepperPtr, ISwitch* _forwardLimitSwitch);
    void forward() override;
};

#endif