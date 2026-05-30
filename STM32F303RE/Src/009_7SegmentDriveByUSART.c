/*
 * 009_7SegmentDriveByUSART.c
 *
 *  Created on: Jan 7, 2026
 *      Author: aswin
 */


#include "stm32f303xx.h"



void vApplicationStackOverflowHook(void)			//Just for RTOS
{
    while (1);
}


void delay_ms(uint32_t ms)
{
    volatile uint32_t i;
    while(ms--)
    {
        for(i = 0; i < 1000; i++);
    }
}


int main()
{
	SysClk_Config();
	GPIOC_REG_RST();
	GPIOA_REG_RST();
	USART1_REG_RST();
	USART_ClkControl(USART1, ENABLE);


//    GPIO_Handle_t GPIOLED;                                     //TEST PURPOSE
//    GPIOLED.pGPIOx = GPIOA;
//    GPIOLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN5;
//    GPIOLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
//    GPIOLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
//    GPIOLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
//    GPIOLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
//    GPIO_Init(&GPIOLED);


	GPIO_Handle_t GPIOTX;

	GPIOTX.pGPIOx = GPIOA;
	GPIOTX.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN9;
	GPIOTX.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIOTX.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOTX.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOTX.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIOTX.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF7;


	GPIO_Handle_t GPIOCOUNT;

	GPIOCOUNT.pGPIOx = GPIOC;
	GPIOCOUNT.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN2;
	GPIOCOUNT.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOCOUNT.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOCOUNT.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;


	GPIO_Handle_t GPIOSEND;

	GPIOSEND.pGPIOx = GPIOC;
	GPIOSEND.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN3;
	GPIOSEND.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOSEND.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_HIGH;
	GPIOSEND.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GPIOCOUNT);
	GPIO_Init(&GPIOSEND);
	GPIO_Init(&GPIOTX);


	USART_Handle_t USART1TEST;

	USART1TEST.pUSARTx = USART1;
	USART1TEST.USART_Config.USART_Baud = USART_BAUD_115200;
	USART1TEST.USART_Config.USART_Mode = USART_MODE_TX_ONLY;
	USART1TEST.USART_Config.USART_StopBits = USART_STOPBITS_1;
	USART1TEST.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	USART1TEST.USART_Config.USART_HWFlowControl = USART_FLOWCTRL_DIS;
	USART1TEST.USART_Config.USART_ParityControl = USART_PARITYCTRL_DIS;


	USART_Init(&USART1TEST);

	uint8_t Value = 0;

	uint8_t count_pressed = 0;
	uint8_t send_pressed  = 0;

	while (1)
	{
	    /* ---------- COUNT BUTTON (PC2) ---------- */
	    if (GPIO_ReadPin(GPIOC, GPIO_PIN2) == GPIO_PIN_RESET)
	    {
	        if (!count_pressed)          // edge detect
	        {
	            Value++;
	            count_pressed = 1;
	        }
	    }
	    else
	    {
	        count_pressed = 0;           // button released
	    }

	    /* ---------- SEND BUTTON (PC3) ---------- */
	    if (GPIO_ReadPin(GPIOC, GPIO_PIN3) == GPIO_PIN_RESET)
	    {
	        if (!send_pressed)
	        {
	            USART_SendData(&USART1TEST, &Value, 1);
	            Value = 0;
	            send_pressed = 1;
	        }
	    }
	    else
	    {
	        send_pressed = 0;
	    }

	    delay_ms(20);    // basic debounce
	}



}





