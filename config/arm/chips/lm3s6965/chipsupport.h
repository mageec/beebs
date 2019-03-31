/* Chip support for ARM LM3S6965.

   Copyright (C) 2019 Technical University - Sofia

   Contributor Lubomir Bogdanov <lbogdanov@tu-sofia.bg>

   This file is part of BEEBS

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 3 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along with
   this program.  If not, see <http://www.gnu.org/licenses/>.  */

#ifndef CHIPSUPPORT_H
#define CHIPSUPPORT_H

// Define the registers we need to do a pin toggle ////////////////////////////
#define ADDR(x)     (*((unsigned long*)(x)))
#define SYSCTL_GPIO_ENABLE     *(volatile unsigned long *)0x400FE108

#define SYSCTL_GPIOB_MASK      0x0002
#define GPIO_PORTB_DIR         *(volatile unsigned long *)0x40005400 //GPIO Port B direction register base address
#define GPIO_PORTB_DATA        *(volatile unsigned long *)0x400053FC //GPIO Port B data register base address
#define GPIO_PORTB_DIG_PIN     *(volatile unsigned long *)0x4000551C //GPIO Port B digital pin enable register base address
#define GPIO_PINMASK_6         0x40                                  //GPIO pin PB6 mask


// Provide macros to do the pin toggling ////////////////////////////////////

// Initialize the pin + clocks
#define PIN_INIT(number)                                        \
    do {                                                        \
        switch(number){                                         \
        case 6:                                                 \
            /* Turn on GPIO B Clock */                          \
            SYSCTL_GPIO_ENABLE |= SYSCTL_GPIOB_MASK;            \
            /* Do a dummy read to wait for GPIO B ready */      \
            volatile long i = SYSCTL_GPIO_ENABLE;               \
            /* Set as output GPIO PB6 */                        \
            GPIO_PORTB_DIR |= GPIO_PINMASK_6;                   \
            GPIO_PORTB_DIG_PIN |= GPIO_PINMASK_6;               \
            /* Pull low GPIO PB6 */                             \
            GPIO_PORTB_DATA &= ~GPIO_PINMASK_6;                 \
            break;                                              \
        }                                                       \
    } while(0)

// Set the pin to high
#define PIN_SET(number)                         \
    do {                                        \
        switch(number){                         \
        case 6:                                 \
            /* Set PB6 */                       \
            GPIO_PORTB_DATA |= GPIO_PINMASK_6;  \
            break;                              \
        }                                       \
    } while(0)                                  \

// Set the pin to low
#define PIN_CLEAR(number)                       \
    do {                                        \
        switch(number){                         \
        case 6:                                 \
            /* Clear PB6 */                     \
            GPIO_PORTB_DATA &= ~GPIO_PINMASK_6; \
            break;                              \
        }                                       \
    } while(0)                                  \

#endif /* CHIPSUPPORT_H */
