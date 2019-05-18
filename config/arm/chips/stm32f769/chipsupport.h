/* Chip support for STM32F769NIH (ARM Cortex-M7).

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

#include <stdint.h>

// Define the registers we need to do a pin toggle ////////////////////////////
/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */
#define     __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

typedef enum{
  RESET = 0U,
  SET = !RESET
} FlagStatus, ITStatus;

typedef struct{
  __IM  uint32_t CPUID;                  /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  __IOM uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  __IOM uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  __IOM uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  __IOM uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  __IOM uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  __IOM uint8_t  SHPR[12U];              /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  __IOM uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  __IOM uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  __IOM uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  __IOM uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  __IOM uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  __IOM uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  __IOM uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  __IM  uint32_t ID_PFR[2U];             /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  __IM  uint32_t ID_DFR;                 /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  __IM  uint32_t ID_AFR;                 /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  __IM  uint32_t ID_MFR[4U];             /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  __IM  uint32_t ID_ISAR[5U];            /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
        uint32_t RESERVED0[1U];
  __IM  uint32_t CLIDR;                  /*!< Offset: 0x078 (R/ )  Cache Level ID register */
  __IM  uint32_t CTR;                    /*!< Offset: 0x07C (R/ )  Cache Type register */
  __IM  uint32_t CCSIDR;                 /*!< Offset: 0x080 (R/ )  Cache Size ID Register */
  __IOM uint32_t CSSELR;                 /*!< Offset: 0x084 (R/W)  Cache Size Selection Register */
  __IOM uint32_t CPACR;                  /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
        uint32_t RESERVED3[93U];
  __OM  uint32_t STIR;                   /*!< Offset: 0x200 ( /W)  Software Triggered Interrupt Register */
        uint32_t RESERVED4[15U];
  __IM  uint32_t MVFR0;                  /*!< Offset: 0x240 (R/ )  Media and VFP Feature Register 0 */
  __IM  uint32_t MVFR1;                  /*!< Offset: 0x244 (R/ )  Media and VFP Feature Register 1 */
  __IM  uint32_t MVFR2;                  /*!< Offset: 0x248 (R/ )  Media and VFP Feature Register 2 */
        uint32_t RESERVED5[1U];
  __OM  uint32_t ICIALLU;                /*!< Offset: 0x250 ( /W)  I-Cache Invalidate All to PoU */
        uint32_t RESERVED6[1U];
  __OM  uint32_t ICIMVAU;                /*!< Offset: 0x258 ( /W)  I-Cache Invalidate by MVA to PoU */
  __OM  uint32_t DCIMVAC;                /*!< Offset: 0x25C ( /W)  D-Cache Invalidate by MVA to PoC */
  __OM  uint32_t DCISW;                  /*!< Offset: 0x260 ( /W)  D-Cache Invalidate by Set-way */
  __OM  uint32_t DCCMVAU;                /*!< Offset: 0x264 ( /W)  D-Cache Clean by MVA to PoU */
  __OM  uint32_t DCCMVAC;                /*!< Offset: 0x268 ( /W)  D-Cache Clean by MVA to PoC */
  __OM  uint32_t DCCSW;                  /*!< Offset: 0x26C ( /W)  D-Cache Clean by Set-way */
  __OM  uint32_t DCCIMVAC;               /*!< Offset: 0x270 ( /W)  D-Cache Clean and Invalidate by MVA to PoC */
  __OM  uint32_t DCCISW;                 /*!< Offset: 0x274 ( /W)  D-Cache Clean and Invalidate by Set-way */
        uint32_t RESERVED7[6U];
  __IOM uint32_t ITCMCR;                 /*!< Offset: 0x290 (R/W)  Instruction Tightly-Coupled Memory Control Register */
  __IOM uint32_t DTCMCR;                 /*!< Offset: 0x294 (R/W)  Data Tightly-Coupled Memory Control Registers */
  __IOM uint32_t AHBPCR;                 /*!< Offset: 0x298 (R/W)  AHBP Control Register */
  __IOM uint32_t CACR;                   /*!< Offset: 0x29C (R/W)  L1 Cache Control Register */
  __IOM uint32_t AHBSCR;                 /*!< Offset: 0x2A0 (R/W)  AHB Slave Control Register */
        uint32_t RESERVED8[1U];
  __IOM uint32_t ABFSR;                  /*!< Offset: 0x2A8 (R/W)  Auxiliary Bus Fault Status Register */
} SCB_Type;

