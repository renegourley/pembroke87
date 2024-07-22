#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(Board* boardPtr) {
    _boardPtr = boardPtr;
}

bool LimitSwitch::isClosed() {
    return _boardPtr->limitSwitchIsClosed();
}