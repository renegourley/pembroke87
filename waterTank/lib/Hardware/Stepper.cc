  #include "Stepper.h"
  
Stepper::Stepper(int pinCount, Board* boardPtr) {
    _out = 0x08;
    _pinCount = pinCount;
    _boardPtr = boardPtr;
    int pins[] = {0,0,0,0};
    boardPtr->writeMotor(pins);
}

void Stepper::step(bool forward) {
    if (forward) {
        // ring shift left
        _out != 0x08 ? _out = _out << 1 : _out = 0x01;
    }
    else {
        // ring shift right
        _out != 0x01 ? _out = _out >> 1 : _out = 0x08;
    }

    int pins[] = {0,0,0,0};
    for (int i = 0; i < _pinCount; i++) {
        int value = (_out & (0x01 << i)) ? 1 : 0;
        pins[i] = value;
    }
    _boardPtr->writeMotor(pins);
}
