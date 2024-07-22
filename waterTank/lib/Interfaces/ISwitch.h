#ifndef ISWITCH_H
#define ISWITCH_H

class ISwitch {
public:
    bool isOpen() { return !this->isClosed(); };
    virtual bool isClosed() { return false; };
};

#endif