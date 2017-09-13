#ifndef IRQ
#define IRQ

extern "C" {
    extern void irqHigh(void);
    extern void irqLow(void);
}

#endif
