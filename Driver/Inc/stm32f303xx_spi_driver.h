/*
 * stm32f303xx_spi_driver.h
 *
 *  Created on: Dec 10, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_SPI_DRIVER_H_
#define INC_STM32F303XX_SPI_DRIVER_H_
#include "stm32f303xx.h"


typedef struct{

	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_CRCEN;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
	uint8_t SPI_DS;

}SPI_Config_t;


typedef struct{

	SPI_Regs_t *pSPIx;
	SPI_Config_t SPIConfig;

}SPI_Handle_t;


//SPI Device Mode
#define SPI_DEVICE_MODE_SLAVE				0
#define SPI_DEVICE_MODE_MASTER				1


//SPI BusConfig
#define SPI_BUS_CONFIG_FD					0
#define SPI_BUS_CONFIG_HD					1
#define SPI_BUS_CONFIG_Srx					2


//SPI SClkSpeed
#define SPI_SCLK_SPEED_DIV2					0
#define SPI_SCLK_SPEED_DIV4					1
#define SPI_SCLK_SPEED_DIV8					2
#define SPI_SCLK_SPEED_DIV16				3
#define SPI_SCLK_SPEED_DIV32				4
#define SPI_SCLK_SPEED_DIV64				5
#define SPI_SCLK_SPEED_DIV128				6
#define SPI_SCLK_SPEED_DIV256				7


//SPI CRCEN
#define SPI_CRCDIS							0
#define SPI_CRCEN_8BITS						1
#define SPI_CRCEN_16BITS					2


//SPI DS
#define SPI_DS_4BITS						3
#define SPI_DS_5BITS						4
#define SPI_DS_6BITS						5
#define SPI_DS_7BITS						6
#define SPI_DS_8BITS						7
#define SPI_DS_9BITS						8
#define SPI_DS_10BITS						9
#define SPI_DS_11BITS						10
#define SPI_DS_12BITS						11
#define SPI_DS_13BITS						12
#define SPI_DS_14BITS						13
#define SPI_DS_15BITS						14
#define SPI_DS_16BITS						15


//SPI CPOL
#define SPI_CPOL_LOW						0
#define SPI_CPOL_HIGH						1


//SPI CPHA
#define SPI_CPHA_LOW						0
#define SPI_CPHA_HIGH						1


//SPI SSM
#define SPI_SSM_DI							0
#define SPI_SSM_EN							1


//API Prototypes

void SPI_Init(SPI_Handle_t *pSPIHandle);
void SPI_DeInit(SPI_Regs_t *pSPIx);
void SPI_ClkControl(SPI_Regs_t *pSPIx, uint8_t EnorDi);

void SPI_SendData(SPI_Regs_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_Regs_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

void SPI_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void SPI_IRQHandling(SPI_Handle_t *pHandle);




















#endif /* INC_STM32F303XX_SPI_DRIVER_H_ */
