/*
 * stm32f303xx.h
 *
 *  Created on: Nov 4, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_H_
#define INC_STM32F303XX_H_


#define __vo volatile
#include <stdint.h>


//Some Basic Macros
#define ENABLE						 1
#define DISABLE						 0
#define SET							 ENABLE
#define RESET						 DISABLE
#define GPIO_PIN_RESET				 RESET
#define GPIO_PIN_SET				 SET



#define GPIO_BASEADDR_TO_PORTCODE(x)  \
        ( (x == GPIOA) ? 0 : \
          (x == GPIOB) ? 1 : \
          (x == GPIOC) ? 2 : \
          (x == GPIOD) ? 3 : \
          (x == GPIOE) ? 4 : \
          (x == GPIOF) ? 5 : \
          (x == GPIOG) ? 6 : \
          (x == GPIOH) ? 7 : 0 )


//Base Addresses of various memories
#define FLASH_BASEADDR				0x08000000u
#define SRAM1_BASEADDR				0x20000000u
#define SRAM2_BASEADDR				0x10000000u
#define ROM_BASEADDR				0x1FFFD800u
#define SRAM						SRAM1_BASEADDR


//Base Addresses of various Buses
#define AHB1_BASEADDR				0x40020000u
#define AHB2_BASEADDR				0x48000000u
#define AHB3_BASEADDR				0x50000000u
#define AHB4_BASEADDR				0x60000000u
#define APB1_BASEADDR				0x40000000u
#define APB2_BASEADDR				0x40010000u


#define NVIC_BASEADDR				0xE000E100u


#define SCB_BASEADDR            	0xE000ED00u

//Base Addresses of various peripherals

//GPIOx Peripherals
#define GPIOA_BASEADDR				(AHB2_BASEADDR + 0x0000)
#define GPIOB_BASEADDR				(AHB2_BASEADDR + 0x0400)
#define GPIOC_BASEADDR				(AHB2_BASEADDR + 0x0800)
#define GPIOD_BASEADDR				(AHB2_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR				(AHB2_BASEADDR + 0x1000)
#define GPIOF_BASEADDR				(AHB2_BASEADDR + 0x1400)
#define GPIOG_BASEADDR				(AHB2_BASEADDR + 0x1800)
#define GPIOH_BASEADDR				(AHB2_BASEADDR + 0x1C00)

//RCC Peripherals
#define RCC_BASEADDR				(AHB1_BASEADDR + 0x1000)

//SPIx Peripherals
#define SPI4_BASEADDR				(APB2_BASEADDR + 0x3C00)
#define SPI3_BASEADDR				(APB1_BASEADDR + 0x3C00)
#define SPI2_BASEADDR				(APB1_BASEADDR + 0x3800)
#define SPI1_BASEADDR				(APB2_BASEADDR + 0x3000)

//I2Cx Peripherals
#define I2C3_BASEADDR				(APB1_BASEADDR + 0x7800)
#define I2C2_BASEADDR				(APB1_BASEADDR + 0x5800)
#define I2C1_BASEADDR				(APB1_BASEADDR + 0x5400)

//UARTx USARTx Peripherals
#define UART5_BASEADDR				(APB1_BASEADDR + 0x5000)
#define UART4_BASEADDR				(APB1_BASEADDR + 0x4C00)
#define USART3_BASEADDR				(APB1_BASEADDR + 0x4800)
#define USART2_BASEADDR				(APB1_BASEADDR + 0x4400)
#define USART1_BASEADDR				(APB2_BASEADDR + 0x3800)

//CAN Peripheral
#define CAN_BASEADDR				(APB1_BASEADDR + 0x6400)

//TIMx Peripherals
#define TIM1_BASEADDR				(APB2_BASEADDR + 0x2C00)
#define TIM2_BASEADDR				(APB1_BASEADDR + 0x0000)
#define TIM3_BASEADDR				(APB1_BASEADDR + 0x0400)
#define TIM4_BASEADDR				(APB1_BASEADDR + 0x0800)
#define TIM6_BASEADDR				(APB1_BASEADDR + 0x1000)
#define TIM7_BASEADDR				(APB1_BASEADDR + 0x1400)
#define TIM8_BASEADDR				(APB2_BASEADDR + 0x3400)
#define TIM15_BASEADDR				(APB2_BASEADDR + 0x4000)
#define TIM16_BASEADDR				(APB2_BASEADDR + 0x4400)
#define TIM17_BASEADDR				(APB2_BASEADDR + 0x4800)
#define TIM20_BASEADDR				(APB2_BASEADDR + 0x5000)
#define IWDG_BASEADDR				(APB1_BASEADDR + 0x3000)
#define WWDG_BASEADDR				(APB1_BASEADDR + 0x2C00)
#define RTC_BASEADDR				(APB1_BASEADDR + 0x2800)


#define EXTI_BASEADDR				(APB2_BASEADDR + 0x0400)

#define SYSCFG_BASEADDR				(APB2_BASEADDR + 0x0000)




//Structure for RCC Registers
typedef struct{

	__vo uint32_t CR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t APB1RSTR;
	__vo uint32_t AHBENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t APB1ENR;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t AHBRSTR;
	__vo uint32_t CFGR2;
	__vo uint32_t CFGR3;

}RCC_Regs_t;



//Structure for GPIOx registers
typedef struct{

	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];
	__vo uint32_t BSR;

} GPIO_Regs_t;



//Structure for SPIx registers
typedef struct{

	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;

} SPI_Regs_t;


//Structure for I2Cx registers
typedef struct{

	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t OAR1;
	__vo uint32_t OAR2;
	__vo uint32_t TIMINGR;
	__vo uint32_t TIMEOUTR;
	__vo uint32_t ISR;
	__vo uint32_t ICR;
	__vo uint32_t PECR;
	__vo uint32_t RXDR;
	__vo uint32_t TXDR;

} I2C_Regs_t;


//Structure for USARTx registers
typedef struct{

	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t CR3;
	__vo uint32_t BRR;
	__vo uint32_t GTPR;
	__vo uint32_t RTOR;
	__vo uint32_t RQR;
	__vo uint32_t ISR;
	__vo uint32_t ICR;
	__vo uint32_t RDR;
	__vo uint32_t TDR;

} USART_Regs_t;


//Structure for General Purpose 1 TIMx registers (TIM 2, 3, 4)
typedef struct
{
    __vo uint32_t CR1;      // 0x00
    __vo uint32_t CR2;      // 0x04
    __vo uint32_t SMCR;     // 0x08
    __vo uint32_t DIER;     // 0x0C
    __vo uint32_t SR;       // 0x10
    __vo uint32_t EGR;      // 0x14
    __vo uint32_t CCMR1;    // 0x18
    __vo uint32_t CCMR2;    // 0x1C
    __vo uint32_t CCER;     // 0x20
    __vo uint32_t CNT;      // 0x24
    __vo uint32_t PSC;      // 0x28
    __vo uint32_t ARR;      // 0x2C
    uint32_t RESERVED0;     // 0x30
    __vo uint32_t CCR1;     // 0x34
    __vo uint32_t CCR2;     // 0x38
    __vo uint32_t CCR3;     // 0x3C
    __vo uint32_t CCR4;     // 0x40
    uint32_t RESERVED1;     // 0x44
    __vo uint32_t DCR;      // 0x48
    __vo uint32_t DMAR;     // 0x4C

} GP1_TIM_Regs_t;


//Structure for NVIC registers
typedef struct {
    __vo uint32_t ISER[8];
    uint32_t RESERVED0[24];

    __vo uint32_t ICER[8];
    uint32_t RESERVED1[24];

    __vo uint32_t ISPR[8];
    uint32_t RESERVED2[24];

    __vo uint32_t ICPR[8];
    uint32_t RESERVED3[24];

    __vo uint32_t IABR[8];
    uint32_t RESERVED4[56];

    __vo uint32_t IPR[60];
    uint32_t RESERVED5[404];

    __vo uint32_t STIR;

} NVIC_Regs_t;


//Structure for EXTI registers
typedef struct{

	__vo uint32_t IMR1;
	__vo uint32_t EMR1;
	__vo uint32_t RTSR1;
	__vo uint32_t FTSR1;
	__vo uint32_t SWIER1;
	__vo uint32_t PR1;
	__vo uint32_t IMR2;
	__vo uint32_t EMR2;
	__vo uint32_t RTSR2;
	__vo uint32_t FTSR2;
	__vo uint32_t SWIER2;
	__vo uint32_t PR2;

} EXTI_Regs_t;


//Structure for SYSCFG registers
typedef struct{

	__vo uint32_t CFGR1;
	__vo uint32_t RCR;
	__vo uint32_t EXTICR[4];
	__vo uint32_t CFGR[3];

} SYSCFG_Regs_t;


typedef struct
{
  volatile uint32_t CPUID;   /* CPU ID Base Register */
  volatile uint32_t ICSR;    /* Interrupt Control and State Register */
  volatile uint32_t VTOR;    /* Vector Table Offset Register */
  volatile uint32_t AIRCR;   /* Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;     /* System Control Register */
  /* ... other SCB registers ... */
} SCB_Regs_t;


