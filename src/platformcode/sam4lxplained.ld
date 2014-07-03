MEMORY
{
  flash (rx) : ORIGIN = 0x00000000, LENGTH = 256K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
}

__stack = ORIGIN(ram) + LENGTH(ram);

ENTRY(_mainCRTStartup)

SECTIONS
{
    .isr_vector :
    {
    . = ALIGN(4);
        KEEP(*(.isr_vector))            /* Startup code */
    . = ALIGN(4);
    } >flash

    .text :
    {
        *(vectors*)
        *(.text*)      /* Programcode */
        . = ALIGN(4);
        *(.rodata*)
        . = ALIGN(4);
    } >flash

    .preinit_array : {
        . = ALIGN(4);
        __preinit_array_start = .;
        KEEP (*(.preinit_array))
        __preinit_array_end = .;
    } >flash
    .init_array : {
        . = ALIGN(4);
        __init_array_start = .;
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array))
        __init_array_end = .;
    } >flash
    .fini_array : {
        . = ALIGN(4);
        __fini_array_start = .;
        KEEP (*(.fini_array))
        KEEP (*(SORT(.fini_array.*)))
        __fini_array_end = .;
    } >flash

    .data :
    {
        __data_start__ = .;
        __data_start = .;
        *(.data .data.*)      /* Data memory */
        __data_end__ = .;
        __data_end = .;
    } >ram AT >flash
    _data_loadaddr = LOADADDR(.data);
    . = ALIGN(256);

   .bss :
    {
    __bss_start__ = ALIGN(0x8);
        *(.bss*)       /* Zero-filled run time allocate data memory */
        *(COMMON)
    __bss_end__ = .;
    } >ram

    _start_heap = .;
    PROVIDE(_start_heap = .);
    PROVIDE( __cs3_heap_start = _start_heap);
}

PROVIDE(end = .);
