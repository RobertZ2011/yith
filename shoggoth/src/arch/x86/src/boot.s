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

#structure to pass data to sothoth
sothoth_data:
.skip 8

#used for the far call to sothoth
far_call:
.skip 2 #segment
.skip 4 #address

.extern kmain
.extern _init
.extern _fini

.section .text
.global _start
.type _start, @function
_start:
	mov $stack_top, %esp
	call _init

	#pass the data structure to kmain
	push $sothoth_data
	push %ebx
	push %eax
	call kmain
	call _fini

	#prepare to call sothoth
	#select the proper segments
	mov $0x20, %ax
	mov %ax, %ds
	mov %ax, %ss

	#pass the data pointer to sothoth
	#first argument is passed in rdi according to system V
	mov $sothoth_data, %edi

	#setup the memory structure for the far call
	#set the code segment
	mov $far_call, %edx
	mov $0x16, %ax
	mov %ax, (%edx)

	#set the address
	mov (%ecx), %eax
	mov %eax, 2(%edx)

	#set the segment registers
	mov $0x20, %ax
	mov %ax, %ds
	mov %ax, %ss

	lcall *sothoth_data

	cli
	hlt
