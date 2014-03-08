#include <string.h>

extern unsigned char __data_start__;
extern unsigned char __data_end__;
extern unsigned char _data_loadaddr;

extern unsigned char __bss_start__;
extern unsigned char __bss_end__;

void software_init_hook()
{
    memcpy(&__data_start__, &_data_loadaddr , (unsigned)&__data_end__ - (unsigned)&__data_start__);
}