//Structure for CAN registers

typedef struct
{
    __vo uint32_t TIR;
    __vo uint32_t TDTR;
    __vo uint32_t TDLR;
    __vo uint32_t TDHR;
} CAN_TxMailbox_t;

typedef struct
{
	__vo uint32_t RIR;    // Identifier register
	__vo uint32_t RDTR;   // DLC + filter match index
	__vo uint32_t RDLR;   // Data low
	__vo uint32_t RDHR;   // Data high
} CAN_RxMailbox_t;

typedef struct
{
	__vo uint32_t FR1;
	__vo uint32_t FR2;
} CAN_FilterBank_t;


typedef struct
{
    /* 0x000: Control and status register*/
    __vo uint32_t MCR;        			// 0x000 CANMCR
    __vo uint32_t MSR;        			// 0x004 CANMSR
    __vo uint32_t TSR;        			// 0x008 CANTSR
    __vo uint32_t RF0R;       			// 0x00C CANRF0R
    __vo uint32_t RF1R;       			// 0x010 CANRF1R
    __vo uint32_t IER;        			// 0x014 CANIER
    __vo uint32_t ESR;        			// 0x018 CANESR
    __vo uint32_t BTR;        			// 0x01C CANBTR

    /* 0x180: Tx mailboxes (3 x 4 regs); Rx FIFO mailboxes (2 x 4 regs) */
    __vo uint32_t RESERVED0[0x160/4];   // 0x020..0x17F
    CAN_TxMailbox_t TX[3];				// 0x180: TX mailboxes (3)
    CAN_RxMailbox_t RX[2];				// 0x1B0: RX mailboxes (2 FIFOs)
    __vo uint32_t RESERVED1[0x30/4];    // 0x1D0..0x1FF

    /* 0x200: Filter registers */
    __vo uint32_t FMR;        			// 0x200 CANFMR
    __vo uint32_t FM1R;       			// 0x204 CANFM1R
    __vo uint32_t RESERVED2;  			// 0x208 Reserved
    __vo uint32_t FS1R;       			// 0x20C CANFS1R
    __vo uint32_t RESERVED3;  			// 0x210 Reserved
    __vo uint32_t FFA1R;      			// 0x214 CANFFA1R
    __vo uint32_t RESERVED4;  			// 0x218 Reserved
    __vo uint32_t FA1R;       			// 0x21C CANFA1R
    __vo uint32_t RESERVED5;  			// 0x220 Reserved
    __vo uint32_t RESERVED6[0x1C/4];   	// 0x224..0x23F

    /* 0x240: Filter bank registers (14 banks x 2 regs = 28 regs) */
    CAN_FilterBank_t FILTER[14];

} CAN_Regs_t;



