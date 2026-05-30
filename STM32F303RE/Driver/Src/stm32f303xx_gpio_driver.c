/*
 * stm32f303xx_gpio_driver.c
 *
 *  Created on: Nov 5, 2025
 *      Author: aswin
 */


#include "stm32f303xx_gpio_driver.h"






void GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
	 //enable the peripheral clock

	GPIO_ClkControl(pGPIOHandle->pGPIOx, ENABLE);

	 uint32_t temp=0; //temp. register



	//1 . configure the mode of gpio pin

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG)
	{
		//the non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber ) );
		pGPIOHandle->pGPIOx->MODER &= ~( 0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
		pGPIOHandle->pGPIOx->MODER |= temp; //setting

	}
	else
	{
	    uint8_t pin = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber;
	    uint8_t port = GPIO_BASEADDR_TO_PORTCODE(pGPIOHandle->pGPIOx);

	    /* 1. Configure EXTI GPIO mapping */
	    EXTI_ConfigGPIO(pin, port);

	    /* 2. Configure trigger selection */
	    if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT)
	    {
	        EXTI_ConfigTrigger(pin, EXTI_TRIGGER_FALLING);
	    }
	    else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT)
	    {
	        EXTI_ConfigTrigger(pin, EXTI_TRIGGER_RISING);
	    }
	    else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT)
	    {
	        EXTI_ConfigTrigger(pin, EXTI_TRIGGER_RISING_FALLING);
	    }

	    /* 3. Enable EXTI interrupt */
	    EXTI_EnableInterrupt(pin);
	}


	//2. configure the speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->OSPEEDR &= ~( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	//3. configure the pupd settings
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) );
	pGPIOHandle->pGPIOx->PUPDR &= ~( 0x3 << ( 2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); //clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp;


	//4. configure the optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber );
	pGPIOHandle->pGPIOx->OTYPER &= ~( 0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); //clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	//5. configure the alt functionality
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN)
	{
		//configure the alt function registers.
		uint8_t temp1, temp2;

		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber  % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << ( 4 * temp2 ) ); //clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << ( 4 * temp2 ) );
	}

}


void GPIO_DeInit(GPIO_Regs_t *pGPIOx)
{

	if(pGPIOx == GPIOA)
	{
		GPIOA_REG_RST();
	}
	else if(pGPIOx == GPIOB)
	{
		GPIOB_REG_RST();
	}
	else if(pGPIOx == GPIOC)
	{
		GPIOC_REG_RST();
	}
	else if(pGPIOx == GPIOD)
	{
		GPIOD_REG_RST();
	}
	else if(pGPIOx == GPIOE)
	{
		GPIOE_REG_RST();
	}
	else if(pGPIOx == GPIOF)
	{
		GPIOF_REG_RST();
	}
	else if(pGPIOx == GPIOG)
	{
		GPIOG_REG_RST();
	}
	else if(pGPIOx == GPIOH)
	{
		GPIOH_REG_RST();
	}

}


void GPIO_ClkControl(GPIO_Regs_t *pGPIOx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_CLK_EN();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_CLK_EN();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_CLK_EN();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_CLK_EN();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_CLK_EN();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_CLK_EN();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_CLK_EN();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_CLK_EN();
		}
	}

	else
	{
		if(pGPIOx == GPIOA)
		{
			GPIOA_CLK_DI();
		}
		else if(pGPIOx == GPIOB)
		{
			GPIOB_CLK_DI();
		}
		else if(pGPIOx == GPIOC)
		{
			GPIOC_CLK_DI();
		}
		else if(pGPIOx == GPIOD)
		{
			GPIOD_CLK_DI();
		}
		else if(pGPIOx == GPIOE)
		{
			GPIOE_CLK_DI();
		}
		else if(pGPIOx == GPIOF)
		{
			GPIOF_CLK_DI();
		}
		else if(pGPIOx == GPIOG)
		{
			GPIOG_CLK_DI();
		}
		else if(pGPIOx == GPIOH)
		{
			GPIOH_CLK_DI();
		}
	}
}


uint8_t GPIO_ReadPin(GPIO_Regs_t *pGPIOx, uint8_t PinNumber)
{

	uint8_t value;
	value = (uint8_t)((pGPIOx -> IDR >> PinNumber) & 0x00000001);
	return value;

}


uint16_t GPIO_ReadPort(GPIO_Regs_t *pGPIOx)
{

	return (uint16_t)(pGPIOx -> IDR);

}


void GPIO_WritePin(GPIO_Regs_t *pGPIOx, uint8_t PinNumber, uint8_t Value)
{

	if(Value == SET)
	{
		pGPIOx -> ODR |= (1 << PinNumber);
	}
	else
	{
		pGPIOx -> ODR &= ~(1 << PinNumber);
	}

}


void GPIO_WritePort(GPIO_Regs_t *pGPIOx, uint8_t Value)
{

	pGPIOx -> ODR = Value;

}


void GPIO_TogglePin(GPIO_Regs_t *pGPIOx, uint8_t PinNumber)
{

	pGPIOx -> ODR ^= (1 << PinNumber);

}


void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi)
{

}


void GPIO_IRQHandling(uint8_t PinNumber)
{

}




