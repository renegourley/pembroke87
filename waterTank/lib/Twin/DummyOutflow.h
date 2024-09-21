#ifndef DUMMYOUTFLOW_H
#define DUMMYOUTFLOW_H

#include "IOutflowPipe.h"
#include "Board.h"

class DummyOutflow : public IOutflowPipe {
private:
public:
    DummyOutflow(){};
    void initialize() override {};
    void tick(bool waterIsFlowing) override {};
};

#endif