//NVIC Peripheral definitions
#define NVIC						((NVIC_Regs_t*)NVIC_BASEADDR)

//temp
#define SCB    						((SCB_Regs_t *)SCB_BASEADDR)


//GPIO Peripheral definitions
#define GPIOA						((GPIO_Regs_t*)GPIOA_BASEADDR)
#define GPIOB						((GPIO_Regs_t*)GPIOB_BASEADDR)
#define GPIOC						((GPIO_Regs_t*)GPIOC_BASEADDR)
#define GPIOD						((GPIO_Regs_t*)GPIOD_BASEADDR)
#define GPIOE						((GPIO_Regs_t*)GPIOE_BASEADDR)
#define GPIOF						((GPIO_Regs_t*)GPIOF_BASEADDR)
#define GPIOG						((GPIO_Regs_t*)GPIOG_BASEADDR)
#define GPIOH						((GPIO_Regs_t*)GPIOH_BASEADDR)


//RCC Peripheral definitions
#define RCC							((RCC_Regs_t*)RCC_BASEADDR)



//SPI Peripheral definitions
#define SPI1						((SPI_Regs_t*)SPI1_BASEADDR)
#define SPI2						((SPI_Regs_t*)SPI2_BASEADDR)
#define SPI3						((SPI_Regs_t*)SPI3_BASEADDR)
#define SPI4						((SPI_Regs_t*)SPI4_BASEADDR)


//I2C Peripheral definitions
#define I2C1						((I2C_Regs_t*)I2C1_BASEADDR)
#define I2C2						((I2C_Regs_t*)I2C2_BASEADDR)
#define I2C3						((I2C_Regs_t*)I2C3_BASEADDR)


//USART Peripheral definitions
#define USART1						((USART_Regs_t*)USART1_BASEADDR)
#define USART2						((USART_Regs_t*)USART2_BASEADDR)
#define USART3						((USART_Regs_t*)USART3_BASEADDR)
#define UART4						((USART_Regs_t*)UART4_BASEADDR)
#define UART5						((USART_Regs_t*)UART5_BASEADDR)

/* USART_CR1 bits */
/* USART_CR1 bits (32-bit) */
#define USART_CR1_UE        (1U << 0)
#define USART_CR1_UESM      (1U << 1)
#define USART_CR1_RE        (1U << 2)
#define USART_CR1_TE        (1U << 3)
#define USART_CR1_IDLEIE    (1U << 4)
#define USART_CR1_RXNEIE    (1U << 5)
#define USART_CR1_TCIE      (1U << 6)
#define USART_CR1_TXEIE     (1U << 7)
#define USART_CR1_PEIE      (1U << 8)
#define USART_CR1_PS        (1U << 9)
#define USART_CR1_PCE       (1U << 10)
#define USART_CR1_WAKE      (1U << 11)
#define USART_CR1_M0        (1U << 12)
#define USART_CR1_MME       (1U << 13)
#define USART_CR1_CMIE      (1U << 14)
#define USART_CR1_OVER8     (1U << 15)
#define USART_CR1_DEDT      (1U << 16)
#define USART_CR1_DEAT      (1U << 21)
#define USART_CR1_RTOIE     (1U << 26)
#define USART_CR1_EOBIE     (1U << 27)
#define USART_CR1_M1        (1U << 28)
/* Bits 29–31: Reserved */


