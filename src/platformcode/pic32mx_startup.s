     ;; Copyright (C) 2014 Embecosm Limited and University of Bristol
     ;;
     ;; This file is part of the Bristol/Embecosm Embedded Benchmark Suite.
     ;;
     ;; Contributor: James Pallister <james.pallister@bristol.ac.uk>
     ;;
     ;; This program is free software: you can redistribute it and/or modify
     ;; it under the terms of the GNU General Public License as published by
     ;; the Free Software Foundation, either version 3 of the License, or
     ;; (at your option) any later version.
     ;;
     ;; This program is distributed in the hope that it will be useful,
     ;; but WITHOUT ANY WARRANTY; without even the implied warranty of
     ;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     ;; GNU General Public License for more details.
     ;;
     ;; You should have received a copy of the GNU General Public License
     ;; along with this program.  If not, see <http: //www.gnu.org/licenses/>.

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
