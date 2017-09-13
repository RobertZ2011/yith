#include "Console.hpp"

#include <stdarg.h>

void Console::printf(const char *fmt, ...) {
    va_list args;
    int c;
    uint32_t x;
    char *str;

    va_start(args, fmt);
    while(*fmt) {
        if(*fmt != '%') {
            this->putchar(*fmt);
            fmt++;
            continue;
        }

        fmt++;
        if(!*fmt) {
            break;
        }

        switch(*fmt) {
            case '%':
                this->putchar('%');
                break;

            case 'c':
                c = va_arg(args, int);
                this->putchar((char) c);
                break;

            case 'x':
                x = va_arg(args, uint32_t);
                this->printHex(x, false);
                break;

            case 'X':
                x = va_arg(args, uint32_t);
                this->printHex(x, true);
                break;

            case 's':
                str = va_arg(args, char*);
                this->print(str);
                break;

            default:
                break;
        }

        fmt++;
    }
    va_end(args);
}

void Console::printHex(uint32_t x, bool uppercase) {
    char lower[] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        'a',
        'b',
        'c',
        'd',
        'e',
        'f'
    };
    char upper[] = {
        '0',
        '1',
        '2',
        '3',
        '4',
        '5',
        '6',
        '7',
        '8',
        '9',
        'A',
        'B',
        'C',
        'D',
        'E',
        'F'
    };
    char *set = (uppercase) ? upper : lower;
    uint8_t nibble;

    for(int i = 7; i >= 0; i--) {
        nibble = x >> (i * 4);
        nibble &= 0xF;
        this->putchar(set[nibble]);
    }
}
