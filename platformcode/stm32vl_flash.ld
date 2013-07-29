MEMORY
{
  flash (rx) : ORIGIN = 0x08000000, LENGTH = 64K
  ram (rwx) : ORIGIN = 0x20000000, LENGTH = 8K
}

__stack = ORIGIN(ram) + LENGTH(ram);

SECTIONS
{

    .text :
    {
        *(vectors*)
        *(.text*)      /* Program code */
        *(.rodata*)
    } >flash

   .bss :
    {
	__bss_start__ = ALIGN(0x8);
    __bss_start = .;
        *(.bss*)       /* Zero-filled run time allocate data memory */
	__bss_end__ = .;
    __bss_end = .;
    end = .;
    _end = .;
    __end = .;
    } >ram

    .data :
    {
        __data_start__ = .;
        __data_start = .;
        *(.data .data.*)      /* Data memory */
        __data_end__ = .;
        __data_end = .;
    } >ram

    . = ALIGN(256);

    _start_heap = .;
    PROVIDE( __cs3_heap_start = _start_heap);
}

PROVIDE(end = .);
