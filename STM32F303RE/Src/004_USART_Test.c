/*
 * 004_USART_Test.c
 *
 *  Created on: Dec 21, 2025
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
        for(i = 0; i < 8000; i++);
    }
}


int main()
{
	SysClk_Config();

	USART1_REG_RST();
	USART_ClkControl(USART1, ENABLE);


	GPIO_Handle_t GPIOTX;

	GPIOTX.pGPIOx = GPIOA;
	GPIOTX.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN9;
	GPIOTX.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIOTX.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIOTX.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIOTX.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIOTX.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF7;



	GPIO_Handle_t GPIORX;

	GPIORX.pGPIOx = GPIOA;
	GPIORX.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN10;
	GPIORX.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIORX.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIORX.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIORX.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
	GPIORX.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF7;



	GPIO_Handle_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOC;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN13;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GPIOBtn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;

	GPIO_Init(&GPIOBtn);
	GPIO_Init(&GPIOTX);
	GPIO_Init(&GPIORX);


	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioLed);


	USART_Handle_t USART1TEST;

	USART1TEST.pUSARTx = USART1;
	USART1TEST.USART_Config.USART_Baud = USART_BAUD_115200;
	USART1TEST.USART_Config.USART_Mode = USART_MODE_TX_RX;
	USART1TEST.USART_Config.USART_StopBits = USART_STOPBITS_1;
	USART1TEST.USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	USART1TEST.USART_Config.USART_HWFlowControl = USART_FLOWCTRL_DIS;
	USART1TEST.USART_Config.USART_ParityControl = USART_PARITYCTRL_DIS;


	USART_Init(&USART1TEST);


    uint8_t msg[] = "HELLO FROM STM32\r\n";
    uint8_t rxByte;

    while (1)
    {
        /* Send data to ESP32 */
        USART_SendData(&USART1TEST, msg, sizeof(msg) - 1);

        /* Receive ONE byte from ESP32 (blocking) */
        USART_ReceiveData(&USART1TEST, &rxByte, 1);

        /* Simple command handling */
        if (rxByte == 'L')   // ESP32 sends 'L'
        {
            GPIO_TogglePin(GPIOA, GPIO_PIN5);
        }

        delay_ms(300);
    }



}








