#ifndef CHIPSUPPORT_H
#define CHIPSUPPORT_H

// Define the registers we need to do a pin toggle ////////////////////////////

#define ADDR(x)     (*((unsigned long*)(x)))

// These registers define clocks, RCC (Reset and clock control)
#define RCC_BASE        0x40021000
#define RCC_AHBENR      ADDR(RCC_BASE + 0x14)

#define GPIOC_BASE      0x48000800
#define GPIOC_MODER     ADDR(GPIOC_BASE + 0x00)
#define GPIOC_BSRR      ADDR(GPIOC_BASE + 0x18)


// Provide a macros to do the pin toggling ////////////////////////////////////

// Initialise the pin + clocks
#define PIN_INIT(number)                \
    do {                                \
        /* Turn on GPIO C Clock */      \
        RCC_AHBENR |= 1<<19;            \
        /* Turn on GPIO C */            \
        GPIOC_MODER |= 1 << number;     \
        /* Pull low GPIO C */           \
        GPIOC_BSRR |= 1 << (number+16); \
    } while(0)

// Set the pin to high
#define PIN_SET(number)                 \
    do {                                \
        /* Pull low GPIO C */           \
        GPIOC_BSRR |= 1 << number;      \
    } while(0)

// Set the pin to low
#define PIN_CLEAR(number)               \
    do {                                \
        /* Pull low GPIO C */           \
        GPIOC_BSRR |= 1 << (number+16); \
    } while(0)

#endif /* CHIPSUPPORT_H */
