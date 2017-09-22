#ifndef ARCH
#define ARCH

#include "Console.hpp"
#include "PageManager.hpp"
#include "Multiboot2Info.hpp"

class Arch {

public:
    virtual void init(Multiboot2Info&) = 0;
    virtual Console& getConsole(void) = 0;
    virtual PageManager& getPageManager(void) = 0;
    virtual bool isSupported(const char **err) = 0;
    virtual void disableInterrupts(void) = 0;
    virtual void enableInterrupts(void) = 0;
    virtual void halt(void) = 0;
    virtual void enable64Bit(void) = 0;
};
#endif
