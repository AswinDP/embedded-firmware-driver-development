/*
 * 002_Spi_SendData.c
 *
 *  Created on: Dec 12, 2025
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
	GPIOA_REG_RST();
	GPIOB_REG_RST();
	SPI2_REG_RST();

	GPIOA_CLK_EN();
	GPIOB_CLK_EN();
	SPI2_CLK_EN();


	GPIO_Handle_t GPIO_SPI1_CS;

	GPIO_SPI1_CS.pGPIOx = GPIOA;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN4;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;



	GPIO_Handle_t GPIO_SPI1_SCLK;

	GPIO_SPI1_SCLK.pGPIOx = GPIOB;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN13;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF5;



	GPIO_Handle_t GPIO_SPI1_MISO;

	GPIO_SPI1_MISO.pGPIOx = GPIOB;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN14;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF5;



	GPIO_Handle_t GPIO_SPI1_MOSI;

	GPIO_SPI1_MOSI.pGPIOx = GPIOB;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN15;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF5;


	GPIO_Init(&GPIO_SPI1_CS);
	GPIO_Init(&GPIO_SPI1_SCLK);
	GPIO_Init(&GPIO_SPI1_MISO);
	GPIO_Init(&GPIO_SPI1_MOSI);


	GPIO_Handle_t GpioLed;

	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN5;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_LOW;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;

	GPIO_Init(&GpioLed);


	SPI_Handle_t SPI2TEST;

	SPI2TEST.pSPIx = SPI2;
	SPI2TEST.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI2TEST.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI2TEST.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI2TEST.SPIConfig.SPI_CRCEN = SPI_CRCDIS;
	SPI2TEST.SPIConfig.SPI_DS = SPI_DS_8BITS;
	SPI2TEST.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI2TEST.SPIConfig.SPI_SSM = SPI_SSM_EN;
	SPI2TEST.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;


	SPI_Init(&SPI2TEST);



	uint8_t txBuf[4] = {0x01, 0x02, 0x03, 0x04};
	uint8_t rxBuf[4];

	while (1)
	{
	    // CS LOW
	    GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_RESET);

	    // Phase 1: Send command/data to ESP32
	    SPI_SendData(SPI2, txBuf, 4);

	    // Phase 2: Receive response from ESP32
	    SPI_ReceiveData(SPI2, rxBuf, 4);

	    // CS HIGH
	    GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_SET);

	    // Blink LED based on received value (1–5)
	    uint8_t blinkCount = rxBuf[0];

	    if (blinkCount >= 1 && blinkCount <= 5)
	    {
	        for (uint8_t i = 0; i < blinkCount; i++)
	        {
	            GPIO_WritePin(GPIOA, GPIO_PIN5, GPIO_PIN_SET);
	            delay_ms(200);
	            GPIO_WritePin(GPIOA, GPIO_PIN5, GPIO_PIN_RESET);
	            delay_ms(200);
	        }
	    }

	    delay_ms(1000);
	}


}
