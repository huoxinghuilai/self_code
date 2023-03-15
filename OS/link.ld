ENTRY(Reset)
SECTIONS
{
    . = 0x10000;

    .start . : {
        start.o(.text)
    }

    .text : {
        *(.text)
    }

    .data : {
        *(.data)
    }

    .bss : {
        *(.bss COMMON)
    }

    . = ALIGN(8);
    . = . + 0x1000;      /* 4KB for stack memory */
    stack_top = .;

    . = ALIGN(8);
    mem_addr = .;
}