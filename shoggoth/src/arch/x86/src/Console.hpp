#ifndef CONSOLE_X86
#define CONSOLE_X86

#include <stdint.h>
#include "../../../Console.hpp"

namespace x86 {
    class Console : public ::Console {
        Color foreground;
        Color background;
        uint8_t xpos;
        uint8_t ypos;

    public:
        Console(void);

        static Console *create(void);

        void setForeground(Color);
        void setBackground(Color);

        void putchar(char c);
        void print(const char *s);
        void clear(void);
    };
}
#endif
