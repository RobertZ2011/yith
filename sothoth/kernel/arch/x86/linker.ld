ENTRY(_start)

SECTIONS
{
	. = 0xF7FE0000; /* 2MB aligned */
	.text ALIGN(2M):
	{
		text_start = . ;
		*(.text)
		text_end = . ;
	}
	.rodata ALIGN(2M):
	{
		*(.rodata)
	}
	.data ALIGN(2M):
	{
		*(.data)
	}
	.bss ALIGN(2M):
	{
		*(COMMON)
		*(.bss)
	}

	kernel_end = . ;
}
