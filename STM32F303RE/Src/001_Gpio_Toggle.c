/*
 * 001_Gpio_Toggle.c
 *
 *  Created on: Dec 9, 2025
 *      Author: aswin
 */


#include "stm32f303xx.h"

void vApplicationStackOverflowHook(void)			//Just for RTOS
{
    while (1);
}



void delay(int x)
{
	for(uint32_t i = 0; i < (x*1000); i++);
}

int main(void)
{

	GPIO_Handle_t GPIOLED;

	GPIOLED.pGPIOx = GPIOA;
	GPIOLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN5;
	GPIOLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIOLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_ClkControl(GPIOA, ENABLE);
	GPIO_Init(&GPIOLED);


	while(1)
	{
		GPIO_TogglePin(GPIOA, GPIO_PIN5);
		delay(500);
	}
}

















