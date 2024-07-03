#ifndef ILINEARACTUATOR_H
#define ILINEARACTUATOR_H

class ILinearActuator {

public:
    ILinearActuator() {};
    virtual void initialize() {};
    virtual void forward() {};
    virtual void backward() {};
};

#endif