/* USART_CR2 bits */
/* Bits 0–3: Reserved */
#define USART_CR2_ADDM7     (1U << 4)
#define USART_CR2_LBDL      (1U << 5)
#define USART_CR2_LBDIE     (1U << 6)
/* Bit 7: Reserved */
#define USART_CR2_LBCL      (1U << 8)
#define USART_CR2_CPHA      (1U << 9)
#define USART_CR2_CPOL      (1U << 10)
#define USART_CR2_CLKEN     (1U << 11)
#define USART_CR2_STOP0     (1U << 12)
#define USART_CR2_STOP1     (1U << 13)
#define USART_CR2_LINEN     (1U << 14)
#define USART_CR2_SWAP      (1U << 15)
#define USART_CR2_RXINV     (1U << 16)
#define USART_CR2_TXINV     (1U << 17)
#define USART_CR2_DATAINV   (1U << 18)
#define USART_CR2_MSBFIRST  (1U << 19)
#define USART_CR2_ABREN     (1U << 20)
#define USART_CR2_ABRMOD    (1U << 21)
#define USART_CR2_RTOEN     (1U << 23)
#define USART_CR2_ADD       (1U << 24)


/* USART_CR3 bits (32-bit) */
#define USART_CR3_EIE       (1U << 0)
#define USART_CR3_IREN      (1U << 1)
#define USART_CR3_IRLP      (1U << 2)
#define USART_CR3_HDSEL     (1U << 3)
#define USART_CR3_NACK      (1U << 4)
#define USART_CR3_SCEN      (1U << 5)
#define USART_CR3_DMAR      (1U << 6)
#define USART_CR3_DMAT      (1U << 7)
#define USART_CR3_RTSE      (1U << 8)
#define USART_CR3_CTSE      (1U << 9)
#define USART_CR3_CTSIE     (1U << 10)
#define USART_CR3_ONEBIT    (1U << 11)
#define USART_CR3_OVRDIS    (1U << 12)
#define USART_CR3_DDRE      (1U << 13)
#define USART_CR3_DEM       (1U << 14)
#define USART_CR3_DEP       (1U << 15)
/* Bit 16: Reserved */
#define USART_CR3_SCARCNT  (1U << 17)
#define USART_CR3_WUS      (1U << 20)
#define USART_CR3_WUFIE     (1U << 22)
/* Bits 23–31: Reserved */


/* USART_RQR bits */
#define USART_RQR_ABRRQ     (1U << 0)
#define USART_RQR_SBKRQ     (1U << 1)
#define USART_RQR_MMRQ      (1U << 2)
#define USART_RQR_RXFRQ     (1U << 3)
#define USART_RQR_TXFRQ     (1U << 4)


/* USART_ISR bits */
#define USART_ISR_PE        (1U << 0)   /* Parity error */
#define USART_ISR_FE        (1U << 1)   /* Framing error */
#define USART_ISR_NF        (1U << 2)   /* Noise detected flag */
#define USART_ISR_ORE       (1U << 3)   /* Overrun error */
#define USART_ISR_IDLE      (1U << 4)   /* Idle line detected */
#define USART_ISR_RXNE      (1U << 5)   /* Read data register not empty */
#define USART_ISR_TC        (1U << 6)   /* Transmission complete */
#define USART_ISR_TXE       (1U << 7)   /* Transmit data register empty */
#define USART_ISR_LBDF      (1U << 8)   /* LIN break detection flag */
#define USART_ISR_CTSIF     (1U << 9)   /* CTS interrupt flag */
#define USART_ISR_CTS       (1U << 10)  /* CTS flag */
#define USART_ISR_RTOF      (1U << 11)  /* Receiver timeout */
#define USART_ISR_EOBF      (1U << 12)  /* End of block flag */
#define USART_ISR_ABRE      (1U << 14)  /* Auto baud rate error */
#define USART_ISR_ABRF      (1U << 15)  /* Auto baud rate flag */
#define USART_ISR_BUSY      (1U << 16)  /* Busy flag */
#define USART_ISR_CMF       (1U << 17)  /* Character match flag */
#define USART_ISR_SBKF      (1U << 18)  /* Send break flag */
#define USART_ISR_RWU       (1U << 19)  /* Receiver wakeup */
#define USART_ISR_WUF       (1U << 20)  /* Wakeup from Stop mode */
#define USART_ISR_TEACK     (1U << 21)  /* Transmit enable acknowledge */
#define USART_ISR_REACK     (1U << 22)  /* Receive enable acknowledge */

