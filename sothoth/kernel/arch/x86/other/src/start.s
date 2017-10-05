.section .text

.extern kmain
.extern _init
.extern _fini

.global _start
.type _start, @function
_start:
    #call _init
    call kmain
    #call _fini

    #shouldn't get to this point, bochs breakpoint and halt
    xchg %bx, %bx
    cli
    hlt
