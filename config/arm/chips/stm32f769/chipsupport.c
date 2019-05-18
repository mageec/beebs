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
#include "chipsupport.h"

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
    (void (*)(void))((uint32_t)&_stack_ptr),// The initial stack pointer                                            
    software_init_hook,                     // The reset handler
    nmi_handler,                            // The NMI handler
    hard_fault_handler,                     // The hard fault handler
    default_int_handler,                    // The MPU fault handler
    default_int_handler,                    // The bus fault handler
    default_int_handler,                    // The usage fault handler
    0,                                  /* Reserved                                                            */
    0,                                  /* Reserved                                                            */
    0,                                  /* Reserved                                                            */
    0,                                  /* Reserved                                                            */
    default_int_handler,                /* SVC handler                                                         */
    default_int_handler,                /* DebugMon handler                                                    */ 
    0,                                  /* Reserved                                                            */
    default_int_handler,                /* PendSV handler                                                      */
    default_int_handler,                /* SysTick handler                                                     */
    default_int_handler,                /* Window Watchdog interrupt                                           */
    default_int_handler,               	/* PVD through EXTI line detection                                     */
    default_int_handler,        	/* Tamper and TimeStamp interrupts through the EXTI line               */
    default_int_handler,          	/* RTC Tamper or TimeStamp /CSS on LSE through EXTI line 19 interrupts */
    default_int_handler,             	/* Flash global interrupt                                              */
    default_int_handler,               	/* RCC global interrupt                                                */
    default_int_handler,             	/* EXTI Line0 interrupt                                                */
    default_int_handler,            	/* EXTI Line1 interrupt                                                */
    default_int_handler,             	/* EXTI Line2 interrupt                                                */
    default_int_handler,            	/* EXTI Line3 interrupt                                                */
    default_int_handler,             	/* EXTI Line4 interrupt                                                */
    default_int_handler,      		/* DMA1 Stream0 global interrupt                                       */
    default_int_handler,      		/* DMA1 Stream1 global interrupt                                       */
    default_int_handler,      		/* DMA1 Stream2 global interrupt                                       */
    default_int_handler,     		/* DMA1 Stream3 global interrupt                                       */
    default_int_handler,     		/* DMA1 Stream4 global interrupt                                       */
    default_int_handler,     		/* DMA1 Stream5 global interrupt                                       */
    default_int_handler,     		/* DMA1 Stream6 global interrupt                                       */
    default_int_handler,               	/* ADC1 global interrupt                                               */
    default_int_handler,           	/* CAN1 TX interrupts                                                  */
    default_int_handler,          	/* CAN1 RX0 interrupts                                                 */
    default_int_handler,         	/* CAN1 RX1 interrupts                                                 */
    default_int_handler,         	/* CAN1 SCE interrupt                                                  */
    default_int_handler,         	/* EXTI Line[9:5] interrupts                                           */
    default_int_handler,     		/* TIM1 Break interrupt and TIM9 global interrupt                      */
    0,                            	/* Reserved                                                            */
    default_int_handler,		/* TIM1 Trigger and Commutation interrupts and TIM11 global interrupt  */
    0,                            	/* Reserved                                                            */
    default_int_handler,              	/* TIM2 global interrupt                                               */
    default_int_handler,              	/* TIM3 global interrupt                                               */
    default_int_handler,              	/* TIM4 global interrupt                                               */
    default_int_handler,           	/* I2C1 event interrupt                                                */
    default_int_handler,           	/* I2C1 error interrupt                                                */
    0,                            	/* Reserved                                                            */
    0,                            	/* Reserved                                                            */
    default_int_handler,              	/* SPI1 global interrupt                                               */
    default_int_handler,              	/* SPI2 global interrupt                                               */
    default_int_handler,            	/* USART1 global interrupt                                             */
    default_int_handler,            	/* USART2 global interrupt                                             */
    default_int_handler,            	/* USART3 global interrupt                                             */
    default_int_handler,         	/* EXTI Line[15:10] interrupts                                         */
    default_int_handler,         	/* RTC alarms through EXTI line 18 interrupts                          */
    default_int_handler,       		/* USB On-The-Go FS Wakeup through EXTI line interrupt                 */
    default_int_handler,    		/* TIM8 Break interrupt and TIM12 global interrupt                     */
    default_int_handler,     		/* TIM8 Update interrupt and TIM13 global interrupt                    */
    default_int_handler,		/* TIM8 Trigger and Commutation interrupts and TIM14 global interrupt  */
    default_int_handler,          	/* TIM8 Capture Compare interrupt                                      */
    default_int_handler,    		/* DMA1 Stream7 global interrupt                                       */
    default_int_handler,           	/* FMC global interrupt                                                */
    default_int_handler,         	/* SDMMC1 global interrupt                                             */
    default_int_handler,           	/* TIM5 global interrupt                                               */
    default_int_handler,              	/* SPI3 global interrupt                                               */
    default_int_handler,             	/* UART4 global interrupt                                              */
    default_int_handler,             	/* UART5 global interrupt                                              */
    default_int_handler,          	/* TIM6 global interrupt, DAC1 and DAC2 underrun error interrupt       */
    default_int_handler,              	/* TIM7 global interrupt                                               */
    default_int_handler,      		/* DMA2 Stream0 global interrupt                                       */
    default_int_handler,      		/* DMA2 Stream1 global interrupt                                       */
    default_int_handler,      		/* DMA2 Stream2 global interrupt                                       */
    default_int_handler,      		/* DMA2 Stream3 global interrupt                                       */
    default_int_handler,      		/* DMA2 Stream4 global interrupt                                       */
    default_int_handler,               	/* Ethernet global interrupt                                           */
    default_int_handler,          	/* Ethernet Wakeup through EXTI line                                   */
    default_int_handler,           	/* CAN2 TX interrupts                                                  */
    default_int_handler,          	/* CAN2 RX0 interrupts                                                 */
    default_int_handler,          	/* CAN2 RX1 interrupts                                                 */
    default_int_handler,          	/* CAN2 SCE interrupt                                                  */
    default_int_handler,            	/* USB On The Go FS global interrupt                                   */
    default_int_handler,      		/* DMA2 Stream5 global interrupt                                       */
    default_int_handler,      		/* DMA2 Stream6 global interrupt                                       */
    default_int_handler,      		/* DMA2 Stream7 global interrupt                                       */
    default_int_handler,            	/* USART6 global interrupt                                             */
    default_int_handler,           	/* I2C3 event interrupt                                                */
    default_int_handler,           	/* I2C3 error interrupt                                                */
    default_int_handler,    		/* USB On The Go HS End Point 1 Out global interrupt                   */
    default_int_handler,     		/* USB On The Go HS End Point 1 In global interrupt                    */
    default_int_handler,       		/* USB On The Go HS Wakeup through EXTI interrupt                      */
    default_int_handler,            	/* USB On The Go HS global interrupt                                   */
    default_int_handler,              	/* DCMI global interrupt                                               */
    0,                            	/* Reserved                                                            */
    default_int_handler,          	/* Hash and Rng global interrupt                                       */
    default_int_handler,               	/* Floating point unit interrupt                                       */
    default_int_handler,             	/* UART 7 global interrupt                                             */
    default_int_handler,             	/* UART 8 global interrupt                                             */
    default_int_handler,              	/* SPI 4 global interrupt                                              */
    default_int_handler,              	/* SPI 5 global interrupt                                              */
    default_int_handler,              	/* SPI 6 global interrupt                                              */
    default_int_handler,              	/* SAI1 global interrupt                                               */
    default_int_handler,           	/* LTDC global interrupt                                               */
    default_int_handler,           	/* LCD-TFT global Error interrupt                                      */
    default_int_handler,             	/* DMA2D global interrupt                                              */
    default_int_handler,              	/* SAI2 global interrupt                                               */
    default_int_handler,           	/* QuadSPI global interrupt                                            */
    default_int_handler,          	/* LP Timer1 global interrupt                                          */
    default_int_handler,          	/* HDMI-CEC global interrupt                                           */
    default_int_handler,           	/* I2C4 event interrupt                                                */
    default_int_handler,           	/* I2C4 Error interrupt                                                */
    default_int_handler,           	/* SPDIFRX global interrupt                                            */
    default_int_handler,           	/* DSI host global interrupt                                           */
    default_int_handler,       		/* DFSDM1 Filter 0 global interrupt                                    */
    default_int_handler,       		/* DFSDM1 Filter 1 global interrupt                                    */
    default_int_handler,       		/* DFSDM1 Filter 2 global interrupt                                    */
    default_int_handler,       		/* DFSDM1 Filter 3 global interrupt                                    */
    default_int_handler,            	/* SDMMC2 global interrupt                                             */
    default_int_handler,           	/* CAN3 TX interrupt                                                   */
    default_int_handler,          	/* CAN3 RX0 interrupt                                                  */
    default_int_handler,          	/* CAN3 RX1 interrupt                                                  */
    default_int_handler,          	/* CAN3 SCE interrupt                                                  */
    default_int_handler,              	/* JPEG global interrupt                                               */
    default_int_handler             	/* MDIO slave global interrupt                                         */
}; 