typedef struct{
  __IO uint32_t CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
  __IO uint32_t PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
  __IO uint32_t CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
  __IO uint32_t CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
  __IO uint32_t AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
  __IO uint32_t AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
  __IO uint32_t AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
  uint32_t      RESERVED0;     /*!< Reserved, 0x1C                                                                    */
  __IO uint32_t APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
  __IO uint32_t APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
  uint32_t      RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
  __IO uint32_t AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
  __IO uint32_t AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
  __IO uint32_t AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
  uint32_t      RESERVED2;     /*!< Reserved, 0x3C                                                                    */
  __IO uint32_t APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
  __IO uint32_t APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
  uint32_t      RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
  __IO uint32_t AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
  __IO uint32_t AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
  __IO uint32_t AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
  uint32_t      RESERVED4;     /*!< Reserved, 0x5C                                                                    */
  __IO uint32_t APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
  __IO uint32_t APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
  uint32_t      RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
  __IO uint32_t BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
  __IO uint32_t CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
  uint32_t      RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
  __IO uint32_t SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
  __IO uint32_t PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */
  __IO uint32_t PLLSAICFGR;    /*!< RCC PLLSAI configuration register,                           Address offset: 0x88 */
  __IO uint32_t DCKCFGR1;      /*!< RCC Dedicated Clocks configuration register1,                 Address offset: 0x8C */
  __IO uint32_t DCKCFGR2;      /*!< RCC Dedicated Clocks configuration register 2,               Address offset: 0x90 */

} RCC_TypeDef;

typedef struct{
  __IO uint32_t CR1;   /*!< PWR power control register 1,        Address offset: 0x00 */
  __IO uint32_t CSR1;  /*!< PWR power control/status register 2, Address offset: 0x04 */
  __IO uint32_t CR2;   /*!< PWR power control register 2,        Address offset: 0x08 */
  __IO uint32_t CSR2;  /*!< PWR power control/status register 2, Address offset: 0x0C */
} PWR_TypeDef;

typedef struct{
  __IO uint32_t ACR;      /*!< FLASH access control register,     Address offset: 0x00 */
  __IO uint32_t KEYR;     /*!< FLASH key register,                Address offset: 0x04 */
  __IO uint32_t OPTKEYR;  /*!< FLASH option key register,         Address offset: 0x08 */
  __IO uint32_t SR;       /*!< FLASH status register,             Address offset: 0x0C */
  __IO uint32_t CR;       /*!< FLASH control register,            Address offset: 0x10 */
  __IO uint32_t OPTCR;    /*!< FLASH option control register ,    Address offset: 0x14 */
  __IO uint32_t OPTCR1;   /*!< FLASH option control register 1 ,  Address offset: 0x18 */
} FLASH_TypeDef;

typedef struct{
  __IO uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
  __IO uint32_t OTYPER;   /*!< GPIO port output type register,        Address offset: 0x04      */
  __IO uint32_t OSPEEDR;  /*!< GPIO port output speed register,       Address offset: 0x08      */
  __IO uint32_t PUPDR;    /*!< GPIO port pull-up/pull-down register,  Address offset: 0x0C      */
  __IO uint32_t IDR;      /*!< GPIO port input data register,         Address offset: 0x10      */
  __IO uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
  __IO uint32_t BSRR;     /*!< GPIO port bit set/reset register,      Address offset: 0x18      */
  __IO uint32_t LCKR;     /*!< GPIO port configuration lock register, Address offset: 0x1C      */
  __IO uint32_t AFR[2];   /*!< GPIO alternate function registers,     Address offset: 0x20-0x24 */
} GPIO_TypeDef;


