#ifndef WATERGAUGE_H
#define WATERGAUGE_H

#include "IWaterGauge.h"
#include "ILinearActuator.h"
#include "Board.h"

class WaterGauge : public IWaterGauge {
private:
    int _waterLevel;
    int _actuatorLength;
    int _fillStep;
    ILinearActuator* _actuatorPtr;
    Board* _boardPtr;
public:
    WaterGauge(Board* boardPtr, ILinearActuator* actuatorPtr, int actuatorLength);
    void initialize() override;
    void tick(bool valveOpen) override;
    bool isEmpty();
};

#endif