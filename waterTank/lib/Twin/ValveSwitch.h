#ifndef VALVESWITCH_H
#define VALVESWITCH_H

#include "Board.h"
#include "ISwitch.h"

class ValveSwitch : public ISwitch {
private:
    Board* _boardPtr;
 
public:
    ValveSwitch(Board* boardPtr);
    bool isClosed() override ;
};

#endif