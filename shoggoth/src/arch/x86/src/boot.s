.set MAGIC,    0xE85250D6       # multboot2 magic number
.set ARCH,	   0                # x86 architecture

.section .multiboot
.align 4
multiboot_start:
.long MAGIC
.long ARCH
.long -(MAGIC + ARCH + multiboot_end - multiboot_start)
.long (multiboot_end - multiboot_start)

#end tag
.short 0
.short 0
.long 8
multiboot_end:

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.extern kmain
.extern _init
.extern _fini

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp
	call _init
	call kmain
	call _fini
	cli
	hlt
