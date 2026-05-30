/*
 * stm32f303xx_usart_driver.h
 *
 *  Created on: Dec 20, 2025
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_USART_DRIVER_H_
#define INC_STM32F303XX_USART_DRIVER_H_


typedef struct{

	uint8_t USART_Mode;
	uint32_t USART_Baud;
	uint8_t USART_StopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;

}USART_Config_t;


typedef struct{

	USART_Regs_t *pUSARTx;
	USART_Config_t USART_Config;

}USART_Handle_t;



#define USART_MODE_RX_ONLY				0
#define USART_MODE_TX_ONLY				1
#define USART_MODE_TX_RX				2

// USART BRR values calculated for 8 MHz peripheral clock
// Oversampling = 16
#define USART_BAUD_2400        0x0D05
#define USART_BAUD_4800        0x0682
#define USART_BAUD_9600        0x0341
#define USART_BAUD_19200       0x01A0
#define USART_BAUD_38400       0x00D0
#define USART_BAUD_57600       0x008A
#define USART_BAUD_115200      0x0045
#define USART_BAUD_230400      0x0022
#define USART_BAUD_460800      0x0011


#define USART_STOPBITS_1				0
#define USART_STOPBITS_0_5				1
#define USART_STOPBITS_2				2
#define USART_STOPBITS_1_5				3

#define USART_WORDLEN_8BITS				0
#define USART_WORDLEN_9BITS				1
#define USART_WORDLEN_7BITS				2

#define USART_PARITYCTRL_DIS			0
#define USART_PARITYCTRL_EN_EVEN		1
#define USART_PARITYCTRL_EN_ODD			2

#define USART_FLOWCTRL_DIS				0
#define USART_FLOWCTRL_EN				1


void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_Regs_t *pUSARTx);
void USART_ClkControl(USART_Regs_t *pUSARTx, uint8_t EnorDi);
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);



#endif /* INC_STM32F303XX_USART_DRIVER_H_ */
