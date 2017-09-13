#include "Idt.hpp"
#include "isr.hpp"
#include "irq.hpp"
#include "../../../memory.hpp"

namespace x86 {
    static Idt idt;

    Idt& Idt::getInstance() {
        return idt;
    }

    void Idt::setEntry(int index, void (*isr)(void)) {
        uint32_t addr = (uint32_t) isr;

        memset<uint8_t>(&this->entries[index], 0, sizeof(Entry));
        this->entries[index].offsetLow = addr & 0xFFFF;
        this->entries[index].offsetHigh = addr >> 16;
        this->entries[index].segment = 0x08;
        this->entries[index].type = 0x8E;
    }

    void Idt::init(Arch& arch) {
        volatile Ptr ptr;

        this->setEntry(0, &isr0);
        this->setEntry(1, &isr1);
        this->setEntry(2, &isr2);
        this->setEntry(3, &isr3);
        this->setEntry(4, &isr4);
        this->setEntry(5, &isr5);
        this->setEntry(6, &isr6);
        this->setEntry(7, &isr7);
        this->setEntry(8, &isr8);
        this->setEntry(9, &isr9);
        this->setEntry(10, &isr10);
        this->setEntry(11, &isr11);
        this->setEntry(12, &isr12);
        this->setEntry(13, &isr13);
        this->setEntry(14, &isr14);
        this->setEntry(15, &isr15);
        this->setEntry(16, &isr16);
        this->setEntry(17, &isr7);
        this->setEntry(18, &isr18);
        this->setEntry(19, &isr19);
        this->setEntry(20, &isr20);
        this->setEntry(21, &isr21);
        this->setEntry(22, &isr22);
        this->setEntry(23, &isr23);
        this->setEntry(24, &isr24);
        this->setEntry(25, &isr25);
        this->setEntry(26, &isr26);
        this->setEntry(27, &isr27);
        this->setEntry(28, &isr28);
        this->setEntry(29, &isr29);
        this->setEntry(30, &isr30);
        this->setEntry(31, &isr31);

        //remap the PIC
        arch.getConsole().print("Remapping PIC\n");

        arch.outb(0x20, 0x11);
        arch.outb(0xA0, 0x11);

        //remap
        arch.outb(0x21, 0x20);
        arch.outb(0xA1, 0x28);

        //setup cascading
        arch.outb(0x21, 0x04);
        arch.outb(0xA1, 0x02);

        arch.outb(0x21, 0x01);
        arch.outb(0xA1, 0x01);

        arch.outb(0x21, 0x00);
        arch.outb(0xA1, 0x00);

        //disable the PIC
        arch.getConsole().print("Disabling PIC\n");
        arch.outb(0xA1, 0xFF);
        arch.outb(0x21, 0xFF);

        //setup dummy irq handlers
        for(int count = 0; count < 8; count++) {
            this->setEntry(count + 32, &irqLow);
        }

        for(int count = 0; count < 8; count++) {
            this->setEntry(count + 40, &irqHigh);
        }

        ptr.limit = sizeof(Entry) * 48;
        ptr.addr = (uint32_t) &this->entries[0];

        asm volatile("lidt (%%eax)" : : "a"(&ptr));
    }
}
