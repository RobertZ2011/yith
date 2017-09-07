#ifndef ARCH
#define ARCH

#include "Console.hpp"

class Arch {

public:
    virtual void init(void) = 0;
    virtual Console *getConsole(void) = 0;
    virtual bool isSupported(char **err) = 0;
    virtual void disableInterrupts(void) = 0;
    virtual void enableInterrupts(void) = 0;
    virtual void halt(void) = 0;
};
#endif
