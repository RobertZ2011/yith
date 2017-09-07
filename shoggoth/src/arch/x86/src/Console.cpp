#include "Console.hpp"

namespace x86 {
    static Console instance;

    Console::Console(void) {
        this->setForeground(Color::LightGray);
        this->setBackground(Color::Black);
        this->xpos = 0;
        this->ypos = 0;
    }

    Console *Console::create(void) {
        return &instance;
    }

    void Console::setForeground(Color c) {
        this->foreground = c;
    }

    void Console::setBackground(Color c) {
        this->background = c;
    }

    void Console::putchar(char c) {
        uint16_t *ptr = (uint16_t*)0xB8000;
        uint16_t foreground = static_cast<uint8_t>(this->foreground);
        uint16_t background = static_cast<uint8_t>(this->background);

        if(c == '\n') {
            return;
        }

        if(c == '\t') {
            return;
        }

        *(ptr + this->xpos + 80 * this->ypos) = ((foreground | ((background & 0x7) << 4)) << 8) | c;
        this->xpos++;

        if(this->xpos >= 80) {
            this->xpos = 0;
            this->ypos++;
            if(this->ypos >= 25) {

            }
        }
    }

    void Console::print(const char *s) {
        while(*s) {
            this->putchar(*s);
            s++;
        }
    }

    void Console::clear(void) {

    }
}
