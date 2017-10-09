.section .bss
.align 64
saved_state:
.skip 512

.section .text

.macro isr number, err=0
.global isr\number
.type isr\number, @function
isr\number :
.if \err == 0
    push $0
.endif
    push $\number
    jmp isr_common
.endm

.macro isrFill start, end
.if \end-\start
isr "(\start+1)",end
.endif
.endm

isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isr 8, 1
isr 9
isr 10, 1
isr 11, 1
isr 12, 1
isr 13, 1
isr 14, 1
isr 15
isr 16
isr 17, 1
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31

.extern isr_handler

isr_common:
    push %rsp
    push %rbp
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rdi
    push %rsi
    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov %ds, %rax
    push %rax

    mov %ss, %rax
    push %rax

    mov %es, %rax
    push %rax

    push %fs
    push %gs

    movabs $saved_state, %rax
    push %rax
    fxsave64 (%rax)

    mov %cr0, %rax
    push %rax

    mov %cr2, %rax
    push %rax

    mov %cr3, %rax
    push %rax

    mov %cr4, %rax
    push %rax

    mov %rsp, %rdi

    call isr_handler

    pop %rax
    mov %rax, %cr4

    pop %rax
    mov %rax, %cr3

    pop %rax

    pop %rax
    mov %rax, %cr0

    pop %rax
    fxrstor64 (%rax)

    pop %gs
    pop %fs

    pop %rax
    mov %ax, %es

    pop %rax
    mov %ax, %ss

    pop %rax
    mov %ax, %ds

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8
    pop %rsi
    pop %rdi
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax

    iretq