/*!
   \brief Sets CPU frequency to 216 MHz, enables icache and dcache, configures flash for 
          high-speed operation, uses external 25MHz input for the HSE module to feed the PLL.
          This function also enables the FPU. 
   
   \param None.
   \return None.
*/
void init_mcu(void){
	/* FPU settings ------------------------------------------------------------*/
	SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */

	/* Reset the RCC clock configuration to the default reset state ------------*/
	/* Set HSION bit */
	RCC->CR |= (uint32_t)0x00000001;

	/* Reset CFGR register */
	RCC->CFGR = 0x00000000;

	/* Reset HSEON, CSSON and PLLON bits */
	RCC->CR &= (uint32_t)0xFEF6FFFF;

	/* Reset PLLCFGR register */
	RCC->PLLCFGR = 0x24003010;

	/* Reset HSEBYP bit */
	RCC->CR &= (uint32_t)0xFFFBFFFF;

	/* Disable all interrupts */
	RCC->CIR = 0x00000000;

	/* Enable I-Cache */
	__DSB();
	__ISB();
	SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
	__DSB();
	__ISB();
	SCB->CCR |=  (uint32_t)SCB_CCR_IC_Msk;  /* enable I-Cache */
	__DSB();
	__ISB();

	uint32_t ccsidr;
	uint32_t sets;
	uint32_t ways;
	/* Enable D-Cache */
	SCB->CSSELR = 0U; /*(0U << 1U) | 0U;*/  /* Level 1 data cache */
	__DSB();
	ccsidr = SCB->CCSIDR;
	/* invalidate D-Cache */
	sets = (uint32_t)(CCSIDR_SETS(ccsidr));
	do {
	   ways = (uint32_t)(CCSIDR_WAYS(ccsidr));
	   do {
	     SCB->DCISW = (((sets << 5) & SCB_DCISW_SET_Msk) |
	                   ((ways << 30) & SCB_DCISW_WAY_Msk)  );
	   } while (ways-- != 0U);
	} while(sets-- != 0U);
	__DSB();
	SCB->CCR |=  (uint32_t)SCB_CCR_DC_Msk;  /* enable D-Cache */
	__DSB();
	__ISB();

	/*Enable the FLASH Adaptive Real-Time memory accelerator.*/
	SET_BIT(FLASH->ACR, FLASH_ACR_ARTEN);
	/*Enable the FLASH prefetch buffer.*/
	FLASH->ACR |= FLASH_ACR_PRFTEN;

	/* Enable Power Control clock */
	__IO uint32_t tmpreg;
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);
	/* Delay after an RCC peripheral clock enabling */
	tmpreg = READ_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);

	/* Configure voltage scaling */
	MODIFY_REG(PWR->CR1, PWR_CR1_VOS, (PWR_REGULATOR_VOLTAGE_SCALE1));
	/* Delay after an RCC peripheral clock enabling */
	tmpreg = READ_BIT(PWR->CR1, PWR_CR1_VOS);

	/*Set clock to 216 MHz */
	/* Turn on HSE osc */
	SET_BIT(RCC->CR, RCC_CR_HSEBYP);
	SET_BIT(RCC->CR, RCC_CR_HSEON);
	/* Wait for HSE to turn on */
	 while((RCC->CR & RCC_FLAG_HSERDY) == RESET){ }
	/* Configure the PLL */
	/* First disable the main PLL. */
	CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
	/* Wait till PLL is ready */
	while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) != RESET){ }

	/* Configure the main PLL clock source, multiplication and division factors.*/
	__HAL_RCC_PLL_CONFIG(RCC_PLLSOURCE_HSE, 25, 432, RCC_PLLP_DIV2, 9, 7);

	/* Enable the main PLL. */
	SET_BIT(RCC->CR, RCC_CR_PLLON);
	/* Wait till PLL is ready */
        while(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET){ }

	/* Activate the Over-Drive mode. */
	/*Enable the Over drive mode.*/
	PWR->CR1 |= (uint32_t)PWR_CR1_ODEN;

	while(!__HAL_PWR_GET_FLAG(PWR_FLAG_ODRDY)){ }

	/* Enable the Over-drive switch */
	PWR->CR1 |= (uint32_t)PWR_CR1_ODSWEN;
	while(!__HAL_PWR_GET_FLAG(PWR_FLAG_ODSWRDY)){ }

	/* Configure clock gating and dividers */

	  /* Increasing the CPU frequency */
	  if(FLASH_LATENCY_7 > __HAL_FLASH_GET_LATENCY()){
	    /* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
	    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(FLASH_LATENCY_7));
	    if(__HAL_FLASH_GET_LATENCY() != FLASH_LATENCY_7){
	      while(1){ }
	    }

	    /* Check that the new number of wait states is taken into account to access the Flash
	    memory by reading the FLASH_ACR register */
	    if(__HAL_FLASH_GET_LATENCY() != FLASH_LATENCY_7){
	      while(1){ }
	    }
	  }

	/* Set the highest APBx dividers in order to ensure that we do not go through a non-spec phase whatever we decrease or increase HCLK. */
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_HCLK_DIV16);
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, (RCC_HCLK_DIV16 << 3));
	MODIFY_REG(RCC->CFGR, RCC_CFGR_HPRE, RCC_SYSCLK_DIV1);

	/* Check the PLL ready flag */
	if(__HAL_RCC_GET_FLAG(RCC_FLAG_PLLRDY) == RESET){
		while(1){ }
	}

	/* PLL is selected as System Clock Source */
	__HAL_RCC_SYSCLK_CONFIG(RCC_SYSCLKSOURCE_PLLCLK);
	while (__HAL_RCC_GET_SYSCLK_SOURCE() != (RCC_SYSCLKSOURCE_PLLCLK << RCC_CFGR_SWS_Pos)){ }

	/* Decreasing the number of wait states because of lower CPU frequency */
	if(FLASH_LATENCY_7 < __HAL_FLASH_GET_LATENCY()){
		/* Program the new number of wait states to the LATENCY bits in the FLASH_ACR register */
		MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, (uint32_t)(FLASH_LATENCY_7));
		if(__HAL_FLASH_GET_LATENCY() != FLASH_LATENCY_7){
			while(1){ }
		}

		/* Check that the new number of wait states is taken into account to access the Flash
	    memory by reading the FLASH_ACR register */
		if(__HAL_FLASH_GET_LATENCY() != FLASH_LATENCY_7){
			while(1){ }
		}
	}

	/*-------------------------- PCLK1 Configuration ---------------------------*/
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE1, RCC_HCLK_DIV4);

	/*-------------------------- PCLK2 Configuration ---------------------------*/
	MODIFY_REG(RCC->CFGR, RCC_CFGR_PPRE2, ((RCC_HCLK_DIV2) << 3));	

	UNUSED(tmpreg);
}

void software_init_hook(){
    int *src, *dest;

    src = &_etext;
    for(dest = &_data; dest < &_edata; ){
        *dest++ = *src++;
    }

    for(dest = &_bss; dest < &_ebss; ){
        *dest++ = 0x00000000;
    }

    init_mcu();

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

