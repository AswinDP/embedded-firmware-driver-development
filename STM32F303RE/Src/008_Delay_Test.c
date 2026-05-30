/*
 * 008_Delay_Test.c
 *
 *  Created on: Jan 6, 2026
 *      Author: aswin
 */


#include "stm32f303xx.h"


void vApplicationStackOverflowHook(void)
{
    while (1);
}

/* Global timer handle for delay */
GP1_TIM_Handle_t TIM2_DE;

int main(void)
{
    /* Reset peripherals */
    GPIOA_REG_RST();
    TIM2_REG_RST();

    /* Enable GPIO clock */
    GPIO_ClkControl(GPIOA, ENABLE);

    /* ---------- LED GPIO (PA5) ---------- */
    GPIO_Handle_t LED;

    LED.pGPIOx = GPIOA;
    LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN5;
    LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

    GPIO_Init(&LED);

    GP1_TIM_Handle_t TIM2_DE;

    /* ---------- TIM2 Delay Timer ---------- */
    TIM2_DE.pGP1TIMx = TIM2;
    TIM2_DE.Channel = GP1_TIM_CHANNEL_1;   // channel irrelevant for delay
    TIM2_DE.GP1_TIM_Config.GP1TIM_Prescaler = 7;      // 8 MHz / (7+1) = 1 MHz
    TIM2_DE.GP1_TIM_Config.GP1TIM_AutoReload = 0xFFFF;
    TIM2_DE.GP1_TIM_Config.GP1TIM_CounterMode = GP1TIM_COUNTMODE_UP;
    TIM2_DE.GP1_TIM_Config.GP1TIM_ClockDivision = GP1TIM_CKD_1;

    GP1TIM_Init(&TIM2_DE);

    /* ---------- BLINK LOOP ---------- */
    while (1)
    {
        GPIO_TogglePin(GPIOA, GPIO_PIN5);   // Toggle LED
        GP1TIM_Delay_ms(&TIM2_DE, 500);     // 500 ms delay
    }
}
