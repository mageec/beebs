MEMORY
{
  flash (rx) : ORIGIN = 0x08000000, LENGTH = 64K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

__stack = ORIGIN(ram) + LENGTH(ram);

ENTRY(_mainCRTStartup)

SECTIONS
{

    .text :
    {
        *(vectors*)
        *(.text*)      /* Program code */
        *(.rodata*)
        KEEP(*(.init))
        KEEP(*(.fini))
    } >flash

   .bss :
    {
	__bss_start__ = ALIGN(0x8);
    __bss_start = .;
        *(.bss*)       /* Zero-filled run time allocate data memory */
        *(COMMON)
	__bss_end__ = ALIGN(0x8);
    __bss_end = .;
    end = .;
    _end = .;
    __end = .;
    } >ram

    .data :
    {
        __data_start__ = ALIGN(0x8);
        __data_start = .;
        *(.data .data.*)      /* Data memory */
        __data_end__ = ALIGN(0x8);
        __data_end = .;
    } >ram AT >flash
    _data_loadaddr = LOADADDR(.data);


    . = ALIGN(256);

    _start_heap = .;
    PROVIDE( __cs3_heap_start = _start_heap);
}

PROVIDE(end = .);
