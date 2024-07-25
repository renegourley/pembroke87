#ifndef ISTEPPER_H
#define ISTEPPER_H

class IStepper {
public:
    virtual void step(bool = true) {};
    virtual void turnOff() {};
};

#endif