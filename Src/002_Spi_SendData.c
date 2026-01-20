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
	USART1_REG_RST();

	GPIO_Handle_t GPIO_SPI1_CS;

	GPIO_SPI1_CS.pGPIOx = GPIOA;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN4;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_CS.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;



	GPIO_Handle_t GPIO_SPI1_SCLK;

	GPIO_SPI1_SCLK.pGPIOx = GPIOA;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN5;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_SPI1_SCLK.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF5;



	GPIO_Handle_t GPIO_SPI1_MISO;

	GPIO_SPI1_MISO.pGPIOx = GPIOA;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN6;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_SPI1_MISO.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF5;



	GPIO_Handle_t GPIO_SPI1_MOSI;

	GPIO_SPI1_MOSI.pGPIOx = GPIOA;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN7;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFN;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GPIO_SPI1_MOSI.GPIO_PinConfig.GPIO_PinAltFunMode = GPIO_AF5;


	GPIO_Init(&GPIO_SPI1_CS);
	GPIO_Init(&GPIO_SPI1_SCLK);
	GPIO_Init(&GPIO_SPI1_MISO);
	GPIO_Init(&GPIO_SPI1_MOSI);



	SPI_Handle_t SPI1TEST;

	SPI1TEST.pSPIx = SPI1;
	SPI1TEST.SPIConfig.SPI_BusConfig = SPI_BUS_CONFIG_FD;
	SPI1TEST.SPIConfig.SPI_CPHA = SPI_CPHA_LOW;
	SPI1TEST.SPIConfig.SPI_CPOL = SPI_CPOL_LOW;
	SPI1TEST.SPIConfig.SPI_CRCEN = SPI_CRCDIS;
	SPI1TEST.SPIConfig.SPI_DS = SPI_DS_8BITS;
	SPI1TEST.SPIConfig.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER;
	SPI1TEST.SPIConfig.SPI_SSM = SPI_SSM_EN;
	SPI1TEST.SPIConfig.SPI_SclkSpeed = SPI_SCLK_SPEED_DIV8;


	SPI_Init(&SPI1TEST);



	uint8_t txBuf[4] = {0xA5, 0x5A, 0xAA, 0x55};
	uint8_t rxBuf[4];

	while (1)
	{
	    /* CS LOW → select ESP32 */
	    GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_RESET);

	    /* Send data to ESP32 */
	    SPI_SendData(SPI1, txBuf, sizeof(txBuf));

	    /* Receive data from ESP32 */
	    SPI_ReceiveData(SPI1, rxBuf, sizeof(rxBuf));

	    /* CS HIGH → deselect ESP32 */
	    GPIO_WritePin(GPIOA, GPIO_PIN4, GPIO_PIN_SET);

	    delay_ms(500);
	}




}
