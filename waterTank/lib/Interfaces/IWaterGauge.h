#ifndef IWATERGAUGE_H
#define IWATERGAUGE_H

class IWaterGauge {
private:
public:
    virtual void initialize(){};
    virtual void tick(bool valveOpen){};
    virtual bool isEmpty(){return false;};
};

#endif