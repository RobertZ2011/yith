.extern isr

.section .text
.global isr0
.type isr0, @function
isr0:
    pushl $0
    pushl $0
    jmp isr_common

.global isr1
.type isr1, @function
isr1:
    pushl $0
    pushl $1
    jmp isr_common

.global isr2
.type isr2, @function
isr2:
    pushl $0
    pushl $2
    jmp isr_common

.global isr3
.type isr3, @function
isr3:
    pushl $0
    pushl $3
    jmp isr_common

.global isr4
.type isr4, @function
isr4:
    pushl $0
    pushl $4
    jmp isr_common

.global isr5
.type isr5, @function
isr5:
    pushl $0
    pushl $5
    jmp isr_common

.global isr6
.type isr6, @function
isr6:
    pushl $0
    pushl $6
    jmp isr_common

.global isr7
.type isr7, @function
isr7:
    pushl $0
    pushl $7
    jmp isr_common

.global isr8
.type isr8, @function
isr8:
    pushl $8
    jmp isr_common

.global isr9
.type isr9, @function
isr9:
    pushl $0
    pushl $9
    jmp isr_common

.global isr10
.type isr10, @function
isr10:
    pushl $10
    jmp isr_common

.global isr11
.type isr11, @function
isr11:
    pushl $11
    jmp isr_common

.global isr12
.type isr12, @function
isr12:
    pushl $12
    jmp isr_common

.global isr13
.type isr13, @function
isr13:
    pushl $13
    jmp isr_common

.global isr14
.type isr14, @function
isr14:
    pushl $14
    jmp isr_common

.global isr15
.type isr15, @function
isr15:
    pushl $0
    pushl $15
    jmp isr_common

.global isr16
.type isr16, @function
isr16:
    pushl $0
    pushl $16
    jmp isr_common

.global isr17
.type isr17, @function
isr17:
    pushl $17
    jmp isr_common

.global isr18
.type isr18, @function
isr18:
    pushl $0
    pushl $18
    jmp isr_common

.global isr19
.type isr19, @function
isr19:
    pushl $0
    pushl $19
    jmp isr_common

.global isr20
.type isr20, @function
isr20:
    pushl $0
    pushl $20
    jmp isr_common

.global isr21
.type isr21, @function
isr21:
    pushl $0
    pushl $21
    jmp isr_common

.global isr22
.type isr22, @function
isr22:
    pushl $0
    pushl $22
    jmp isr_common

.global isr23
.type isr23, @function
isr23:
    pushl $0
    pushl $23
    jmp isr_common

.global isr24
.type isr24, @function
isr24:
    pushl $0
    pushl $24
    jmp isr_common

.global isr25
.type isr25, @function
isr25:
    pushl $0
    pushl $25
    jmp isr_common

.global isr26
.type isr26, @function
isr26:
    pushl $0
    pushl $26
    jmp isr_common

.global isr27
.type isr27, @function
isr27:
    pushl $0
    pushl $27
    jmp isr_common

.global isr28
.type isr28, @function
isr28:
    pushl $0
    pushl $28
    jmp isr_common

.global isr29
.type isr29, @function
isr29:
    pushl $0
    pushl $29
    jmp isr_common

.global isr30
.type isr30, @function
isr30:
    pushl $0
    pushl $30
    jmp isr_common

.global isr31
.type isr31, @function
isr31:
    pushl $0
    pushl $31
    jmp isr_common

isr_common:
    pusha

    push %ds
    push %ss
    push %es
    push %fs
    push %gs
    push %esp
    call isr
    hlt
