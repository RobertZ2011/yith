.set MAGIC,    0xE85250D6       # multboot2 magic number
.set ARCH,	   0                # x86 architecture

.set LONG_CS, 0x18
.set LONG_DS, 0x20

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

#structure to pass data to sothoth
sothoth_data:
.skip 8

#used for the far call to sothoth
far_call:
.skip 4 #address
.skip 2 #segment

.extern kmain
.extern _init
.extern _fini

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp
	#pass the data structure to kmain
	push $sothoth_data
	push %ebx
	push %eax

	call _init
	call kmain

	add $12, %esp
	call _fini

	#prepare to call sothoth
	#select the proper segments
	mov $LONG_DS, %ax
	mov %ax, %ds
	mov %ax, %ss
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs

	#pass the data pointer to sothoth
	#first argument is passed in rdi according to system V
	mov $sothoth_data, %edi

	#setup the memory structure for the far call
	#set the code segment
	mov $far_call, %edx
	mov $LONG_CS, %ax
	mov %ax, 4(%edx)

	#set the address
	mov $sothoth_data, %ecx
	mov (%ecx), %eax
	mov %eax, (%edx)

	lcall *(%edx)

	#should never run, add a magic breakpoint and halt the machine
	xchg %bx, %bx
	cli
	hlt
