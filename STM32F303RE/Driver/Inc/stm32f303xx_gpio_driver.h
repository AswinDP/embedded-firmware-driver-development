/*
 * stm32f303xx_gpio_driver.h
 *
 *  Created on: Nov 5, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_GPIO_DRIVER_H_
#define INC_STM32F303XX_GPIO_DRIVER_H_



#include "stm32f303xx.h"


typedef struct{

	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;


typedef struct{

	GPIO_Regs_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handle_t;

/*
 * @GPIO_PIN_NUMBERS
 * GPIO pin numbers
 */
#define GPIO_PIN0  				0
#define GPIO_PIN1  				1
#define GPIO_PIN2  				2
#define GPIO_PIN3  				3
#define GPIO_PIN4  				4
#define GPIO_PIN5  				5
#define GPIO_PIN6  				6
#define GPIO_PIN7  				7
#define GPIO_PIN8  				8
#define GPIO_PIN9  				9
#define GPIO_PIN10  			10
#define GPIO_PIN11 				11
#define GPIO_PIN12  			12
#define GPIO_PIN13 				13
#define GPIO_PIN14 				14
#define GPIO_PIN15 				15

/*
 * @GPIO_PIN_MODES
 * GPIO pin possible modes
 */
#define GPIO_MODE_IN 		0
#define GPIO_MODE_OUT 		1
#define GPIO_MODE_ALTFN 	2
#define GPIO_MODE_ANALOG 	3
#define GPIO_MODE_IT_FT     4
#define GPIO_MODE_IT_RT     5
#define GPIO_MODE_IT_RFT    6


/*
 * GPIO pin possible output types
 */
#define GPIO_OP_TYPE_PP   0
#define GPIO_OP_TYPE_OD   1


/*
 * @GPIO_PIN_SPEED
 * GPIO pin possible output speeds
 */
#define GPIO_SPEED_LOW			0
#define GPIO_SPEED_MEDIUM		1
#define GPIO_SPEED_FAST			2
#define GPIO_SPEED_HIGH			3


/*
 * GPIO pin pull up AND pull down configuration macros
 */
#define GPIO_NO_PUPD   		0
#define GPIO_PIN_PU			1
#define GPIO_PIN_PD			2


/*
 * GPIO pin Alternate Function macros
 */
#define GPIO_AF0				0
#define GPIO_AF1				1
#define GPIO_AF2				2
#define GPIO_AF3				3
#define GPIO_AF4				4
#define GPIO_AF5				5
#define GPIO_AF6				6
#define GPIO_AF7				7
#define GPIO_AF8				8
#define GPIO_AF9				9
#define GPIO_AF10				10
#define GPIO_AF11				11
#define GPIO_AF12				12
#define GPIO_AF13				13
#define GPIO_AF14				14
#define GPIO_AF15				15


//Funtions for various API


void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_Regs_t *pGPIOx);
void GPIO_ClkControl(GPIO_Regs_t *pGPIOx, uint8_t EnorDi);
uint8_t GPIO_ReadPin(GPIO_Regs_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadPort(GPIO_Regs_t *pGPIOx);
void GPIO_WritePin(GPIO_Regs_t *pGPIOx, uint8_t PinNumber, uint8_t Value);
void GPIO_WritePort(GPIO_Regs_t *pGPIOx, uint8_t Value);
void GPIO_TogglePin(GPIO_Regs_t *pGPIOx, uint8_t PinNumber);
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnorDi);
void GPIO_IRQHandling(uint8_t PinNumber);





























#endif /* INC_STM32F303XX_GPIO_DRIVER_H_ */