#define SCB_CCR_IC_Msk                     (1UL << 17UL)         /*!< SCB CCR: Instruction cache enable bit Mask */
#define SCB_CCSIDR_ASSOCIATIVITY_Msk       (0x3FFUL << 3UL)      /*!< SCB CCSIDR: Associativity Mask */
#define SCB_CCSIDR_NUMSETS_Msk             (0x7FFFUL << 13UL)    /*!< SCB CCSIDR: NumSets Mask */
#define SCB_DCISW_SET_Msk                  (0x1FFUL << 5UL)      /*!< SCB DCISW: Set Mask */
#define SCB_DCISW_WAY_Msk                  (3UL << 30UL)         /*!< SCB DCISW: Way Mask */
#define SCB_CCR_DC_Msk                     (1UL << 16UL) /*!< SCB CCR: Cache enable bit Mask */
#define FLASH_ACR_ARTEN                    (1UL << 9U)
#define FLASH_ACR_PRFTEN                   (1UL << 8UL)
#define RCC_APB1ENR_PWREN                  (1UL << 28UL)
#define PWR_REGULATOR_VOLTAGE_SCALE1       (3UL << 14UL)
#define PWR_CR1_VOS                        (3UL << 14UL) /*!< VOS[1:0] bits (Regulator voltage scaling output selection) */
#define RCC_CR_HSEON                       (1UL << 16UL)
#define RCC_FLAG_HSERDY                    ((uint8_t)0x17U)
#define RCC_FLAG_PLLRDY                    ((uint8_t)0x39U)
#define RCC_CR_PLLON                       (1UL << 24UL)
#define RCC_PLLSOURCE_HSE                  (1UL << 22UL)
#define RCC_PLLCFGR_PLLN_Pos               (6UL)
#define RCC_PLLP_DIV2                      ((uint32_t)0x00000002UL)
#define RCC_PLLCFGR_PLLP_Pos               (16UL)
#define RCC_PLLCFGR_PLLQ_Pos               (24UL)
#define RCC_PLLCFGR_PLLR_Pos               (28UL)
#define PWR_CR1_ODEN                       (1UL << 16UL)
#define PWR_FLAG_ODRDY                     (1UL << 16UL)
#define PWR_CR1_ODSWEN                     (1UL << 17UL)
#define PWR_FLAG_ODSWRDY                   (1UL << 17UL)
#define FLASH_LATENCY_7                     0x00000007UL    /*!< FLASH Seven Latency cycles */
#define FLASH_ACR_LATENCY                  (15UL << 0UL)
#define RCC_CFGR_PPRE1                     (7UL << 10UL)
#define RCC_HCLK_DIV16                      0x00001C00UL
#define RCC_CFGR_PPRE2                     (7UL << 13UL)
#define RCC_CFGR_HPRE                      (15UL << 4UL)
#define RCC_SYSCLK_DIV1                     0x00000000UL
#define RCC_CFGR_SW                        (3UL << 0UL)
#define RCC_SYSCLKSOURCE_PLLCLK             0x00000002UL
#define RCC_CFGR_SWS                       (3UL << 2UL)
#define RCC_CFGR_SWS_Pos                   (2UL)
#define RCC_HCLK_DIV4                      0x00001400UL
#define RCC_HCLK_DIV2                      0x00001000UL
#define RCC_AHB1ENR_GPIOAEN                (1UL << 0UL)
#define RCC_FLAG_MASK                      ((uint8_t)0x1F)
#define RCC_CR_HSEBYP                      (1UL << 18UL)
#define GPIO_PIN_4                         (uint16_t)0x0010U
#define GPIO_MODER_MODER0                  (3UL << 0UL)
#define GPIO_RESET_OFFSET                  ((uint32_t)16UL)
#define GPIO_MODE_OUTPUT_PP                ((uint32_t)0x00000001UL)   /*!< Output Push Pull Mode */
#define GPIO_MODE                          ((uint32_t)0x00000003U)
#define GPIO_SPEED_HIGH                    ((uint32_t)0x00000003U)
#define GPIO_OSPEEDER_OSPEEDR0             (3UL << 0UL)
#define GPIO_OTYPER_OT_0                   0x00000001UL
#define GPIO_OUTPUT_TYPE                   ((uint32_t)0x00000010U)

#define SCB	((SCB_Type *) 0xE000ED00UL)
#define RCC     ((RCC_TypeDef *) 0x40023800UL)
#define FLASH   ((FLASH_TypeDef *) 0x40023C00UL)
#define PWR     ((PWR_TypeDef *) 0x40007000UL)
#define GPIOA   ((GPIO_TypeDef *) 0x40020000UL)

/* Cache Size ID Register Macros */
#define CCSIDR_WAYS(x)         (((x) & SCB_CCSIDR_ASSOCIATIVITY_Msk) >> 3UL)
#define CCSIDR_SETS(x)         (((x) & SCB_CCSIDR_NUMSETS_Msk      ) >> 13UL)

