/* Platform header support function for low power benchmarks

   Copyright (C) 2013  Embecosm Limited <info@embecosm.com>

   Contributor James Pallister <james.pallister@embecosm.com>
   Contributor Jeremy Bennett <jeremy.bennett@embecosm.com>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite
   Suite (BEEBS)

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

#ifdef CORTEX_M3
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

#elif defined(CORTEX_M0)

#define ADDR(x)     (*((unsigned long*)(x)))

#define RCC_BASE        0x40021000
#define RCC_AHBENR      ADDR(RCC_BASE + 0x14)

#define RCC_APB2RSTR    ADDR(RCC_BASE + 0xC)
#define RCC_APB1RSTR    ADDR(RCC_BASE + 0x10)
#define RCC_AHBRSTR     ADDR(RCC_BASE + 0x28)

#define GPIOC_BASE      0x48000800
#define GPIOC_MODER     ADDR(GPIOC_BASE + 0x00)
#define GPIOC_OTYPER    ADDR(GPIOC_BASE + 0x04)
#define GPIOC_BSRR      ADDR(GPIOC_BASE + 0x18)

void initialise_trigger()
{
    RCC_AHBENR |= 1<<19;    // Turn on GPIO C

    GPIOC_MODER = 0x01;     // Set GPIOC pin 1 to output
    GPIOC_BSRR = 0x00010000;// Clear bit so pin is pulled low
    GPIOC_BSRR = 0x00000001;// Pull bit high
}

void start_trigger()
{
    GPIOC_BSRR = 0x00000001;// Pull bit high
}

void stop_trigger()
{
    GPIOC_BSRR = 0x00010000;// bit low
}

#elif AVR_ATMEGA
#include <avr/io.h>

void initialise_trigger()
{
    int i, j, k;
    DDRC |= _BV(DDC0);
    PORTC &= ~_BV(PORTC0);

}

void start_trigger()
{
    PORTC |= _BV(PORTC0);
}

void stop_trigger()
{
    PORTC &= ~_BV(PORTC0);
}

#elif AVR_ATXMEGA
#include <avr/io.h>

void initialise_trigger()
{
  PORTA.DIRSET = 1;
  PORTA.OUTCLR = 1;
}

void start_trigger()
{
  PORTA.OUTSET = 1;
}

void stop_trigger()
{
  PORTA.OUTCLR = 1;
}

#elif MSP430FR
#include <msp430fr5739.h>
#define T_PADIR (*(unsigned char volatile*)0x0204)
#define T_PAOUT (*(unsigned char volatile*)0x0202)

void initialise_trigger()
{
  WDTCTL = WDTPW + WDTHOLD;

  T_PAOUT = 0;
  T_PADIR = 0x20; // Pin 1.5
}

void start_trigger()
{
  T_PAOUT = 0x20;
}

void stop_trigger()
{
  T_PAOUT = 0x0;
}


#elif CORTEX_M4

#define ADDR(x)     (*((unsigned long volatile  *)(x)))
#define GPIO_BASE   0x400E1000
#define PM_BASE     0x400E0000
#define SCIF_BASE   0x400E0800

#define GPIOC_BASE  (GPIO_BASE+0x400)
#define GPIOC_GPER  ADDR(GPIOC_BASE)
#define GPIOC_ODER  ADDR(GPIOC_BASE+0x40)
#define GPIOC_OVR   ADDR(GPIOC_BASE+0x50)

#define PM_UNLOCK   ADDR(PM_BASE + 0x58)
#define PM_MCCTL    ADDR(PM_BASE)
#define SCIF_PCLKSR   ADDR(SCIF_BASE + 0x14)
#define SCIF_OSCCTRL0   ADDR(SCIF_BASE + 0x20)


void initialise_trigger ()
{
    // Set the clock to 12MHz external crystal,
    // because the startup oscillator is way slow (115kHz)
    PM_UNLOCK = 0xAA000020;
    // Enable OSC0, startuptime=4, gain=3, mode=external
    SCIF_OSCCTRL0 = 0x00010407;

    while(!(SCIF_PCLKSR&1));    // Wait for OSC0
    PM_UNLOCK = 0xAA000000;
    PM_MCCTL = 1;               // Switch to OSC0

    GPIOC_GPER = 0xFFFFFFFF;
    GPIOC_ODER = 0x1;
    GPIOC_OVR = 0x0;
}

void start_trigger ()
{
    GPIOC_OVR = 0x1;
}

void stop_trigger ()
{
    GPIOC_OVR = 0x0;
}

#elif PIC

#define SFR(addr)   (*((unsigned int volatile*)(addr+0xBF880000)))

#define ANSELA   SFR(0x6000)
#define TRISA    SFR(0x6010)
#define PORTA    SFR(0x6020)

#define TRISB    SFR(0x6110)
#define PORTB    SFR(0x6120)

void initialise_trigger()
{
    PORTA = 0x0;
    TRISA = 0x0;
}

void start_trigger()
{
    PORTA = 0x10;
}

void stop_trigger()
{
    PORTA = 0;
}

void exit(int);
void __real_main();
// The pic32 tools repeatedly call main if it returns.
// This is ...not good, so we call exit after main.
void __wrap_main()
{
  __real_main();
  exit(0);
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
