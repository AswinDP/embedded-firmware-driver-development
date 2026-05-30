/*
 * stm32f303xx_nvic_driver.h
 *
 *  Created on: Dec 27, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_NVIC_DRIVER_H_
#define INC_STM32F303XX_NVIC_DRIVER_H_

#define NO_PR_BITS_IMPLEMENTED   4


/* ================= STM32F303 IRQn Enumeration ================= */

typedef enum
{
    /* Cortex-M4 Processor Exceptions (Negative IRQn) */
    NonMaskableInt_IRQn   = -14,  /* Non Maskable Interrupt */
    HardFault_IRQn        = -13,  /* Hard Fault Interrupt */
    MemManage_IRQn        = -12,  /* Memory Management Fault */
    BusFault_IRQn         = -11,  /* Bus Fault */
    UsageFault_IRQn       = -10,  /* Usage Fault */
    SVCall_IRQn           = -5,   /* SV Call */
    PendSV_IRQn           = -2,   /* Pendable request for system service */
    SysTick_IRQn          = -1,   /* System tick timer */

    /* STM32F303 External Interrupts (IRQ >= 0) */
    WWDG_IRQn             = 0,
    PVD_IRQn              = 1,
    TAMPER_STAMP_IRQn     = 2,
    RTC_WKUP_IRQn         = 3,
    FLASH_IRQn            = 4,
    RCC_IRQn              = 5,
    EXTI0_IRQn            = 6,
    EXTI1_IRQn            = 7,
    EXTI2_TS_IRQn         = 8,
    EXTI3_IRQn            = 9,
    EXTI4_IRQn            = 10,
    DMA1_Channel1_IRQn    = 11,
    DMA1_Channel2_IRQn    = 12,
    DMA1_Channel3_IRQn    = 13,
    DMA1_Channel4_IRQn    = 14,
    DMA1_Channel5_IRQn    = 15,
    DMA1_Channel6_IRQn    = 16,
    DMA1_Channel7_IRQn    = 17,
    ADC1_2_IRQn           = 18,
    USB_HP_CAN_TX_IRQn    = 19,
    USB_LP_CAN_RX0_IRQn   = 20,
    CAN_RX1_IRQn          = 21,
    CAN_SCE_IRQn          = 22,
    EXTI9_5_IRQn          = 23,
    TIM1_BRK_TIM15_IRQn   = 24,
    TIM1_UP_TIM16_IRQn    = 25,
    TIM1_TRG_COM_TIM17_IRQn = 26,
    TIM1_CC_IRQn          = 27,
    TIM2_IRQn             = 28,
    TIM3_IRQn             = 29,
    TIM4_IRQn             = 30,
    I2C1_EV_IRQn          = 31,
    I2C1_ER_IRQn          = 32,
    I2C2_EV_IRQn          = 33,
    I2C2_ER_IRQn          = 34,
    SPI1_IRQn             = 35,
    SPI2_IRQn             = 36,
    USART1_IRQn           = 37,
    USART2_IRQn           = 38,
    USART3_IRQn           = 39,
    EXTI15_10_IRQn        = 40,
    RTC_Alarm_IRQn        = 41,
    USBWakeUp_IRQn        = 42,
    TIM8_BRK_IRQn         = 43,
    TIM8_UP_IRQn          = 44,
    TIM8_TRG_COM_IRQn     = 45,
    TIM8_CC_IRQn          = 46,
    ADC3_IRQn             = 47,
    FMC_IRQn              = 48,
    SPI3_IRQn             = 51,
    UART4_IRQn            = 52,
    UART5_IRQn            = 53,
    TIM6_DAC_IRQn         = 54,
    TIM7_IRQn             = 55,
    DMA2_Channel1_IRQn    = 56,
    DMA2_Channel2_IRQn    = 57,
    DMA2_Channel3_IRQn    = 58,
    DMA2_Channel4_IRQn    = 59,
    DMA2_Channel5_IRQn    = 60,
    ADC4_IRQn             = 61,
    COMP1_2_3_IRQn        = 64,
    COMP4_5_6_IRQn        = 65,
    COMP7_IRQn            = 66,
    I2C3_EV_IRQn          = 72,
    I2C3_ER_IRQn          = 73,
    USB_HP_IRQn           = 74,
    USB_LP_IRQn           = 75,
    USB_WakeUp_RMP_IRQn   = 76,
    TIM20_BRK_IRQn        = 77,
    TIM20_UP_IRQn         = 78,
    TIM20_TRG_COM_IRQn    = 79,
    TIM20_CC_IRQn         = 80,
    FPU_IRQn              = 81,
    SPI4_IRQn             = 84

} IRQn_Type;


/* ================= NVIC API Prototypes (STM32) ================= */

/* Enable an interrupt or exception */
void NVIC_EnableIRQ(IRQn_Type IRQn);

/* Disable an interrupt or exception */
void NVIC_DisableIRQ(IRQn_Type IRQn);

/* Set pending status of an interrupt or exception */
void NVIC_SetPendingIRQ(IRQn_Type IRQn);

/* Clear pending status of an interrupt or exception */
void NVIC_ClearPendingIRQ(IRQn_Type IRQn);

/* Get pending status of an interrupt or exception
 * Returns non-zero if pending, 0 otherwise
 */
uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn);

/* Set priority of an interrupt or exception */
void NVIC_SetPriority(IRQn_Type IRQn, uint8_t priority);

/* Get priority of an interrupt or exception */
uint8_t NVIC_GetPriority(IRQn_Type IRQn);



#endif /* INC_STM32F303XX_NVIC_DRIVER_H_ */
