#ifndef IDT
#define IDT

#include <stdint.h>
#include "Arch.hpp"

namespace x86 {
    class Idt {
        struct Entry {
            uint16_t offsetLow;
            uint16_t segment;
            uint8_t reserved;
            uint8_t type;
            uint16_t offsetHigh;

        } __attribute__((packed));

        static_assert(sizeof(Entry) == 8, "IDT Entry is not 64 bits");

        struct Ptr {
            uint16_t limit;
            uint32_t addr;
        } __attribute__((packed));

        static_assert(sizeof(Ptr) == 6, "IDT Ptr is not 48 bits");

        Entry entries[48];

    public:
        static Idt& getInstance(void);

        void setEntry(int, void (*)(void));
        void init(Arch& arch);
    };
}
#endif
