#include <iostream>
#include "Constants.h"
#include "IStepper.h"
#include "StepperFloat.h"

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

TEST(StepperFloatTests, InitializeNonEmptyShouldGoBeyondTop) {
    TestStepper stepper(1);
    StepperFloat stepperFloat(&stepper);
    EXPECT_EQ(STEPPER_MAX_STEPS+1,stepper.getTotalSteps());
}

TEST(StepperFloatTests, InitializeEmptyShouldGoToTop) {
    TestStepper stepper(0);
    StepperFloat stepperFloat(&stepper);
    EXPECT_EQ(STEPPER_MAX_STEPS,stepper.getTotalSteps());
}

TEST(StepperFloatTests, ShouldNotChangeOnceAtTop) {
    TestStepper stepper(STEPPER_MAX_STEPS);
    StepperFloat stepperFloat(&stepper);
    int expectedValue = stepper.getTotalSteps();
    stepperFloat.tick();
    EXPECT_EQ(expectedValue,stepper.getTotalSteps());
}


