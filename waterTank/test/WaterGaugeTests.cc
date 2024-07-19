#include "ILinearActuator.h"
#include "WaterGauge.h"
#include "Constants.h"

#include "gtest/gtest.h"

int actuatorSteps = 100;

class TestActuator : public ILinearActuator {
private:
    int _position;
public:
    TestActuator(int currentStep) : ILinearActuator() {
        _position = currentStep;
    };
    void initialize() override {
        _position = actuatorSteps;
    };
    void forward() override { 
        _position += 1;
    };
    void backward() override {
        _position -= 1;
    };
    int getPosition() {
        return _position;
    }
};

TEST(WaterGaugeTests, Initialize_ShouldGoForward) {
    TestActuator actuator(0);
    WaterGauge gauge(&actuator, actuatorSteps);
    gauge.initialize();
    EXPECT_FALSE(gauge.isEmpty());
    EXPECT_EQ(actuatorSteps,actuator.getPosition());
}

TEST(WaterGaugeTests, Tick_ShouldGoDownWhenOpen) {
    TestActuator actuator(0);
    WaterGauge gauge(&actuator, 2);
    gauge.initialize();
    gauge.tick(true);
    EXPECT_FALSE(gauge.isEmpty());
    EXPECT_EQ(1,actuator.getPosition());
}

TEST(WaterGaugeTests, Tick_ShouldNotGoPastEmpty) {
    TestActuator actuator(0);
    WaterGauge gauge(&actuator, 1);
    gauge.initialize();
    gauge.tick(true);
    gauge.tick(true);
    gauge.tick(true);
    EXPECT_TRUE(gauge.isEmpty());
    EXPECT_EQ(0,actuator.getPosition());
}

TEST(WaterGaugeTests, Tick_ShouldNotGoPastFull) {
    TestActuator actuator(0);
    WaterGauge gauge(&actuator, 100);
    gauge.initialize();
    gauge.tick(true);
    for (int i=0; i<100; i++)
        gauge.tick(false);
    EXPECT_EQ(100,actuator.getPosition());
}

TEST(WaterGaugeTests, Tick_ShouldGoUp) {
    TestActuator actuator(0);
    WaterGauge gauge(&actuator, 100);
    gauge.initialize();
    gauge.tick(true);
    gauge.tick(true);
    for (int i=0; i<100; i++)
        gauge.tick(false);
    EXPECT_EQ(100,actuator.getPosition());
}

TEST(WaterGaugeTests, Tick_ShouldGoDownFasterThanUp) {
    TestActuator actuator(0);
    WaterGauge gauge(&actuator,100);
    gauge.initialize();
    for (int i=0;i<FILL_TO_EMPTY_RATIO;i++) {
        gauge.tick(true);
    }
    int startPosition = actuator.getPosition();
    gauge.tick(true);
    for (int i=0;i<=FILL_TO_EMPTY_RATIO;i++) {
        gauge.tick(false);
    }
    EXPECT_EQ(startPosition,actuator.getPosition());
}