     ;; Copyright (C) 2013 Embecosm Limited and University of Bristol
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

