#ifndef OUTFLOWPIPE_H
#define OUTFLOWPIPE_H

#include "IOutflowPipe.h"
#include "Board.h"

class OutflowPipe : public IOutflowPipe {
private:
    Board* _boardPtr;
    uint _maxVolume;
    uint _currentVolume;
    int _volumeSteps;
    int _delay;
    int _probabilityOfEasterEgg;
    bool _isPlaying;
    void setVolume(uint volume);
    uint chooseTrack();
    void start();
    void stop();
public:
    OutflowPipe(Board* boardPtr, uint maxVolume, int volumeSteps, int delay, int probabilityOfEasterEgg);
    void initialize() override;
    void tick(bool waterIsFlowing) override;
};

#endif