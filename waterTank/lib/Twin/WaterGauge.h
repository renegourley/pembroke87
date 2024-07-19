#ifndef WATERGAUGE_H
#define WATERGAUGE_H

#include "ILinearActuator.h"

class WaterGauge {
private:
    int _waterLevel;
    int _actuatorLength;
    int _fillStep;
    ILinearActuator* _actuatorPtr;
public:
    WaterGauge(ILinearActuator* actuatorPtr, int actuatorLength);
    void initialize();
    void tick(bool valveOpen);
    bool isEmpty();
};

#endif