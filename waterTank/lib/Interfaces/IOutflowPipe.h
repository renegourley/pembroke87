#ifndef IOUTFLOWPIPE_H
#define IOUTFLOWPIPE_H

class IOutflowPipe {
private:
public:
    virtual void initialize(){};
    virtual void tick(bool waterIsFlowing){};
};

#endif