#ifndef CONSOLE
#define CONSOLE

#include <stdint.h>

class Console {

public:
    //obviously this favors good old 0xB8000 on IBM compatible PCs, but I'm not
    //too concerned about it, I doubt that this project will ever become big,
    //at most I plan to port it to a raspberry pi and conversion can be done
    //with a simple lookup table
    enum class Color : uint8_t {
        Black = 0,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Brown,
        LightGray,
        DarkGray,
        LightBlue,
        LightGreen,
        LightCyan,
        LightRed,
        LightMagenta,
        Yellow,
        White
    };

    virtual void setForeground(Color) = 0;
    virtual void setBackground(Color) = 0;

    virtual void putchar(char c) = 0;
    virtual void print(const char *s) = 0;
    virtual void clear(void) = 0;

    void printf(const char *fmt, ...);
    void printHex(uint32_t x, bool uppercase);
};
#endif
