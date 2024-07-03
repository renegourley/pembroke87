#ifndef TOWERFLOAT_H
#define TOWERFLOAT_H

#include "ILinearActuator.h"

class WaterGauge {
private:
    int _waterLevel;
    int _actuatorLength;
    ILinearActuator* _actuatorPtr;
public:
    WaterGauge(ILinearActuator* actuatorPtr, int actuatorLength);
    void initialize();
    void tick(bool valveOpen);
};

#endif