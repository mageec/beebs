/* Copyright (C) 2019 Technical University - Sofia

   Contributor Lubomir Bogdanov <lbogdanov@tu-sofia.bg>

   This file is part of the Bristol/Embecosm Embedded Benchmark Suite.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program. If not, see <http://www.gnu.org/licenses/>. */
#include <stdint.h>

void software_init_hook(void);
static void nmi_handler(void);
static void hard_fault_handler(void);
static void default_int_handler(void);

extern int _stack_ptr;
extern int _etext;
extern int _data;
extern int _edata;
extern int _bss;
extern int _ebss;

extern int main(void);

__attribute__ ((section(".vector_table")))
void (* const vector_table[])(void) = {
    (void (*)(void))((uint32_t)&_stack_ptr),  // The initial stack pointer
    software_init_hook,                       // Reset handler
    nmi_handler,                              // NMI handler
    hard_fault_handler,                       // Hard fault 
    default_int_handler,                      // MPU fault 
    default_int_handler,                      // Bus fault 
    default_int_handler,                      // Usage fault
    0,                                        // Reserved
    0,                                        // Reserved
    0,                                        // Reserved
    0,                                        // Reserved
    default_int_handler,                      // SVCall 
    default_int_handler,                      // Debug monitor
    0,                                        // Reserved
    default_int_handler,                      // PendSV
    default_int_handler,                      // SysTick
    default_int_handler,                      // GPIOA
    default_int_handler,                      // GPIOB
    default_int_handler,                      // GPIOC
    default_int_handler,                      // GPIOD
    default_int_handler,                      // GPIOE
    default_int_handler,                      // UART0
    default_int_handler,                      // UART1
    default_int_handler,                      // SSI0
    default_int_handler,                      // I2C0
    default_int_handler,                      // PWM Fault
    default_int_handler,                      // PWM0
    default_int_handler,                      // PWM1
    default_int_handler,                      // PWM2
    default_int_handler,                      // QEI0
    default_int_handler,                      // ADC0
    default_int_handler,                      // ADC1
    default_int_handler,                      // ADC2
    default_int_handler,                      // ADC3
    default_int_handler,                      // WDT 
    default_int_handler,                      // Timer0_A
    default_int_handler,                      // Timer0_B
    default_int_handler,                      // Timer1_A
    default_int_handler,                      // Timer1_B
    default_int_handler,                      // Timer2_A
    default_int_handler,                      // Timer2_B
    default_int_handler,                      // A_Comp0
    default_int_handler,                      // A_Comp1
    default_int_handler,                      // A_Comp2
    default_int_handler,                      // SC
    default_int_handler,                      // FLASH
    default_int_handler,                      // GPIOF
    default_int_handler,                      // GPIOG
    default_int_handler,                      // GPIOH
    default_int_handler,                      // UART2
    default_int_handler,                      // SSI1
    default_int_handler,                      // Timer3_A
    default_int_handler,                      // Timer3_B
    default_int_handler,                      // I2C1
    default_int_handler,                      // QEI_1
    default_int_handler,                      // CAN0
    default_int_handler,                      // CAN1
    default_int_handler,                      // CAN2
    default_int_handler,                      // Eth
    default_int_handler                       // HIB
};

void software_init_hook(){
    int *src, *dest;

    src = &_etext;
    for(dest = &_data; dest < &_edata; ){
        *dest++ = *src++;
    }

    for(dest = &_bss; dest < &_ebss; ){
        *dest++ = 0x00000000;
    }

    main();

    while(1){ }
}

static void nmi_handler(void){
    while(1){ }
}

static void hard_fault_handler(void){
    while(1){ }
}

static void default_int_handler(void){
    while(1){ }
}