/* USART_ICR bits */
#define USART_ICR_PECF      (1U << 0)   /* Parity error clear */
#define USART_ICR_FECF      (1U << 1)   /* Framing error clear */
#define USART_ICR_NCF       (1U << 2)   /* Noise detected clear */
#define USART_ICR_ORECF     (1U << 3)   /* Overrun error clear */
#define USART_ICR_IDLECF    (1U << 4)   /* Idle line clear */
#define USART_ICR_TCCF      (1U << 6)   /* Transmission complete clear */
#define USART_ICR_LBDCF     (1U << 8)   /* LIN break detection clear */
#define USART_ICR_CTSCF     (1U << 9)   /* CTS clear */
#define USART_ICR_RTOCF     (1U << 11)  /* Receiver timeout clear */
#define USART_ICR_EOBCF     (1U << 12)  /* End of block clear */
#define USART_ICR_CMCF      (1U << 17)  /* Character match clear */
#define USART_ICR_WUCF      (1U << 20)  /* Wakeup from Stop mode clear */

//CAN Peripheral definitions
#define CAN						((CAN_Regs_t*)CAN_BASEADDR)

//TIM Peripheral definitions
#define TIM2   				((GP1_TIM_Regs_t*)TIM2_BASEADDR)
#define TIM3   				((GP1_TIM_Regs_t*)TIM3_BASEADDR)
#define TIM4   				((GP1_TIM_Regs_t*)TIM4_BASEADDR)

/* TIMx_CR1 register bit positions */
#define GP1_TIM_CR1_CEN        0   /* Counter enable */
#define GP1_TIM_CR1_UDIS       1   /* Update disable */
#define GP1_TIM_CR1_URS        2   /* Update request source */
#define GP1_TIM_CR1_OPM        3   /* One-pulse mode */
#define GP1_TIM_CR1_DIR        4   /* Direction */
#define GP1_TIM_CR1_CMS        5   /* Center-aligned mode (bits 6:5) */
#define GP1_TIM_CR1_ARPE       7   /* Auto-reload preload enable */
#define GP1_TIM_CR1_CKD        8   /* Clock division (bits 9:8) */
#define GP1_TIM_CR1_UIFREMAP  10   /* UIF status bit remap */
/* TIMx_DIER register bit positions */
#define GP1_TIM_DIER_UIE      0   /* Update interrupt enable */
#define GP1_TIM_DIER_CC1IE    1   /* Capture/Compare 1 interrupt enable */
#define GP1_TIM_DIER_CC2IE    2
#define GP1_TIM_DIER_CC3IE    3
#define GP1_TIM_DIER_CC4IE    4
#define GP1_TIM_DIER_TIE      6   /* Trigger interrupt enable */
#define GP1_TIM_DIER_UDE      8   /* Update DMA request enable */
#define GP1_TIM_DIER_CC1DE    9
#define GP1_TIM_DIER_CC2DE   10
#define GP1_TIM_DIER_CC3DE   11
#define GP1_TIM_DIER_CC4DE   12
#define GP1_TIM_DIER_TDE     14   /* Trigger DMA request enable */
/* TIMx_SR register bit positions */
#define GP1_TIM_SR_UIF        0   /* Update interrupt flag */
#define GP1_TIM_SR_CC1IF     1   /* Capture/Compare 1 flag */
#define GP1_TIM_SR_CC2IF     2
#define GP1_TIM_SR_CC3IF     3
#define GP1_TIM_SR_CC4IF     4
#define GP1_TIM_SR_TIF       6   /* Trigger interrupt flag */
#define GP1_TIM_SR_CC1OF     9   /* Capture/Compare 1 overcapture */
#define GP1_TIM_SR_CC2OF    10
#define GP1_TIM_SR_CC3OF    11
#define GP1_TIM_SR_CC4OF    12
/* TIMx_EGR register bit positions */
#define GP1_TIM_EGR_UG        0   /* Update generation */
#define GP1_TIM_EGR_CC1G     1   /* Capture/Compare 1 generation */
#define GP1_TIM_EGR_CC2G     2
#define GP1_TIM_EGR_CC3G     3
#define GP1_TIM_EGR_CC4G     4
#define GP1_TIM_EGR_TG       6   /* Trigger generation */
/* TIMx_CCMR1 output compare bit positions */
#define GP1_TIM_CCMR1_CC1S    0   /* Capture/Compare 1 selection (bits 1:0) */
#define GP1_TIM_CCMR1_OC1FE   2
#define GP1_TIM_CCMR1_OC1PE   3
#define GP1_TIM_CCMR1_OC1M    4   /* OC1 mode (bits 6:4) */
#define GP1_TIM_CCMR1_OC1CE   7
#define GP1_TIM_CCMR1_CC2S    8   /* Capture/Compare 2 selection (bits 9:8) */
#define GP1_TIM_CCMR1_OC2FE  10
#define GP1_TIM_CCMR1_OC2PE  11
#define GP1_TIM_CCMR1_OC2M   12   /* OC2 mode (bits 14:12) */
#define GP1_TIM_CCMR1_OC2CE  15
/* TIMx_CCMR1 input capture bit positions */
#define GP1_TIM_CCMR1_IC1PSC  2   /* Input capture 1 prescaler (bits 3:2) */
#define GP1_TIM_CCMR1_IC1F    4   /* Input capture 1 filter (bits 7:4) */
#define GP1_TIM_CCMR1_IC2PSC 10   /* Input capture 2 prescaler (bits 11:10) */
#define GP1_TIM_CCMR1_IC2F   12   /* Input capture 2 filter (bits 15:12) */
/* TIMx_CCMR2 output compare bit positions */
#define GP1_TIM_CCMR2_CC3S    0
#define GP1_TIM_CCMR2_OC3FE   2
#define GP1_TIM_CCMR2_OC3PE   3
#define GP1_TIM_CCMR2_OC3M    4
#define GP1_TIM_CCMR2_OC3CE   7
#define GP1_TIM_CCMR2_CC4S    8
#define GP1_TIM_CCMR2_OC4FE  10
#define GP1_TIM_CCMR2_OC4PE  11
#define GP1_TIM_CCMR2_OC4M   12
#define GP1_TIM_CCMR2_OC4CE  15
/* TIMx_CCMR2 input capture bit positions */
#define GP1_TIM_CCMR2_IC3PSC  2
#define GP1_TIM_CCMR2_IC3F    4
#define GP1_TIM_CCMR2_IC4PSC 10
#define GP1_TIM_CCMR2_IC4F   12
/* TIMx_CCER register bit positions */
/* Channel 1 */
#define GP1_TIM_CCER_CC1E     0   /* Capture/Compare 1 output enable */
#define GP1_TIM_CCER_CC1P     1   /* Capture/Compare 1 polarity */
#define GP1_TIM_CCER_CC1NP    3   /* Capture/Compare 1 complementary polarity */
/* Channel 2 */
#define GP1_TIM_CCER_CC2E     4
#define GP1_TIM_CCER_CC2P     5
#define GP1_TIM_CCER_CC2NP    7
/* Channel 3 */
#define GP1_TIM_CCER_CC3E     8
#define GP1_TIM_CCER_CC3P     9
#define GP1_TIM_CCER_CC3NP   11
/* Channel 4 */
#define GP1_TIM_CCER_CC4E    12
#define GP1_TIM_CCER_CC4P    13
#define GP1_TIM_CCER_CC4NP   15


