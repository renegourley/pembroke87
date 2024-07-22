#ifndef BOARD_H
#define BOARD_H

#if __GNUC__
#include <stdint.h>
typedef uint32_t uint;
#endif

class Board{

public:
    virtual void writeMotor(int[4]);
    virtual void mp3Play(uint track);
    virtual void mp3Stop();
    virtual void mp3Volume(uint level);
    virtual bool valveSwitchIsClosed();
    virtual bool limitSwitchIsClosed();
    virtual void delayMilliseconds(int milliseconds);
    virtual unsigned long millisecondsSinceBoot();
};

#endif