/*
 * 010_GPIO_EXTI_Test.c
 *
 *  Created on: Jan 18, 2026
 *      Author: aswin
 */


/*
 * NOTE: EDUCATIONAL USE ONLY - INTENTIONAL DESIGN FLAW
 *
 * This code purposely calls blocking delays (delay_ms) inside the Interrupt
 * Service Routine (ISR). In real-world applications, this is bad practice
 * as it freezes the main loop and starves other tasks.
 *
 * However, this design is used here specifically to demonstrate "NVIC Preemption."
 * By holding the CPU in an ISR for a long duration, we can visually observe
 * a higher-priority interrupt interrupting a lower-priority one.
 */

#include "stm32f303xx.h"

void vApplicationStackOverflowHook(void)			//Just for RTOS
{
    while (1);
}

void delay_ms(uint32_t ms)
{
    volatile uint32_t count;

    while (ms--)
    {
        count = 1140;   // calibrated for YOUR system
        while (count--);
    }
}


void Handle_LED0(void)
{
	GPIO_WritePin(GPIOB, GPIO_PIN0, ENABLE);
	delay_ms(10000);
	GPIO_WritePin(GPIOB, GPIO_PIN0, DISABLE);
}

void Handle_LED1(void)
{
	GPIO_WritePin(GPIOB, GPIO_PIN1, ENABLE);
	delay_ms(5000);
	GPIO_WritePin(GPIOB, GPIO_PIN1, DISABLE);
}

void Handle_LED2(void)
{
	GPIO_WritePin(GPIOB, GPIO_PIN2, ENABLE);
	delay_ms(2000);
	GPIO_WritePin(GPIOB, GPIO_PIN2, DISABLE);
}


void EXTI_Callback(uint8_t exti_line)
{
    if(exti_line == GPIO_PIN0)
    	Handle_LED0();
    else if(exti_line == GPIO_PIN1)
    	Handle_LED1();
    else if(exti_line == GPIO_PIN2)
    	Handle_LED2();
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



	NVIC_SetPriority(EXTI0_IRQn, 3);
	NVIC_SetPriority(EXTI1_IRQn, 2);
	NVIC_SetPriority(EXTI2_TS_IRQn, 1);
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_TS_IRQn);


	while(1)
	{

	}




}
