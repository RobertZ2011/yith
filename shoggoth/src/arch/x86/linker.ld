ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	. = 1M;
	.text ALIGN(4K):
	{
		*(.multiboot)
		*(.text)
	}
	.rodata ALIGN(4K):
	{
		*(.rodata)
	}
	.data ALIGN(4K):
	{
		*(.data)
	}
	.bss ALIGN(4K):
	{
		*(COMMON)
		*(.bss)
	}
    kernelEnd = .;
}