#define __HAL_PWR_GET_FLAG(__FLAG__) ((PWR->CSR1 & (__FLAG__)) == (__FLAG__))
#define __HAL_FLASH_GET_LATENCY()     (READ_BIT((FLASH->ACR), FLASH_ACR_LATENCY))
#define __HAL_RCC_SYSCLK_CONFIG(__RCC_SYSCLKSOURCE__) MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, (__RCC_SYSCLKSOURCE__))
#define __HAL_RCC_GET_SYSCLK_SOURCE() (RCC->CFGR & RCC_CFGR_SWS)
#define __HAL_RCC_GET_FLAG(__FLAG__) (((((((__FLAG__) >> 5) == 1)? RCC->CR :((((__FLAG__) >> 5) == 2) ? RCC->BDCR :((((__FLAG__) >> 5) == 3)? RCC->CSR :RCC->CIR))) & ((uint32_t)1 << ((__FLAG__) & RCC_FLAG_MASK)))!= 0)? 1 : 0)
#define __HAL_RCC_PLL_CONFIG(__RCC_PLLSource__, __PLLM__, __PLLN__, __PLLP__, __PLLQ__,__PLLR__)  \
                            (RCC->PLLCFGR = ((__RCC_PLLSource__) | (__PLLM__)                   | \
                            ((__PLLN__) << RCC_PLLCFGR_PLLN_Pos)                      | \
                            ((((__PLLP__) >> 1) -1) << RCC_PLLCFGR_PLLP_Pos)          | \
                            ((__PLLQ__) << RCC_PLLCFGR_PLLQ_Pos)                      | \
                            ((__PLLR__) << RCC_PLLCFGR_PLLR_Pos)))


/* Data Synchronization Barrier */
__attribute__((always_inline)) static inline void __DSB(void){
  __asm volatile ("dsb 0xF":::"memory");
}

/* Instruction Synchronization Barrier */
__attribute__((always_inline)) static inline void __ISB(void){
  __asm volatile ("isb 0xF":::"memory");
}


// Provide macros to do the pin toggling ////////////////////////////////////

// Initialize the pin
#define PIN_INIT(number)                                                           \
    do {                                                                           \
        __IO uint32_t tmpreg;                                                      \
	uint32_t temp = 0x00;                                                      \
	uint32_t position = 0x04;                                                  \
                                                                                   \
        switch(number){                                                            \
        case 4:                                                                    \
        /* Enable GPIO A */                                                        \
	SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);                                \
	/* Delay after an RCC peripheral clock enabling */                         \
	tmpreg = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN);                      \
        UNUSED(tmpreg);                                                            \
                                                                                   \
	/* Configure IO Direction mode (Input, Output, Alternate or Analog) */     \
	temp = GPIOA->MODER;                                                       \
	temp &= ~(GPIO_MODER_MODER0 << (position * 2));                            \
	temp |= ((GPIO_MODE_OUTPUT_PP & GPIO_MODE) << (position * 2));             \
	GPIOA->MODER = temp;                                                       \
                                                                                   \
	/* Configure the IO Speed */                                               \
	temp = GPIOA->OSPEEDR;                                                     \
	temp &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2));                       \
	temp |= (GPIO_SPEED_HIGH << (position * 2));                               \
	GPIOA->OSPEEDR = temp;                                                     \
                                                                                   \
	/* Configure the IO Output Type */                                         \
	temp = GPIOA->OTYPER;                                                      \
	temp &= ~(GPIO_OTYPER_OT_0 << position) ;                                  \
	temp |= (((GPIO_MODE_OUTPUT_PP & GPIO_OUTPUT_TYPE) >> 4) << position);     \
	GPIOA->OTYPER = temp;                                                      \
            break;                                                                 \
        }                                                                          \
    } while(0)                                                                     \

// Set the pin to high
#define PIN_SET(number)                         \
    do {                                        \
        switch(number){                         \
        case 4:                                 \
            /* Set PA4 */                       \
            GPIOA->BSRR = GPIO_PIN_4;           \
            break;                              \
        }                                       \
    } while(0)                                  \

// Set the pin to low
#define PIN_CLEAR(number)                                  \
    do {                                                   \
        switch(number){                                    \
        case 4:                                            \
            /* Clear PA4 */                                \
            GPIOA->BSRR = GPIO_PIN_4 << GPIO_RESET_OFFSET; \
            break;                                         \
        }                                                  \
    } while(0)                                             \

#endif /* CHIPSUPPORT_H */
