#include <iostream>
#include "Constants.h"
#include "IStepper.h"
#include "LinearActuator.h"

#include "gtest/gtest.h"

class TestStepper : public IStepper {

private:
    int _stepSum;
public:
    TestStepper(int initialLevel) : IStepper() {
        printf("initializing testStepper\n");
        _stepSum = initialLevel;
    };

    void step(bool forward) override{
        printf("step");
        _stepSum += (forward) ? 1 : -1;
    };

    int getTotalSteps(){
        return _stepSum;
    }

};

TEST(LinearActuatorTests, InitializeNonEmptyShouldGoBeyondTop) {
    TestStepper stepper(1);
    LinearActuator stepperFloat(&stepper);
    EXPECT_EQ(STEPPER_MAX_STEPS+1,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, InitializeEmptyShouldGoToTop) {
    TestStepper stepper(0);
    LinearActuator stepperFloat(&stepper);
    EXPECT_EQ(STEPPER_MAX_STEPS,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, ShouldNotChangeOnceAtTop) {
    TestStepper stepper(STEPPER_MAX_STEPS);
    LinearActuator stepperFloat(&stepper);
    int expectedValue = stepper.getTotalSteps();
    stepperFloat.tick();
    EXPECT_EQ(expectedValue,stepper.getTotalSteps());
}


