#include "OutflowPipe.h"

OutflowPipe::OutflowPipe(Board* boardPtr, uint maxVolume, int volumeSteps, int delay, int probabilityOfEasterEgg) {
    _boardPtr = boardPtr;
    _maxVolume = maxVolume;
    _volumeSteps = volumeSteps;
    _delay = delay;
    _probabilityOfEasterEgg = probabilityOfEasterEgg;
}

void OutflowPipe::initialize() {
    _boardPtr->mp3Volume(0);
    _currentVolume = 0;
    _boardPtr->mp3Stop();
    _isPlaying = false;
}

void OutflowPipe::tick(bool waterIsFlowing) {
    (waterIsFlowing) ? this->start() : this->stop();
}

void OutflowPipe::start() {
    if (_isPlaying) return;

    _boardPtr->mp3Play(chooseTrack());
    _isPlaying = true;
    for (int i=0;i<=_volumeSteps;i++) {
        setVolume(_maxVolume*i/_volumeSteps);
        _boardPtr->delayMilliseconds(_delay);
    }
}

void OutflowPipe::stop() {
    if (!_isPlaying) return;

    for (int i=_volumeSteps;i>=0;i--) {
        setVolume(_maxVolume*i/_volumeSteps);
        _boardPtr->delayMilliseconds(_delay);
    }
    _boardPtr->mp3Stop();
    _isPlaying = false;
}

void OutflowPipe::setVolume(uint volume) {
    _boardPtr->mp3Volume(volume);
    _currentVolume = volume;
}

uint OutflowPipe::chooseTrack() {
    if (0 == _boardPtr->millisecondsSinceBoot()%_probabilityOfEasterEgg) 
        return 2;
    else
        return 1;
}