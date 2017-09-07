#include "Gdt.hpp"
#include "../../../memory.hpp"

namespace x86 {
    static Gdt gdtInstance;

    Gdt *Gdt::create(void) {
        return &gdtInstance;
    }

    void Gdt::setEntry(int index, uint32_t base, uint32_t limit, Type type, bool longMode) {
        memset(&this->entries[index], 0, sizeof(Entry));
        this->entries[index].baseLow = base & 0xFFFF;
        this->entries[index].baseHighLow = (base >> 16) & 0xFF;
        this->entries[index].baseHighHigh = (base >> 24) & 0xFF;

        this->entries[index].limitLow = limit & 0xFFFF;
        this->entries[index].limitHigh = (limit >> 16) & 0xF;

        this->entries[index].type = static_cast<uint8_t>(type);
        this->entries[index].granularity = 1;
        this->entries[index].longMode = longMode;
        this->entries[index].db = (longMode) ? 0 : 1; //1 for 32 bit segments, 0 for 64 bit
    }

    void Gdt::init(void) {
        Ptr ptr;

        //setup the entries
        this->setEntry(0, 0, 0, Type::Null ,false); //null segment
        this->setEntry(1, 0, 0xFFFFF, Type::CodeR, false); //32 bit code segment
        this->setEntry(2, 0, 0xFFFFF, Type::DataRW, false); //32 bit data segment
        this->setEntry(3, 0, 0xFFFFF, Type::CodeR, true); //32e code segment
        this->setEntry(4, 0, 0xFFFFF, Type::DataRW, true); //32e data segment

        //load the GDT
        ptr.limit = sizeof(Entry) * NumGdtEntries;
        ptr.addr = (uint32_t) &this->entries[0];

        asm volatile(
            "lgdt (%%eax)\n"
            "ljmp $0x08, $loadCS\n"
            "loadCS:\n"
            "mov $0x10, %%ax\n"
            "mov %%ax, %%ds\n"
            "mov %%ax, %%ss\n"
            "mov %%ax, %%es\n"
            "mov %%ax, %%fs\n"
            "mov %%ax, %%gs\n"
            :
            : "a" (&ptr)
        );
    }
}
