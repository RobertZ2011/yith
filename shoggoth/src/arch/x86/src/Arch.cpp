#include "Arch.hpp"
#include "Gdt.hpp"
#include "Idt.hpp"
#include "PageManager.hpp"

#include <stdint.h>

namespace x86 {
    static Arch instance;

    Arch::Arch(void) {

    }

    Arch& Arch::getInstance(void) {
        return instance;
    }

    void Arch::init(Multiboot2Info& info) {
        Gdt& gdt = Gdt::getInstance();
        Idt& idt = Idt::getInstance();

        this->getConsole().print("Setting up GDT\n");
        gdt.init();

        this->getConsole().print("Setting up IDT\n");
        idt.init(*this);

        this->getConsole().print("Enabling SSE2\n");
        this->enableSSE();

        this->getConsole().print("Enabling interrupts\n");
        this->enableInterrupts();
    }

    ::Console& Arch::getConsole(void) {
        return Console::getInstance();
    }

    ::PageManager& Arch::getPageManager(void) {
        return PageManager::getInstance();
    }

    bool Arch::isSupported(const char **err) {
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

    void Arch::enable64Bit(void) {
        return;
    }

    void Arch::enableSSE(void) {
        asm volatile(
            "mov %cr0, %eax\n"
            "and $0xFFFB, %ax\n"
            "or $0x2, %ax\n"
            "mov %eax, %cr0\n"
            "mov %cr4, %eax\n"
            "or $0x300, %ax\n"
            "mov %eax, %cr4\n"
        );
    }

    uint64_t Arch::readMSR(MSR reg) {
        uint32_t higher;
        uint32_t lower;

        asm volatile(
            "rdmsr" :
            "=d" (higher),
            "=a" (lower):
            "c" (static_cast<uint32_t>(reg))
        );

        return (static_cast<uint64_t>(higher) << 32) | lower;
    }

    void Arch::writeMSR(MSR reg, uint64_t value) {
        uint32_t higher = value >> 32;
        uint32_t lower = value & 0xFFFFFFFF;

        asm volatile(
            "wrmsr" :
            :
            "c" (static_cast<uint32_t>(reg)),
            "d" (higher),
            "a" (lower)
        );
    }

    void Arch::outb(uint16_t port, uint8_t value) {
        asm volatile(
            "outb %%al, %%dx" :
            :
            "a" (value),
            "d" (port)
        );
    }
}
