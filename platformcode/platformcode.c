/* Platform header support function for low power benchmarks

   Copyright (C) 2013  Embecosm Limited <info@embecosm.com>

   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the low power benchmark

   This program is free software: you can redistribute it and/or modify it
   under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or (at your
   option) any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
   License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#include "platformcode.h"

#ifdef ARM
#define ADDR(x)     (*((unsigned long*)(x)))

#define RCC_BASE        0x40021000
#define RCC_APB2ENR     ADDR(RCC_BASE + 0x18)

#define GPIOC_BASE      0x40011000
#define GPIOC_CRL       ADDR(GPIOC_BASE + 0x00)
#define GPIOC_BSRR      ADDR(GPIOC_BASE + 0x10)


void initialise_trigger()
{
    RCC_APB2ENR |= 1<<4;    // Turn on GPIO C


    GPIOC_CRL = 0x1;

    GPIOC_BSRR = 0x00010000;// Clear bit so pin is pulled low
}

void start_trigger()
{
    GPIOC_BSRR = 0x00000001;// Pull bit high
}

void stop_trigger()
{
    GPIOC_BSRR = 0x00010000;// bit low
}

#else

/* Anything to initialize the trigger. */
void initialise_trigger ()
{
}

/* Anything to start the trigger. */
void start_trigger ()
{
}

/* Anything to stop the trigger. */
void stop_trigger ()
{
}

#endif /* ARM */
