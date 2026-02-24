/*
 * stm32f303xx_can_driver.c
 *
 *  Created on: Jan 31, 2026
 *      Author: aswin
 */

#include "stm32f303xx.h"

CAN_Handle_t CANx = {0};



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
	if((CANx->State == CAN_STATE_RESET) || (CANx->State == CAN_STATE_SLEEP))
	{
		if(CANx->State == CAN_STATE_RESET)
		{
			CAN_ClkControl(CANx->pCANx, ENABLE);
			CANx->State = CAN_STATE_SLEEP;    //By default CAN lands in Sleep Mode after a reset
		}

		//Leave Sleep mode and enter Initialization mode

		CANx->pCANx->MCR &= ~(1 << 1);  		//SLEEP
		CANx->pCANx->MCR |= (1 << 0);   		//INRQ
		while(!(CANx->pCANx->MSR & (1 << 0)));	//INAK
		CANx->State = CAN_STATE_INIT;
	}

	else if(CANx->State == CAN_STATE_NORMAL)
	{
		//Leave Normal mode and enter Initialization mode

		CANx->pCANx->MCR |= (1 << 0);			//INRQ
		while(!(CANx->pCANx->MSR & (1 << 0)));	//INAK
		CANx->State = CAN_STATE_INIT;
	}

	//CAN Initialization - STATE = INITIALIZATION at this moment

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


CAN_Status_t CAN_DeInit(CAN_Handle_t *CANx)
{
    CAN_CLK_RST();
    CAN_ClkControl(CANx->pCANx, DISABLE);
    CANx->State = CAN_STATE_RESET;

    return CAN_OK;
}


CAN_Status_t CAN_Start(CAN_Handle_t *CANx)
{
	if(CANx->State == CAN_STATE_INIT)
	{
		//Leave INITIALIZATION mode and enter NORMAL mode
		CANx->pCANx->MCR &= ~(1 << 1); 		 	//SLEEP
		CANx->pCANx->MCR &= ~(1 << 0);   		//INRQ
		while(CANx->pCANx->MSR & (1 << 0));	//INAK
		CANx->State = CAN_STATE_NORMAL;
	}

	else
	{
		return CAN_ERROR;
	}

	return CAN_OK;
}


CAN_Status_t CAN_Stop(CAN_Handle_t *CANx)
{
	if(CANx->State == CAN_STATE_NORMAL)
	{
		//Leave NORMAL mode and enter INITIALIZATION mode
		CANx->pCANx->MCR |= (1 << 0);   		//INRQ
		while(!(CANx->pCANx->MSR & (1 << 0)));	//INAK
		CANx->State = CAN_STATE_INIT;
	}

	else
	{
		return CAN_ERROR;
	}

	return CAN_OK;
}


CAN_Status_t CAN_RequestSleep(CAN_Handle_t *CANx)
{
	if(CANx->State == CAN_STATE_INIT)
	{
		//Leave INITIALIZATION mode and enter SLEEP mode
		CANx->pCANx->MCR &= ~(1 << 0);   		//INRQ
		CANx->pCANx->MCR |= (1 << 1); 		 	//SLEEP
		while(!(CANx->pCANx->MSR & (1 << 1)));	//SLAK
		CANx->State = CAN_STATE_SLEEP;
	}

	else if(CANx->State == CAN_STATE_NORMAL)
	{
		//Leave NORMAL mode and enter SLEEP mode
		CANx->pCANx->MCR |= (1 << 1); 		 	//SLEEP
		CANx->pCANx->MCR &= ~(1 << 0);   		//INRQ
		while(!(CANx->pCANx->MSR & (1 << 1)));	//SLAK
		CANx->State = CAN_STATE_SLEEP;
	}

	else
	{
		return CAN_ERROR;
	}

	return CAN_OK;
}


CAN_Status_t CAN_WakeUp(CAN_Handle_t *CANx)
{
	if(CANx->State == CAN_STATE_SLEEP)
	{
		//Leave SLEEP mode and enter NORMAL mode
		CANx->pCANx->MCR &= ~(1 << 1); 		 	//SLEEP
		CANx->pCANx->MCR &= ~(1 << 0);   		//INRQ
		while(CANx->pCANx->MSR & (1 << 1));		//SLAK
		CANx->State = CAN_STATE_NORMAL;
	}

	else
	{
		return CAN_ERROR;
	}

	return CAN_OK;
}


CAN_State_t  CAN_GetState(CAN_Handle_t *CANx)
{
	return (CANx->State);
}






















