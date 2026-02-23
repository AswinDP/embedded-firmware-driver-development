/*
 * stm32f303xx_can_driver.h
 *
 *  Created on: Jan 31, 2026
 *      Author: aswin
 */

#ifndef INC_STM32F303XX_CAN_DRIVER_H_
#define INC_STM32F303XX_CAN_DRIVER_H_

typedef struct
{
    /* -------- Bit Timing -------- */
    uint16_t Prescaler;
    uint8_t  SJW;
    uint8_t  BS1;
    uint8_t  BS2;

    /* -------- Operating Mode -------- */
    uint8_t  Mode;

    /* -------- Feature Control -------- */
    uint8_t  TTCM;
    uint8_t  ABOM;
    uint8_t  AWUM;
    uint8_t  NART;
    uint8_t  RFLM;
    uint8_t  TXFP;

} CAN_Config_t;



typedef struct
{
    uint8_t  FilterBank;
    uint8_t  FilterMode;       // Mask or List
    uint8_t  FilterScale;      // 16-bit or 32-bit
    uint32_t FilterID;
    uint32_t FilterMask;
    uint8_t  FIFOAssignment;
    uint8_t  Activation;

} CAN_FilterConfig_t;



typedef struct
{
    uint32_t StdId;
    uint32_t ExtId;
    uint8_t  IDE;
    uint8_t  RTR;
    uint8_t  DLC;
    uint8_t  Data[8];

} CAN_TxMsg_t;



typedef struct{

	CAN_Regs_t *pCANx;
	CAN_Config_t CAN_Config;
	CAN_FilterConfig_t CAN_FilterConfig;
	CAN_TxMsg_t CAN_TxMsg;

}CAN_Handle_t;























#endif /* INC_STM32F303XX_CAN_DRIVER_H_ */