//NVIC Peripheral definitions
#define EXTI						((EXTI_Regs_t*)EXTI_BASEADDR)

//SYSCFG Peripheral definitions
#define SYSCFG						((SYSCFG_Regs_t*)SYSCFG_BASEADDR)


//Clock Enable Macros for GPIOx
#define GPIOA_CLK_EN()				( RCC -> AHBENR |= (1 << 17))
#define GPIOB_CLK_EN()				( RCC -> AHBENR |= (1 << 18))
#define GPIOC_CLK_EN()				( RCC -> AHBENR |= (1 << 19))
#define GPIOD_CLK_EN()				( RCC -> AHBENR |= (1 << 20))
#define GPIOE_CLK_EN()				( RCC -> AHBENR |= (1 << 21))
#define GPIOF_CLK_EN()				( RCC -> AHBENR |= (1 << 22))
#define GPIOG_CLK_EN()				( RCC -> AHBENR |= (1 << 23))
#define GPIOH_CLK_EN()				( RCC -> AHBENR |= (1 << 16))


//Clock Enable Macros for SPI
#define SPI1_CLK_EN()				( RCC -> APB2ENR |= (1 << 12))
#define SPI2_CLK_EN()				( RCC -> APB1ENR |= (1 << 14))
#define SPI3_CLK_EN()				( RCC -> APB1ENR |= (1 << 15))
#define SPI4_CLK_EN()				( RCC -> APB2ENR |= (1 << 15))


//Clock Enable Macros for I2C
#define I2C1_CLK_EN()				(RCC -> APB1ENR |= (1 << 21))
#define I2C2_CLK_EN()				(RCC -> APB1ENR |= (1 << 22))
#define I2C3_CLK_EN()				(RCC -> APB1ENR |= (1 << 30))


//Clock Enable Macros for USART UART
#define USART1_CLK_EN()				(RCC -> APB2ENR |= (1 << 14))
#define USART2_CLK_EN()				(RCC -> APB1ENR |= (1 << 17))
#define USART3_CLK_EN()				(RCC -> APB1ENR |= (1 << 18))
#define UART4_CLK_EN()				(RCC -> APB1ENR |= (1 << 19))
#define UART5_CLK_EN()				(RCC -> APB1ENR |= (1 << 20))


