#ifndef ISWITCH_H
#define ISWITCH_H

class ISwitch {
public:
    virtual bool isOpen() { return !this->isClosed(); };
    virtual bool isClosed() { return false; };
};

#endif