#include "gtest/gtest.h"
typedef uint32_t uint;
#include "IOutflowPipe.h"
#include "ISwitch.h"
#include "IWaterGauge.h"
#include "WaterTower.h"
#include "LimitSwitch.h"
#include "Stepper.h"
#include "LimitedLinearActuator.h"
#include "WaterGauge.h"
#include "ValveSwitch.h"
#include "OutflowPipe.h"
#include "WaterTower.h"

class IntegrationTestBoard : public Board {

public:
    int _motorWriteCount = 0;
    bool _isPlaying = false;
    bool _valveSwitchIsClosed = false;
    bool _limitSwitchIsClosed = false;

    void writeMotor(int pinValues[]) { 
      // do not record a write if the motor is getting turned off
      _motorWriteCount += (pinValues[0]+pinValues[1]+pinValues[2]+pinValues[3]); 
    };
    void mp3Play(uint track) { _isPlaying = true; };
    void mp3Stop() { _isPlaying = false; };
    void mp3Volume(uint level) {};
    bool valveSwitchIsClosed() { return _valveSwitchIsClosed; };
    bool limitSwitchIsClosed() { return _limitSwitchIsClosed; };
    void delayMilliseconds(int milliseconds) {};
    unsigned long millisecondsSinceBoot() { return 123; };};

TEST(IntegrationTests, InitializeDoesNotMoveIfLimitSwitchClosed) {
  IntegrationTestBoard board;
  LimitSwitch limitSwitch(&board);
  Stepper stepper(4, &board);
  LimitedLinearActuator linearActuator(&stepper,&limitSwitch);
  WaterGauge waterGauge(&board, &linearActuator, 10);
  ValveSwitch valveSwitch(&board);
  OutflowPipe outflowPipe(&board, 10, 5, 50, 100);
  WaterTower waterTower(&waterGauge, &valveSwitch, &outflowPipe);
  board._limitSwitchIsClosed = true;
  printf("before first comparison %d\n", board._motorWriteCount);
  EXPECT_EQ(0,board._motorWriteCount); 
  waterTower.initialize();
  printf("before second comparison %d\n", board._motorWriteCount);
  EXPECT_EQ(0,board._motorWriteCount);
  EXPECT_FALSE(board._isPlaying);
}

TEST(IntegrationTests, InitializeGoesToTopAndSilent) {
  IntegrationTestBoard board;
  LimitSwitch limitSwitch(&board);
  Stepper stepper(4, &board);
  LimitedLinearActuator linearActuator(&stepper,&limitSwitch);
  WaterGauge waterGauge(&board, &linearActuator, 10);
  ValveSwitch valveSwitch(&board);
  OutflowPipe outflowPipe(&board, 10, 5, 50, 100);
  WaterTower waterTower(&waterGauge, &valveSwitch, &outflowPipe);
  waterTower.initialize();
  EXPECT_EQ(10,board._motorWriteCount); // Stepper initialization
  EXPECT_FALSE(board._isPlaying);
}

TEST(IntegrationTests, TickMovesActuatorAndPlaySoundWhenValveSwitchClosed) {
  IntegrationTestBoard board;
  LimitSwitch limitSwitch(&board);
  Stepper stepper(4, &board);
  LimitedLinearActuator linearActuator(&stepper,&limitSwitch);
  WaterGauge waterGauge(&board, &linearActuator, 10);
  ValveSwitch valveSwitch(&board);
  OutflowPipe outflowPipe(&board, 10, 5, 50, 100);
  WaterTower waterTower(&waterGauge, &valveSwitch, &outflowPipe);
  board._limitSwitchIsClosed = true;
  waterTower.initialize();
  board._valveSwitchIsClosed = true;
  waterTower.tick();
  EXPECT_EQ(1,board._motorWriteCount); //Stepper initialization, down
  EXPECT_TRUE(board._isPlaying);
  board._limitSwitchIsClosed = false;
  board._valveSwitchIsClosed = false;
  waterTower.tick();
  EXPECT_FALSE(board._isPlaying);
  EXPECT_FALSE(waterGauge.isEmpty());
  waterTower.tick();
  waterTower.tick();
  waterTower.tick();
  waterTower.tick();
  EXPECT_EQ(2,board._motorWriteCount); //Stepper initialization, down, up
}