//Clock Enable Macros for TIMx
#define TIM1_CLK_EN()				( RCC -> APB2ENR |= (1 << 11))
#define TIM2_CLK_EN()				( RCC -> APB1ENR |= (1 << 0))
#define TIM3_CLK_EN()				( RCC -> APB1ENR |= (1 << 1))
#define TIM4_CLK_EN()				( RCC -> APB1ENR |= (1 << 2))
#define TIM6_CLK_EN()				( RCC -> APB1ENR |= (1 << 4))
#define TIM7_CLK_EN()				( RCC -> APB1ENR |= (1 << 5))
#define TIM8_CLK_EN()				( RCC -> APB2ENR |= (1 << 13))
#define TIM15_CLK_EN()				( RCC -> APB2ENR |= (1 << 16))
#define TIM16_CLK_EN()				( RCC -> APB2ENR |= (1 << 17))
#define TIM17_CLK_EN()				( RCC -> APB2ENR |= (1 << 18))
#define TIM20_CLK_EN()				( RCC -> APB2ENR |= (1 << 20))
#define WWDG_CLK_EN()				( RCC -> APB1ENR |= (1 << 11))
//#define IWDG_CLK_EN()
//#define RTC_CLK_EN()


//Clock Enable Macros for SYSCFG & EXTI
#define SYSCFG_CLK_EN()				( RCC -> APB2ENR |= (1 << 0))


//Clock Enable Macros for CAN
#define CAN_CLK_EN()				( RCC -> APB1ENR |= (1 << 25))

//Clock Disable Macros for GPIOx
#define GPIOA_CLK_DI()				( RCC -> AHBENR &= ~(1 << 17))
#define GPIOB_CLK_DI()				( RCC -> AHBENR &= ~(1 << 18))
#define GPIOC_CLK_DI()				( RCC -> AHBENR &= ~(1 << 19))
#define GPIOD_CLK_DI()				( RCC -> AHBENR &= ~(1 << 20))
#define GPIOE_CLK_DI()				( RCC -> AHBENR &= ~(1 << 21))
#define GPIOF_CLK_DI()				( RCC -> AHBENR &= ~(1 << 22))
#define GPIOG_CLK_DI()				( RCC -> AHBENR &= ~(1 << 23))
#define GPIOH_CLK_DI()				( RCC -> AHBENR &= ~(1 << 16))


//Clock Disable Macros for SPI
#define SPI1_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 12))
#define SPI2_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 14))
#define SPI3_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 15))
#define SPI4_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 15))

//Clock Disable Macros for I2C
#define I2C1_CLK_DI()				(RCC -> APB1ENR &= ~(1 << 21))
#define I2C2_CLK_DI()				(RCC -> APB1ENR &= ~(1 << 22))
#define I2C3_CLK_DI()				(RCC -> APB1ENR &= ~(1 << 30))


//Clock Disable Macros for USART UART
#define USART1_CLK_DI()				(RCC -> APB2ENR &= ~(1 << 14))
#define USART2_CLK_DI()				(RCC -> APB1ENR &= ~(1 << 17))
#define USART3_CLK_DI()				(RCC -> APB1ENR &= ~(1 << 18))
#define UART4_CLK_DI()				(RCC -> APB1ENR &= ~(1 << 19))
#define UART5_CLK_DI()				(RCC -> APB1ENR &= ~(1 << 20))


//Clock Disable Macros for TIMx
#define TIM1_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 11))
#define TIM2_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 0))
#define TIM3_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 1))
#define TIM4_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 2))
#define TIM6_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 4))
#define TIM7_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 5))
#define TIM8_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 13))
#define TIM15_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 16))
#define TIM16_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 17))
#define TIM17_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 18))
#define TIM20_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 20))
#define WWDG_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 11))
//#define IWDG_CLK_DI()
//#define RTC_CLK_DI()


//Clock Disable Macros for SYSCFG & EXTI
#define SYSCFG_CLK_DI()				( RCC -> APB2ENR &= ~(1 << 0))


//Clock Disable Macros for CAN
#define CAN_CLK_DI()				( RCC -> APB1ENR &= ~(1 << 25))

//Gpio Reset Macro
#define GPIOA_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 17));  ( RCC -> AHBRSTR &= ~(1 << 17));} while(0)
#define GPIOB_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 18));  ( RCC -> AHBRSTR &= ~(1 << 18));} while(0)
#define GPIOC_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 19));  ( RCC -> AHBRSTR &= ~(1 << 19));} while(0)
#define GPIOD_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 20));  ( RCC -> AHBRSTR &= ~(1 << 20));} while(0)
#define GPIOE_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 21));  ( RCC -> AHBRSTR &= ~(1 << 21));} while(0)
#define GPIOF_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 22));  ( RCC -> AHBRSTR &= ~(1 << 22));} while(0)
#define GPIOG_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 23));  ( RCC -> AHBRSTR &= ~(1 << 23));} while(0)
#define GPIOH_REG_RST()				do {( RCC -> AHBRSTR |= (1 << 16));  ( RCC -> AHBRSTR &= ~(1 << 16));} while(0)


