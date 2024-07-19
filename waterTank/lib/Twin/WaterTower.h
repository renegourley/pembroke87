#ifndef WATERTOWER_H
#define WATERTOWER_H

#include "IWaterGauge.h"
#include "ISwitch.h"
#include "IOutflowPipe.h"

class WaterTower {
private:
    IWaterGauge* _waterGaugePtr;
    ISwitch* _valveSwitchPtr;
    IOutflowPipe* _outflowPipePtr;    
public:
    WaterTower(IWaterGauge* waterGaugePtr, ISwitch* valveSwitchPtr, IOutflowPipe* outflowPipePtr);
    void initialize();
    void tick();
};

#endif