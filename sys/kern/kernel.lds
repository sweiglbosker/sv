OUTPUT_ARCH(riscv)
ENTRY(_start)

SECTIONS
{
        . = LOAD_ADDR;
        . = ALIGN(PAGE_SIZE);

        .text :
        {
                PROVIDE(__text_start = .);
                *(.text.init)
                *(.text .text.*)
                . = ALIGN(8);
                PROVIDE(__text_end = .);
        }
        . = ALIGN(PAGE_SIZE);

        PROVIDE(__global_pointer$ = .);

        .rodata :
        {
                PROVIDE(__rodata_start = .);
                *(.rodata .rodata.*)
                . = ALIGN(8);
                PROVIDE(__rodata_end = .); 
        }

        . = ALIGN(PAGE_SIZE);

        .data : 
        {
                PROVIDE(__data_start = .);
                *(.sdata .sdata.*) 
                *(.data .data.*)
                *(.readmostly.data)
                *(*.data)
                . = ALIGN(8);
                PROVIDE(__data_end = .);
        }

        . = ALIGN(PAGE_SIZE); 

	.bss :
	{
		PROVIDE(__bss_start = .);
		*(.sbss .sbss.*)
		*(.bss .bss.*)
		. = ALIGN(8);
		PROVIDE(__bss_end = .);
	}

	. = ALIGN(PAGE_SIZE);

        PROVIDE(__stack_start = .);
        PROVIDE(__stack_end = __stack_start + (PAGE_SIZE * NPROC));
        PROVIDE(__heap_start = __stack_end);
}
