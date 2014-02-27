    .align 8
    .set nomips16
    .section .boot, "ax"
boot_entry:
    # Jump to _reset
    lui $2, 0x9d00
    add $2, $2, 0x1000

    jr $2
    nop

    .align 8
    .set nomips16
    .section .bootev, "ax"
bootev_entry:
    j boot_entry

    lui $2, 0x9d00
    add $2, $2, 0x1000
    jr $2
    nop

    .section .config0, "a"
    .word 0xFFFFFFFF
    .section .config1, "a"
    .word 0xFFFFFFFF
    .section .config2, "a"
    .word 0xFFFFFFFF
    .section .config3, "a"
    .word 0xFFFFFFFF