//SPI Reset Macro
#define SPI1_REG_RST()				do {( RCC -> APB2RSTR |= (1 << 12));  ( RCC -> APB2RSTR &= ~(1 << 12));} while(0)
#define SPI2_REG_RST()				do {( RCC -> APB1RSTR |= (1 << 14));  ( RCC -> APB1RSTR &= ~(1 << 14));} while(0)
#define SPI3_REG_RST()				do {( RCC -> APB1RSTR |= (1 << 15));  ( RCC -> APB1RSTR &= ~(1 << 15));} while(0)
#define SPI4_REG_RST()				do {( RCC -> APB2RSTR |= (1 << 15));  ( RCC -> APB2RSTR &= ~(1 << 15));} while(0)


//I2C Reset Macro
#define I2C1_REG_RST()				do {( RCC -> APB1RSTR |= (1 << 21));  ( RCC -> APB1RSTR &= ~(1 << 21));} while(0)
#define I2C2_REG_RST()				do {( RCC -> APB1RSTR |= (1 << 22));  ( RCC -> APB1RSTR &= ~(1 << 22));} while(0)
#define I2C3_REG_RST()				do {( RCC -> APB1RSTR |= (1 << 30));  ( RCC -> APB1RSTR &= ~(1 << 30));} while(0)


//USART Reset Macro
#define USART1_REG_RST()			do {( RCC -> APB2RSTR |= (1 << 14));  ( RCC -> APB2RSTR &= ~(1 << 14));} while(0)
#define USART2_REG_RST()			do {( RCC -> APB1RSTR |= (1 << 17));  ( RCC -> APB1RSTR &= ~(1 << 17));} while(0)
#define USART3_REG_RST()			do {( RCC -> APB1RSTR |= (1 << 18));  ( RCC -> APB1RSTR &= ~(1 << 18));} while(0)
#define UART4_REG_RST()				do {( RCC -> APB1RSTR |= (1 << 19));  ( RCC -> APB1RSTR &= ~(1 << 19));} while(0)
#define UART5_REG_RST()				do {( RCC -> APB1RSTR |= (1 << 20));  ( RCC -> APB1RSTR &= ~(1 << 20));} while(0)


//Clock Reset Macros for TIMx
#define TIM1_REG_RST()			    do { (RCC->APB2RSTR |=  (1 << 11)); (RCC->APB2RSTR &= ~(1 << 11)); } while(0)
#define TIM15_REG_RST()   			do { (RCC->APB2RSTR |=  (1 << 16)); (RCC->APB2RSTR &= ~(1 << 16)); } while(0)
#define TIM16_REG_RST()   			do { (RCC->APB2RSTR |=  (1 << 17)); (RCC->APB2RSTR &= ~(1 << 17)); } while(0)
#define TIM17_REG_RST()   			do { (RCC->APB2RSTR |=  (1 << 18)); (RCC->APB2RSTR &= ~(1 << 18)); } while(0)
#define TIM2_REG_RST()    			do { (RCC->APB1RSTR |=  (1 << 0));  (RCC->APB1RSTR &= ~(1 << 0));  } while(0)
#define TIM20_REG_RST()   			do { (RCC->APB2RSTR |=  (1 << 20)); (RCC->APB2RSTR &= ~(1 << 20)); } while(0)
#define TIM3_REG_RST()    			do { (RCC->APB1RSTR |=  (1 << 1));  (RCC->APB1RSTR &= ~(1 << 1));  } while(0)
#define TIM4_REG_RST()    			do { (RCC->APB1RSTR |=  (1 << 2));  (RCC->APB1RSTR &= ~(1 << 2));  } while(0)
#define TIM6_REG_RST()    			do { (RCC->APB1RSTR |=  (1 << 4));  (RCC->APB1RSTR &= ~(1 << 4));  } while(0)
#define TIM7_REG_RST()    			do { (RCC->APB1RSTR |=  (1 << 5));  (RCC->APB1RSTR &= ~(1 << 5));  } while(0)
#define TIM8_REG_RST()    			do { (RCC->APB2RSTR |=  (1 << 13)); (RCC->APB2RSTR &= ~(1 << 13)); } while(0)
#define WWDG_REG_RST()    			do { (RCC->APB1RSTR |=  (1 << 11)); (RCC->APB1RSTR &= ~(1 << 11)); } while(0)

//Clock Reset Macro for SYSCFG & EXTI
#define SYSCFG_CLK_RST()			do {( RCC -> APB2RSTR |= (1 << 0));  ( RCC -> APB2RSTR &= ~(1 << 0));} while(0)


//Clock Reset Macro for CAN
#define CAN_CLK_RST()				do {( RCC -> APB1RSTR |= (1 << 25));  ( RCC -> APB1RSTR &= ~(1 << 25));} while(0)


#include "stm32f303xx_gpio_driver.h"
#include "stm32f303xx_spi_driver.h"
#include "stm32f303xx_i2c_driver.h"
#include "stm32f303xx_usart_driver.h"
#include "stm32f303xx_tim_driver.h"
#include "stm32f303xx_nvic_driver.h"
#include "stm32f303xx_rcc_driver.h"
#include "stm32f303xx_exti_driver.h"
#include "stm32f303xx_can_driver.h"

#endif /* INC_STM32F303XX_H_ */
