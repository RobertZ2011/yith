#ifndef GDT
#define GDT

#include <stdint.h>

namespace x86 {
    static const int NumGdtEntries = 5;

    class Gdt {
        struct Entry {
            uint16_t limitLow;
            uint16_t baseLow;
            uint8_t baseHighLow;
            uint8_t type;
            uint8_t limitHigh : 4;
            uint8_t avl : 1;
            uint8_t longMode : 1;
            uint8_t db : 1;
            uint8_t granularity : 1;
            uint8_t baseHighHigh;
        } __attribute__((packed));

        struct Ptr {
            uint16_t limit;
            uint32_t addr;
        } __attribute__((packed));

        enum class Type : uint8_t {
            Null = 0x00,
            DataRW = 0x92,
            CodeR = 0x9A
        };

        Entry entries[NumGdtEntries];

    public:

        static Gdt *create(void);

        void setEntry(int index, uint32_t base, uint32_t limit, Type type, bool longMode);
        void init(void);
    };
}
#endif
