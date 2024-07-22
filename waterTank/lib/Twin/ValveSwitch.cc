#include "ValveSwitch.h"

ValveSwitch::ValveSwitch(Board* boardPtr) {
    _boardPtr = boardPtr;
}

bool ValveSwitch::isClosed() {
    return _boardPtr->valveSwitchIsClosed();
}