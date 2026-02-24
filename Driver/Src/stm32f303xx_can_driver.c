/*
 * stm32f303xx_can_driver.c
 *
 *  Created on: Jan 31, 2026
 *      Author: aswin
 */

#include "stm32f303xx.h"





void CAN_ClkControl(CAN_Regs_t *pCANx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		CAN_CLK_EN();
	}

	else
	{
		CAN_CLK_DI();
	}
}



CAN_Status_t CAN_Init(CAN_Handle_t *CANx)
{
	CAN_ClkControl(CANx->pCANx, ENABLE);
	CANx->State = CAN_STATE_SLEEP;    //By default CAN lands in Sleep Mode after a reset

	//Leave Sleep mode and enter Initialization mode

	CANx->pCANx->MCR &= ~(1 << 1);
	CANx->pCANx->MCR |= (1 << 0);
	while(!(CANx->pCANx->MSR & (1 << 0)));
	CANx->State = CAN_STATE_INIT;


	//CAN Initialization

	uint32_t temp = 0;

	temp |= ((CANx->Config.Prescaler - 1) << 0);
	temp |= (CANx->Config.BS1 << 16);
	temp |= (CANx->Config.BS2 << 20);
	temp |= (CANx->Config.SJW << 24);
	temp |= (CANx->Config.Mode << 30);

	CANx->pCANx->BTR = temp;

	temp =0;

	temp |= (CANx->Config.TTCM << 7);
	temp |= (CANx->Config.ABOM << 6);
	temp |= (CANx->Config.AWUM << 5);
	temp |= (CANx->Config.NART << 4);
	temp |= (CANx->Config.RFLM << 3);
	temp |= (CANx->Config.TXFP << 2);

	CANx->pCANx->MCR |= temp;

	return CAN_OK;
}














