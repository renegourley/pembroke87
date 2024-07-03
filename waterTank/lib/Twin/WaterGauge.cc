#include "LimitedLinearActuator.h"

#include "WaterGauge.h"

WaterGauge::WaterGauge(ILinearActuator* actuatorPtr, int actuatorLength) {
    _actuatorLength = actuatorLength;
    _actuatorPtr = actuatorPtr;
}

void WaterGauge::initialize() {
    for (int i=0;i<_actuatorLength;i++) {
        _actuatorPtr->forward();
    }
    _waterLevel = _actuatorLength;
}

void WaterGauge::tick(bool valveOpen) {
    if (valveOpen && _waterLevel > 0) {
        _actuatorPtr->backward();
        _waterLevel -= 1;
    }
    if (!valveOpen && _waterLevel < _actuatorLength) {
        _actuatorPtr->forward();
        _waterLevel += 1;
    }
}