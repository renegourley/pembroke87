#include "WaterTower.h"

WaterTower::WaterTower(IWaterGauge* waterGaugePtr, ISwitch* valveSwitchPtr, IOutflowPipe* outflowPipePtr) {
    _waterGaugePtr = waterGaugePtr;
    _valveSwitchPtr = valveSwitchPtr;
    _outflowPipePtr = outflowPipePtr;
}

void WaterTower::initialize(){
    _waterGaugePtr->initialize();
    _outflowPipePtr->initialize();
}

void WaterTower::tick() {
    _waterGaugePtr->tick(_valveSwitchPtr->isClosed());
    _outflowPipePtr->tick(_valveSwitchPtr->isClosed() && !_waterGaugePtr->isEmpty());
}