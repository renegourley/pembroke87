#ifndef OUTFLOWPIPE_H
#define OUTFLOWPIPE_H

#include "Board.h"

class OutflowPipe {
private:
    Board* _boardPtr;
    uint _maxVolume;
    uint _currentVolume;
    int _volumeSteps;
    int _delay;
    int _probabilityOfEasterEgg;
    void setVolume(uint volume);
    uint chooseTrack();
public:
    OutflowPipe(Board* boardPtr, uint maxVolume, int volumeSteps, int delay, int probabilityOfEasterEgg);
    void initialize();
    void start();
    void stop();
};

#endif