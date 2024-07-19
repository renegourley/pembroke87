#include "gtest/gtest.h"
#include "IOutflowPipe.h"
#include "ISwitch.h"
#include "IWaterGauge.h"
#include "WaterTower.h"

class TestWaterGauge : public IWaterGauge {
private:
public:
    bool _isEmpty = false;
    bool _initialized = false;
    bool _isFlowing = false;
    void initialize(){_initialized=true;};
    void tick(bool valveOpen){_isFlowing = valveOpen && !_isEmpty;};
    bool isEmpty() { return _isEmpty; };
};

class TestOutflowPipe : public IOutflowPipe {
public:
    bool _initialized = false;
    bool _isFlowing = false;
    void initialize(){_initialized=true;};
    void tick(bool waterIsFlowing) {_isFlowing = waterIsFlowing; };
};

class TestSwitch : public ISwitch {
public:
    bool _isClosed = false;
    bool isOpen() { return !_isClosed; };
    bool isClosed() { return _isClosed; };
};

TEST(WaterTowerTests, Initialize_ShouldInitializeChildren) {
    TestWaterGauge gauge;
    TestSwitch valve;
    TestOutflowPipe pipe;
    WaterTower tower(&gauge, &valve, &pipe);
    tower.initialize();
    EXPECT_TRUE(gauge._initialized);
    EXPECT_TRUE(pipe._initialized);
}

TEST(WaterTowerTests, Should_NotBeFlowingOnStartup) {
    TestWaterGauge gauge;
    TestSwitch valve;
    TestOutflowPipe pipe;
    WaterTower tower(&gauge, &valve, &pipe);
    tower.initialize();
    tower.tick();
    EXPECT_FALSE(gauge._isFlowing);
    EXPECT_FALSE(pipe._isFlowing);
}

TEST(WaterTowerTests, ShouldFlowWhenValveClosed) {
    TestWaterGauge gauge;
    TestSwitch valve;
    TestOutflowPipe pipe;
    WaterTower tower(&gauge, &valve, &pipe);
    tower.initialize();
    valve._isClosed=true;
    tower.tick();
    EXPECT_TRUE(gauge._isFlowing);
    EXPECT_TRUE(pipe._isFlowing);
}

TEST(WaterTowerTests, ShouldStopWhenValveOpened) {
    TestWaterGauge gauge;
    TestSwitch valve;
    TestOutflowPipe pipe;
    WaterTower tower(&gauge, &valve, &pipe);
    tower.initialize();
    valve._isClosed=true;
    tower.tick();
    valve._isClosed=false;
    tower.tick();
    EXPECT_FALSE(gauge._isFlowing);
    EXPECT_FALSE(pipe._isFlowing);
}

TEST(WaterTowerTests, ShouldStopWhenEmpty) {
    TestWaterGauge gauge;
    TestSwitch valve;
    TestOutflowPipe pipe;
    WaterTower tower(&gauge, &valve, &pipe);
    tower.initialize();
    valve._isClosed=true;
    gauge._isEmpty=true;
    tower.tick();
    EXPECT_FALSE(gauge._isFlowing);
    EXPECT_FALSE(pipe._isFlowing);
}