.section .text
.global irqHigh
.type irqHigh, @function
irqHigh:
    push %eax
    mov $0x20, %al
    #send an EOI to the master and slave PIC
    outb %al, $0xA0
    outb %al, $0x20
    pop %eax
    iret

.global irqLow
.type irqLow, @function
irqLow:
    push %eax
    #send an EOI to the master pic
    mov $0x20, %al
    outb %al, $0x20
    pop %eax
    iret
