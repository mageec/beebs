/* Copyright (C) 2013-2014 Embecosm Limited and University of Bristol

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   Contributor: James Pallister <james.pallister@bristol.ac.uk>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http: //www.gnu.org/licenses/>.  */

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
    } >flash

   .bss :
    {
	__bss_start__ = ALIGN(0x8);
    __bss_start = .;
        *(.bss*)       /* Zero-filled run time allocate data memory */
        *(COMMON)
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
    } >ram AT >flash
    _data_loadaddr = LOADADDR(.data);


    . = ALIGN(256);

    _start_heap = .;
    PROVIDE( __cs3_heap_start = _start_heap);
}

PROVIDE(end = .);
