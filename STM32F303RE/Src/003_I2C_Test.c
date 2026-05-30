/*
 * 003_I2C_Test.c
 *
 *  Created on: Dec 17, 2025
 *      Author: aswin
 */


#include "stm32f303xx.h"

#define SLAVE_ADDR			0x20	//ESP32

void delay_ms(uint32_t ms)
{
    volatile uint32_t i;
    while(ms--)
    {
        for(i = 0; i < 8000; i++);
    }
}


//void scanButtonsAndStore(void)
//{
//    if (keyIndex >= MAX_KEYS)
//        return;
//
//    if (GPIO_ReadPin(GPIOA, GPIO_PIN0) == 0) {
//        keyBuf[keyIndex++] = 1;
//        delay_ms(200);   // debounce
//    }
//    else if (GPIO_ReadPin(GPIOA, GPIO_PIN1) == 0) {
//        keyBuf[keyIndex++] = 2;
//        delay_ms(200);
//    }
//    else if (GPIO_ReadPin(GPIOA, GPIO_PIN2) == 0) {
//        keyBuf[keyIndex++] = 3;
//        delay_ms(200);
//    }
//}



int main()
{
	GPIO_Handle_t GPIOSCL;

	GPIOSCL.pGPIOx = GPIOB;
	GPIOSCL.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN6;
	GPIOSCL.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIOSCL.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	GPIOSCL.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GPIOSCL.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOSCL.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF4;


	GPIO_Handle_t GPIOSDA;

	GPIOSDA.pGPIOx = GPIOB;
	GPIOSDA.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN7;
	GPIOSDA.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIOSDA.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_MEDIUM;
	GPIOSDA.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_OD;
	GPIOSDA.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIOSDA.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF4;


	GPIO_Init(&GPIOSCL);
	GPIO_Init(&GPIOSDA);


	I2C_Handle_t I2C1ESP;

	I2C1ESP.pI2Cx = I2C1;
	I2C1ESP.I2C_Config.I2C_DeviceAddress = 0x30; // STM32
	I2C1ESP.I2C_Config.I2C_SCLSpeed = I2C_SCL_SPEED_SM100kHz;
	I2C1ESP.I2C_Config.I2C_NoStretch = I2C_STRETCH_ENABLE;
	I2C1ESP.I2C_Config.I2C_AnalogFilter = I2C_ANALOG_FILTER_ENABLE;
	I2C1ESP.I2C_Config.I2C_DigitalFilter = I2C_DIGITAL_FILTER_0;


	I2C_Init (&I2C1ESP);

	while (1)
	{
	    uint8_t data[10] = {1,2,3,4,5,6,7,8,9,0};

	    for (uint8_t i = 0; i < 10; i++)
	    {
	        I2C_MasterSendData(I2C1, &data[i], 1, SLAVE_ADDR);
	        delay_ms(500);
	    }
	}


}
