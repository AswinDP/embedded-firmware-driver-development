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



}














