#ifndef ISR
#define ISR

#include <stdint.h>

struct InterruptState {
    uint32_t gs;
    uint32_t fs;
    uint32_t es;
    uint32_t ss;
    uint32_t ds;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    uint32_t eax;
    uint32_t intNumber;
    uint32_t errorCode;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

extern "C" {
    extern void isr0(void);
    extern void isr1(void);
    extern void isr2(void);
    extern void isr3(void);
    extern void isr4(void);
    extern void isr5(void);
    extern void isr6(void);
    extern void isr7(void);
    extern void isr8(void);
    extern void isr9(void);
    extern void isr10(void);
    extern void isr11(void);
    extern void isr12(void);
    extern void isr13(void);
    extern void isr14(void);
    extern void isr15(void);
    extern void isr16(void);
    extern void isr17(void);
    extern void isr18(void);
    extern void isr19(void);
    extern void isr20(void);
    extern void isr21(void);
    extern void isr22(void);
    extern void isr23(void);
    extern void isr24(void);
    extern void isr25(void);
    extern void isr26(void);
    extern void isr27(void);
    extern void isr28(void);
    extern void isr29(void);
    extern void isr30(void);
    extern void isr31(void);

    void isr(InterruptState&);
}

#endif
