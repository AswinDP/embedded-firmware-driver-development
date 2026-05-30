/*
 * stm32f303xx_i2c_driver.h
 *
 *  Created on: Dec 13, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_I2C_DRIVER_H_
#define INC_STM32F303XX_I2C_DRIVER_H_

#include "stm32f303xx.h"



typedef struct{

	uint32_t I2C_SCLSpeed;
	uint8_t I2C_DeviceAddress;
	uint8_t I2C_AnalogFilter;
	uint8_t I2C_DigitalFilter;
	uint8_t I2C_NoStretch;

}I2C_Config_t;


typedef struct{

	I2C_Regs_t *pI2Cx;
	I2C_Config_t I2C_Config;

}I2C_Handle_t;



#define I2C_SCL_SPEED_SM10kHz				0   //32 bit value for I2C_TIMINGR Register
#define I2C_SCL_SPEED_SM100kHz				1  //with proper SCLL, SCLH etc for 8Mhz
#define I2C_SCL_SPEED_FM400kHz				2    //APB1 Bus
#define I2C_SCL_SPEED_FMP500kHz				3


#define I2C_ANALOG_FILTER_ENABLE			0
#define I2C_ANALOG_FILTER_DISABLE			1


#define I2C_STRETCH_ENABLE					0
#define I2C_STRETCH_DISABLE					1


#define I2C_DIGITAL_FILTER_0  				0
#define I2C_DIGITAL_FILTER_1 				1
#define I2C_DIGITAL_FILTER_2  				2
#define I2C_DIGITAL_FILTER_3 				3
#define I2C_DIGITAL_FILTER_4  				4
#define I2C_DIGITAL_FILTER_5				5
#define I2C_DIGITAL_FILTER_6 				6
#define I2C_DIGITAL_FILTER_7 			    7
#define I2C_DIGITAL_FILTER_8  			    8
#define I2C_DIGITAL_FILTER_9  				9
#define I2C_DIGITAL_FILTER_10  			   	10
#define I2C_DIGITAL_FILTER_11 				11
#define I2C_DIGITAL_FILTER_12  				12
#define I2C_DIGITAL_FILTER_13 				13
#define I2C_DIGITAL_FILTER_14			  	14
#define I2C_DIGITAL_FILTER_15				15




void I2C_Init(I2C_Handle_t *pI2CHandle);
void I2C_DeInit(I2C_Regs_t *pI2Cx);
void I2C_ClkControl(I2C_Regs_t *pI2Cx, uint8_t EnorDi);
void I2C_SlaveSendData(I2C_Regs_t *pI2Cx, uint8_t data);
uint8_t I2C_SlaveReceiveData(I2C_Regs_t *pI2Cx);
void I2C_MasterSendData(I2C_Regs_t *pI2Cx, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr);
void I2C_MasterReceiveData(I2C_Regs_t *pI2Cx, uint8_t *pRxBuffer, uint32_t Len, uint8_t SlaveAddr);
























#endif /* INC_STM32F303XX_I2C_DRIVER_H_ */
