.section .text

.extern kmain
.extern _init
.extern _fini

.global _start
.type _start, @function
_start:
    xchg %bx, %bx
    #call _init
    call kmain
    #call _fini
    int $0

    #shouldn't get to this point
    xchg %bx, %bx
    cli
    hlt
