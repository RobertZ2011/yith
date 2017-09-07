#include "Arch.hpp"
#include "Gdt.hpp"
//#include "IDT.hpp"

#include <stdint.h>

namespace x86 {
    static Arch instance;

    Arch::Arch(void) {

    }

    Arch *Arch::create(void) {
        return &instance;
    }

    void Arch::init(void) {
        Gdt *gdt = Gdt::create();
        //IDT *idt = IDT::create();

        this->getConsole()->print("Setting up GDT");
        gdt->init();
        //idt->init();
    }

    ::Console *Arch::getConsole(void) {
        return Console::create();
    }

    bool Arch::isSupported(char **err) {
        uint32_t highest;

        //get the highest basic function
        asm volatile("cpuid" : "=a"(highest) : "a"(static_cast<uint32_t>(CpuidFunc::HighestFunction)));
        if(highest < static_cast<uint32_t>(CpuidFunc::ExtProcessorInfo)) {
            return false;
        }


        return true;
    }

    void Arch::disableInterrupts(void) {
        asm volatile("cli");
    }

    void Arch::enableInterrupts(void) {
        asm volatile("sti");
    }

    void Arch::halt(void) {
        asm volatile("hlt");
    }
}
