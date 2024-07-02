#include <iostream>
#include "Constants.h"
#include "IStepper.h"
#include "ISwitch.h"
#include "LinearActuator.h"
#include "LimitedLinearActuator.h"

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

class TestSwitch : public ISwitch {
private:
    bool _isClosed;
public:
    TestSwitch(bool isClosed) : ISwitch() {
        _isClosed = isClosed;
    };
    bool isOpen() override {
        return !_isClosed;
    };
    bool isClosed() override {
        return _isClosed;
    };
    void toggle() {
        _isClosed = !_isClosed;
    }
};

TEST(LinearActuatorTests, InitializeNonEmptyShouldGoBeyondTop) {
    TestStepper stepper(1);
    LinearActuator linearActuator(&stepper);
    linearActuator.initialize();
    EXPECT_EQ(STEPPER_MAX_STEPS+1,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, InitializeEmptyShouldGoToTop) {
    TestStepper stepper(0);
    LinearActuator linearActuator(&stepper);
    linearActuator.initialize();
    EXPECT_EQ(STEPPER_MAX_STEPS,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, ShouldGoForward) {
    TestStepper stepper(STEPPER_MAX_STEPS);
    LinearActuator linearActuator(&stepper);
    int expectedValue = stepper.getTotalSteps() + 1;
    linearActuator.forward();
    EXPECT_EQ(expectedValue,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, ShouldGoBackward) {
    TestStepper stepper(STEPPER_MAX_STEPS);
    LinearActuator linearActuator(&stepper);
    int expectedValue = stepper.getTotalSteps() - 1;
    linearActuator.backward();
    EXPECT_EQ(expectedValue,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, ShouldNotProgressIfLimitClosed) {
    TestStepper stepper(10);
    TestSwitch limitSwitch(true);
    LimitedLinearActuator linearActuator(&stepper,&limitSwitch);
    int expectedValue = stepper.getTotalSteps();
    linearActuator.forward();
    linearActuator.forward();
    EXPECT_EQ(expectedValue,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, ShouldProgressIfLimitOpen) {
    TestStepper stepper(10);
    TestSwitch limitSwitch(false);
    LimitedLinearActuator linearActuator(&stepper,&limitSwitch);
    int expectedValue = stepper.getTotalSteps() + 2;
    linearActuator.forward();
    linearActuator.forward();
    EXPECT_EQ(expectedValue,stepper.getTotalSteps());
}

TEST(LinearActuatorTests, ShouldRegressRegardlessOfLimit) {
    TestStepper stepper(10);
    TestSwitch limitSwitch(false);
    LimitedLinearActuator linearActuator(&stepper,&limitSwitch);
    int expectedValue = stepper.getTotalSteps() - 2;
    linearActuator.backward();
    limitSwitch.toggle();
    linearActuator.backward();
    EXPECT_EQ(expectedValue,stepper.getTotalSteps());
}
