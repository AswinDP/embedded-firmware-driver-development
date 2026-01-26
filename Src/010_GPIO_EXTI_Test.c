/*
 * 010_GPIO_EXTI_Test.c
 *
 *  Created on: Jan 18, 2026
 *      Author: aswin
 */


#include "stm32f303xx.h"

void vApplicationStackOverflowHook(void)			//Just for RTOS
{
    while (1);
}

/* Global timer handle for delay */
GP1_TIM_Handle_t TIM2_DE;

volatile uint8_t led0_req = 0;
volatile uint8_t led1_req = 0;
volatile uint8_t led2_req = 0;



void EXTI_Callback(uint8_t exti_line)
{
    if(exti_line == GPIO_PIN0)
        led0_req = 1;
    else if(exti_line == GPIO_PIN1)
        led1_req = 1;
    else if(exti_line == GPIO_PIN2)
        led2_req = 1;
}



int main(void)
{
	GPIOB_REG_RST();
	GPIOC_REG_RST();


	GPIO_Handle_t GPIOLED0, GPIOLED1, GPIOLED2;

	GPIOLED0.pGPIOx = GPIOB;
	GPIOLED0.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN0;
	GPIOLED0.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLED0.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOLED0.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLED0.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIOLED1.pGPIOx = GPIOB;
	GPIOLED1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN1;
	GPIOLED1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLED1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOLED1.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLED1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIOLED2.pGPIOx = GPIOB;
	GPIOLED2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN2;
	GPIOLED2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLED2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOLED2.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLED2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOLED0);
	GPIO_Init(&GPIOLED1);
	GPIO_Init(&GPIOLED2);


	GPIO_Handle_t GPIOBTN0, GPIOBTN1, GPIOBTN2;

	GPIOBTN0.pGPIOx = GPIOC;
	GPIOBTN0.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN0;
	GPIOBTN0.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBTN0.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBTN0.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIOBTN1.pGPIOx = GPIOC;
	GPIOBTN1.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN1;
	GPIOBTN1.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBTN1.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBTN1.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIOBTN2.pGPIOx = GPIOC;
	GPIOBTN2.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN2;
	GPIOBTN2.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBTN2.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBTN2.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBTN0);
	GPIO_Init(&GPIOBTN1);
	GPIO_Init(&GPIOBTN2);


    /* ---------- TIM2 Delay Timer ---------- */
    TIM2_DE.pGP1TIMx = TIM2;
    TIM2_DE.Channel = GP1_TIM_CHANNEL_1;   // channel irrelevant for delay
    TIM2_DE.GP1_TIM_Config.GP1TIM_Prescaler = 7;      // 8 MHz / (7+1) = 1 MHz
    TIM2_DE.GP1_TIM_Config.GP1TIM_AutoReload = 0xFFFF;
    TIM2_DE.GP1_TIM_Config.GP1TIM_CounterMode = GP1TIM_COUNTMODE_UP;
    TIM2_DE.GP1_TIM_Config.GP1TIM_ClockDivision = GP1TIM_CKD_1;

    GP1TIM_Init(&TIM2_DE);



	NVIC_SetPriority(EXTI0_IRQn, 3);
	NVIC_SetPriority(EXTI1_IRQn, 2);
	NVIC_SetPriority(EXTI2_TS_IRQn, 1);
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_TS_IRQn);


	while(1)
	{
	    if(led0_req)
	    {
	        led0_req = 0;
	        GPIO_WritePin(GPIOB, GPIO_PIN0, ENABLE);
	        GP1TIM_Delay_ms(&TIM2_DE, 10000);
	        GPIO_WritePin(GPIOB, GPIO_PIN0, DISABLE);
	    }

	    if(led1_req)
	    {
	        led1_req = 0;
	        GPIO_WritePin(GPIOB, GPIO_PIN1, ENABLE);
	        GP1TIM_Delay_ms(&TIM2_DE, 5000);
	        GPIO_WritePin(GPIOB, GPIO_PIN1, DISABLE);
	    }

	    if(led2_req)
	    {
	        led2_req = 0;
	        GPIO_WritePin(GPIOB, GPIO_PIN2, ENABLE);
	        GP1TIM_Delay_ms(&TIM2_DE, 2000);
	        GPIO_WritePin(GPIOB, GPIO_PIN2, DISABLE);
	    }
	}




}
