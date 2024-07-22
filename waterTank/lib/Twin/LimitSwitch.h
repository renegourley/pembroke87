#ifndef LIMITSWITCH_H
#define LIMITSWITCH_H

#include "Board.h"
#include "ISwitch.h"

class LimitSwitch : public ISwitch {
private:
    Board* _boardPtr;
 
public:
    LimitSwitch(Board* boardPtr);
    bool isClosed() override ;
};

#endif