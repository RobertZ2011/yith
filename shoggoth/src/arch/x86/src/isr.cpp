#include "isr.hpp"
#include "Arch.hpp"
#include "Console.hpp"

static const char *exceptions[] = {
    "Divide Error",
    "Debug Exception",
    "NMI Interrupt", //A case of RAS Syndrome
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode (Undefined Opcode)",
    "Device Not Available (No Math Coprocessor)",
    "Double Fault",
    "Coprocessor Segment Overrun (reserved)",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Reserved",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception"
};

void isr(InterruptState& state) {
    Arch& arch = x86::Arch::getInstance();
    Console& console = arch.getConsole();

    console.setBackground(Console::Color::Black);
    console.setForeground(Console::Color::Red);

    if(state.intNumber <= 20) {
        console.printf("Exception: %x, %s\n", state.intNumber, exceptions[state.intNumber]);
    }
    else {
        console.printf("Exception: %x, Reserved\n", state.intNumber);
    }

    console.printf("eax: %x\tebx: %x\tecx: %x\tedx: %x\n", state.eax, state.ebx, state.ecx, state.edx);
    console.printf("esp: %x\tebp: %x\tesi: %x\tedi: %x\n\n", state.esp, state.ebp, state.esi, state.edi);
    console.printf("cs: %x\tds: %x\tss: %x\n", state.cs, state.ds, state.ss);
    console.printf("es: %x\tfs: %x\tgs: %x\n\n", state.es, state.fs, state.gs);
    console.printf("eip: %x\teflags: %x\n\n", state.eip, state.eflags);

    if(state.intNumber !=14 && state.errorCode != 0) {
        if(state.errorCode & 0xFFF80000) {
            console.printf("Invalid error code: %x\n", state.errorCode);
        }
        else {
            console.printf("Error code: %x\n", state.errorCode);
            if(state.errorCode & 0x1) {
                console.print("\tExternal\n");
            }

            if(state.errorCode & 0x2) {
                console.print("\tIDT entry\n");
            }
            else {
                if(state.errorCode & 0x4) {
                    console.print("\tLDT entry\n");
                }
                else {
                    console.print("\tGDT entry\n");
                }
            }

            console.printf("\tsegment: %x\n", state.errorCode >> 3);
        }
    }
    else {
        console.print((state.errorCode & 0x1) ? "Present\n" : "Not Present\n");
        console.print((state.errorCode & 0x2) ? "Write\n" : "");
        console.print((state.errorCode & 0x4) ? "User mode\n" : "");
        console.print((state.errorCode & 0x8) ? "Reserved bit set\n" : "");
        console.print((state.errorCode & 0x10) ? "Instruction fetch\n" : "");
        console.print((state.errorCode & 0x20) ? "Protection key issue\n" : "");
        console.print((state.errorCode & 0x8000) ? "SGX related\n" : "");
    }

    if(state.intNumber == 14) {
        uint32_t faultAddr;

        asm volatile("mov %%cr2, %0" : "=r"(faultAddr));
        console.printf("Faulting address: %x\n", faultAddr);
    }

    arch.halt();
}
