
#ifdef CORTEX_M0 || CORTEX_M3
    .globl startup
startup:
    ldr r0, =0x20004000
    mov sp, r0
    bl main
exit:
    b exit
    .ltorg
#endif

