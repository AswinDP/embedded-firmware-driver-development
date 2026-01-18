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


void EXTI_Callback(uint8_t exti_line)
{
    if(exti_line == GPIO_PIN13)
    {
        GPIO_TogglePin(GPIOA, GPIO_PIN5);
    }
}


int main(void)
{
	GPIOA_REG_RST();
	GPIOC_REG_RST();

	NVIC_SetPriority(EXTI15_10_IRQn, 2);
	NVIC_EnableIRQ(EXTI15_10_IRQn);

	GPIO_Handle_t GPIOLED;

	GPIOLED.pGPIOx = GPIOA;
	GPIOLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN5;
	GPIOLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOLED);


	GPIO_Handle_t GPIOBTN;

	GPIOBTN.pGPIOx = GPIOC;
	GPIOBTN.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN13;
	GPIOBTN.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
	GPIOBTN.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOBTN.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOBTN);



	while(1)
	{

	}



}
