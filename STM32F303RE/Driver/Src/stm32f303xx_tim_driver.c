/*
 * stm32f303xx_tim_driver.c
 *
 *  Created on: Dec 23, 2025
 *      Author: aswin
 */


#include "stm32f303xx_tim_driver.h"


void GP1TIM_PeriClockControl(GP1_TIM_Regs_t *pTIMx, uint8_t EnorDi)
{

	if(EnorDi == ENABLE)
		{
			if(pTIMx == TIM2)
			{
				TIM2_CLK_EN();
			}
			else if(pTIMx == TIM3)
			{
				TIM3_CLK_EN();
			}
			else if(pTIMx == TIM4)
			{
				TIM4_CLK_EN();
			}
		}

	else
		{
			if(pTIMx == TIM2)
			{
				TIM2_CLK_DI();
			}
			else if(pTIMx == TIM3)
			{
				TIM3_CLK_DI();
			}
			else if(pTIMx == TIM4)
			{
				TIM4_CLK_DI();
			}
		}
}


void GP1TIM_Init(GP1_TIM_Handle_t *pTIMHandle)
{

	GP1TIM_PeriClockControl(pTIMHandle->pGP1TIMx, ENABLE);

	pTIMHandle->pGP1TIMx->CR1 &= ~(1 << GP1_TIM_CR1_CEN);
	uint32_t temp = 0;

	temp |= (pTIMHandle->GP1_TIM_Config.GP1TIM_ClockDivision << GP1_TIM_CR1_CKD);
	temp |= (1 << GP1_TIM_CR1_ARPE);

	temp &= ~(3 << GP1_TIM_CR1_CMS);
	temp |= (pTIMHandle->GP1_TIM_Config.GP1TIM_CounterMode << GP1_TIM_CR1_DIR);

	pTIMHandle->pGP1TIMx->CR1 = temp;

	pTIMHandle->pGP1TIMx->PSC = pTIMHandle->GP1_TIM_Config.GP1TIM_Prescaler;
	pTIMHandle->pGP1TIMx->ARR = pTIMHandle->GP1_TIM_Config.GP1TIM_AutoReload;

	pTIMHandle->pGP1TIMx->EGR |= (1 << GP1_TIM_EGR_UG);
	while(!(pTIMHandle->pGP1TIMx->SR & (1 << GP1_TIM_SR_UIF)));
	pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_UIF);
	pTIMHandle->State = GP1TIM_STATE_RDY;

}


void GP1TIM_Start(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->State == GP1TIM_STATE_RDY)
	{
		pTIMHandle->pGP1TIMx->CR1 |= (1 << GP1_TIM_CR1_CEN);
		pTIMHandle->State = GP1TIM_STATE_BSY;
	}


}


void GP1TIM_Stop(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->State == GP1TIM_STATE_BSY)
	{
		pTIMHandle->pGP1TIMx->CR1 &= ~(1 << GP1_TIM_CR1_CEN);
		pTIMHandle->State = GP1TIM_STATE_RDY;
	}


}


uint32_t GP1TIM_GetCounterValue(GP1_TIM_Handle_t *pTIMHandle)
{
    return pTIMHandle->pGP1TIMx->CNT;
}


void GP1TIM_Delay_ms(GP1_TIM_Handle_t *pTIMHandle, uint32_t delay_ms)
{
	// Max delay using Delay_ms is ~65.5 seconds for 16-bit timers (TIM3, TIM4)
		//Assuming 8MHz Clock
	pTIMHandle->pGP1TIMx->PSC = 7999;
	pTIMHandle->pGP1TIMx->ARR = delay_ms - 1;

	pTIMHandle->pGP1TIMx->EGR |= (1 << GP1_TIM_EGR_UG);
	pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_UIF);

	GP1TIM_Start(pTIMHandle);

	while(!(pTIMHandle->pGP1TIMx->SR & (1 << GP1_TIM_SR_UIF)));
	pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_UIF);

	GP1TIM_Stop(pTIMHandle);
}


void GP1TIM_Delay_us(GP1_TIM_Handle_t *pTIMHandle, uint32_t delay_us)
{
	// Max delay using Delay_us is ~65 ms for 16-bit timers (TIM3, TIM4)
	// and ~71 minutes for 32-bit timer (TIM2, if configured as 32-bit)
//Assuming 8MHz Clock
	pTIMHandle->pGP1TIMx->PSC = 7;
	pTIMHandle->pGP1TIMx->ARR = delay_us - 1;

	pTIMHandle->pGP1TIMx->EGR |= (1 << GP1_TIM_EGR_UG);
	pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_UIF);

	GP1TIM_Start(pTIMHandle);

	while(!(pTIMHandle->pGP1TIMx->SR & (1 << GP1_TIM_SR_UIF)));
	pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_UIF);

	GP1TIM_Stop(pTIMHandle);
}


void GP1TIM_IC_Init(GP1_TIM_Handle_t *pTIMHandle)
{
	uint32_t temp;

	if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
	{
		pTIMHandle->pGP1TIMx->CCER &= ~(GP1_TIM_CCER_CC1E);

		temp = pTIMHandle->pGP1TIMx->CCMR1;
		temp &= ~(15 << GP1_TIM_CCMR1_IC1F);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICFilter << GP1_TIM_CCMR1_IC1F);
		temp &= ~(3 << GP1_TIM_CCMR1_IC1PSC);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPrescaler << GP1_TIM_CCMR1_IC1PSC);
		temp &= ~(3 << GP1_TIM_CCMR1_CC1S);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICSelection << GP1_TIM_CCMR1_CC1S);
		pTIMHandle->pGP1TIMx->CCMR1 = temp;

		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC1P);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC1NP);
		if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_FALLING)
		{
		    pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC1P);
		}
		else if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_BOTHEDGE)
		{
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC1P);
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC1NP);
		}

	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
	{
		pTIMHandle->pGP1TIMx->CCER &= ~(GP1_TIM_CCER_CC2E);

		temp = pTIMHandle->pGP1TIMx->CCMR1;
		temp &= ~(15 << GP1_TIM_CCMR1_IC2F);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICFilter << GP1_TIM_CCMR1_IC2F);
		temp &= ~(3 << GP1_TIM_CCMR1_IC2PSC);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPrescaler << GP1_TIM_CCMR1_IC2PSC);
		temp &= ~(3 << GP1_TIM_CCMR1_CC2S);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICSelection << GP1_TIM_CCMR1_CC2S);
		pTIMHandle->pGP1TIMx->CCMR1 = temp;

		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC2P);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC2NP);
		if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_FALLING)
		{
		    pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC2P);
		}
		else if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_BOTHEDGE)
		{
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC2P);
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC2NP);
		}
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
	{
		pTIMHandle->pGP1TIMx->CCER &= ~(GP1_TIM_CCER_CC3E);

		temp = pTIMHandle->pGP1TIMx->CCMR2;
		temp &= ~(15 << GP1_TIM_CCMR2_IC3F);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICFilter << GP1_TIM_CCMR2_IC3F);
		temp &= ~(3 << GP1_TIM_CCMR2_IC3PSC);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPrescaler << GP1_TIM_CCMR2_IC3PSC);
		temp &= ~(3 << GP1_TIM_CCMR2_CC3S);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICSelection << GP1_TIM_CCMR2_CC3S);
		pTIMHandle->pGP1TIMx->CCMR2 = temp;

		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC3P);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC3NP);
		if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_FALLING)
		{
		    pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC3P);
		}
		else if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_BOTHEDGE)
		{
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC3P);
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC3NP);
		}
	}
	else
	{
		pTIMHandle->pGP1TIMx->CCER &= ~(GP1_TIM_CCER_CC4E);

		temp = pTIMHandle->pGP1TIMx->CCMR2;
		temp &= ~(15 << GP1_TIM_CCMR2_IC4F);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICFilter << GP1_TIM_CCMR2_IC4F);
		temp &= ~(3 << GP1_TIM_CCMR2_IC4PSC);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPrescaler << GP1_TIM_CCMR2_IC4PSC);
		temp &= ~(3 << GP1_TIM_CCMR2_CC4S);
		temp |= (pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICSelection << GP1_TIM_CCMR2_CC4S);
		pTIMHandle->pGP1TIMx->CCMR2 = temp;

		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC4P);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC4NP);
		if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_FALLING)
		{
		    pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC4P);
		}
		else if(pTIMHandle->GP1_TIM_IC_Config.GP1TIM_ICPolarity == GP1_TIM_IC_POLARITY_BOTHEDGE)
		{
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC4P);
			pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC4NP);
		}
	}
}


void GP1TIM_IC_Start(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1OF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC1E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2OF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC2E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3OF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC3E);
	}
	else
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4OF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC4E);
	}
}


void GP1TIM_IC_Stop(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1OF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC1E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2OF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC2E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3OF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC3E);
	}
	else
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4OF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC4E);
	}
}


uint8_t GP1TIM_IC_IsCaptureFlagSet(GP1_TIM_Handle_t *pTIMHandle)
{
    uint32_t bit;

    switch (pTIMHandle->Channel)
    {
        case GP1_TIM_CHANNEL_1:
            bit = GP1_TIM_SR_CC1IF;
            break;

        case GP1_TIM_CHANNEL_2:
            bit = GP1_TIM_SR_CC2IF;
            break;

        case GP1_TIM_CHANNEL_3:
            bit = GP1_TIM_SR_CC3IF;
            break;

        case GP1_TIM_CHANNEL_4:
            bit = GP1_TIM_SR_CC4IF;
            break;

        default:
            return 0;   /* Invalid channel */
    }

    return (pTIMHandle->pGP1TIMx->SR & (1U << bit)) ? 1 : 0;
}


void GP1TIM_IC_ClearCaptureFlag(GP1_TIM_Handle_t *pTIMHandle)
{
    uint32_t bit;

    switch (pTIMHandle->Channel)
    {
        case GP1_TIM_CHANNEL_1:
            bit = GP1_TIM_SR_CC1IF;
            break;

        case GP1_TIM_CHANNEL_2:
            bit = GP1_TIM_SR_CC2IF;
            break;

        case GP1_TIM_CHANNEL_3:
            bit = GP1_TIM_SR_CC3IF;
            break;

        case GP1_TIM_CHANNEL_4:
            bit = GP1_TIM_SR_CC4IF;
            break;

        default:
            return;
    }

    /* Clear CCxIF */
    pTIMHandle->pGP1TIMx->SR &= ~(1U << bit);
}


uint32_t GP1TIM_IC_GetCaptureValue(GP1_TIM_Handle_t *pTIMHandle)
{
	uint32_t capture;

	if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
	{
		while(!(pTIMHandle->pGP1TIMx->SR & (1 << GP1_TIM_SR_CC1IF)));
		capture = pTIMHandle->pGP1TIMx->CCR1;
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1OF);

		return capture;
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
	{
		while(!(pTIMHandle->pGP1TIMx->SR & (1 << GP1_TIM_SR_CC2IF)));
		capture = pTIMHandle->pGP1TIMx->CCR2;
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2OF);

		return capture;
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
	{
		while(!(pTIMHandle->pGP1TIMx->SR & (1 << GP1_TIM_SR_CC3IF)));
		capture = pTIMHandle->pGP1TIMx->CCR3;
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3OF);

		return capture;
	}
	else
	{
		while(!(pTIMHandle->pGP1TIMx->SR & (1 << GP1_TIM_SR_CC4IF)));
		capture = pTIMHandle->pGP1TIMx->CCR4;
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4IF);
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4OF);

		return capture;
	}

	return 0;
}


/* Output Compare */
void GP1TIM_OC_Init(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->State == GP1TIM_STATE_RDY)
	{
		uint32_t temp;

		if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC1E);
			temp &= ~(1 << GP1_TIM_CCER_CC1NP);
			temp &= ~(1 << GP1_TIM_CCER_CC1P);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCPolarity << GP1_TIM_CCER_CC1P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR1;
			temp &= ~(3 << GP1_TIM_CCMR1_CC1S);
			temp |= (1 << GP1_TIM_CCMR1_OC1PE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC1FE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC1CE);
			temp &= ~(15 << GP1_TIM_CCMR1_OC1M);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCMode << GP1_TIM_CCMR1_OC1M);
			pTIMHandle->pGP1TIMx->CCMR1 = temp;

			pTIMHandle->pGP1TIMx->CCR1 = pTIMHandle->GP1_TIM_OC_Config.GP1TIM_Compare;

		}
		else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC2E);
			temp &= ~(1 << GP1_TIM_CCER_CC2NP);
			temp &= ~(1 << GP1_TIM_CCER_CC2P);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCPolarity << GP1_TIM_CCER_CC2P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR1;
			temp &= ~(3 << GP1_TIM_CCMR1_CC2S);
			temp |= (1 << GP1_TIM_CCMR1_OC2PE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC2FE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC2CE);
			temp &= ~(15 << GP1_TIM_CCMR1_OC2M);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCMode << GP1_TIM_CCMR1_OC2M);
			pTIMHandle->pGP1TIMx->CCMR1 = temp;

			pTIMHandle->pGP1TIMx->CCR2 = pTIMHandle->GP1_TIM_OC_Config.GP1TIM_Compare;

		}
		else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC3E);
			temp &= ~(1 << GP1_TIM_CCER_CC3NP);
			temp &= ~(1 << GP1_TIM_CCER_CC3P);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCPolarity << GP1_TIM_CCER_CC3P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR2;
			temp &= ~(3 << GP1_TIM_CCMR2_CC3S);
			temp |= (1 << GP1_TIM_CCMR2_OC3PE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC3FE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC3CE);
			temp &= ~(15 << GP1_TIM_CCMR2_OC3M);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCMode << GP1_TIM_CCMR2_OC3M);
			pTIMHandle->pGP1TIMx->CCMR2 = temp;

			pTIMHandle->pGP1TIMx->CCR3 = pTIMHandle->GP1_TIM_OC_Config.GP1TIM_Compare;

		}
		else
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC4E);
			temp &= ~(1 << GP1_TIM_CCER_CC4NP);
			temp &= ~(1 << GP1_TIM_CCER_CC4P);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCPolarity << GP1_TIM_CCER_CC4P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR2;
			temp &= ~(3 << GP1_TIM_CCMR2_CC4S);
			temp |= (1 << GP1_TIM_CCMR2_OC4PE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC4FE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC4CE);
			temp &= ~(15 << GP1_TIM_CCMR2_OC4M);
			temp |= (pTIMHandle->GP1_TIM_OC_Config.GP1TIM_OCMode << GP1_TIM_CCMR2_OC4M);
			pTIMHandle->pGP1TIMx->CCMR2 = temp;

			pTIMHandle->pGP1TIMx->CCR4 = pTIMHandle->GP1_TIM_OC_Config.GP1TIM_Compare;

		}

	}
}


void GP1TIM_OC_Start(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1IF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC1E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2IF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC2E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3IF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC3E);
	}
	else
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4IF);
		pTIMHandle->pGP1TIMx->CCER |= (1 << GP1_TIM_CCER_CC4E);
	}
}


void GP1TIM_OC_Stop(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC1IF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC1E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC2IF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC2E);
	}
	else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC3IF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC3E);
	}
	else
	{
		pTIMHandle->pGP1TIMx->SR &= ~(1 << GP1_TIM_SR_CC4IF);
		pTIMHandle->pGP1TIMx->CCER &= ~(1 << GP1_TIM_CCER_CC4E);
	}
}


void GP1TIM_OC_SetCompare(GP1_TIM_Handle_t *pTIMHandle, uint32_t Compare)
{
    if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
    {
    	pTIMHandle->pGP1TIMx->CCR1 = Compare;
    }
    else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
    {
    	pTIMHandle->pGP1TIMx->CCR2 = Compare;
    }
    else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
    {
    	pTIMHandle->pGP1TIMx->CCR3 = Compare;
    }
    else
    {
    	pTIMHandle->pGP1TIMx->CCR4 = Compare;
    }
}


void GP1TIM_PWM_Init(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->State == GP1TIM_STATE_RDY)
	{
		uint32_t temp;

		if(pTIMHandle->Channel == GP1_TIM_CHANNEL_1)
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC1E);
			temp &= ~(1 << GP1_TIM_CCER_CC1NP);
			temp &= ~(1 << GP1_TIM_CCER_CC1P);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Polarity << GP1_TIM_CCER_CC1P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR1;
			temp &= ~(3 << GP1_TIM_CCMR1_CC1S);
			temp |= (1 << GP1_TIM_CCMR1_OC1PE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC1FE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC1CE);
			temp &= ~(15 << GP1_TIM_CCMR1_OC1M);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_PWMMode << GP1_TIM_CCMR1_OC1M);
			pTIMHandle->pGP1TIMx->CCMR1 = temp;

			pTIMHandle->pGP1TIMx->CCR1 = pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Duty;

		}
		else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_2)
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC2E);
			temp &= ~(1 << GP1_TIM_CCER_CC2NP);
			temp &= ~(1 << GP1_TIM_CCER_CC2P);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Polarity << GP1_TIM_CCER_CC2P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR1;
			temp &= ~(3 << GP1_TIM_CCMR1_CC2S);
			temp |= (1 << GP1_TIM_CCMR1_OC2PE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC2FE);
			temp &= ~(1 << GP1_TIM_CCMR1_OC2CE);
			temp &= ~(15 << GP1_TIM_CCMR1_OC2M);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_PWMMode << GP1_TIM_CCMR1_OC2M);
			pTIMHandle->pGP1TIMx->CCMR1 = temp;

			pTIMHandle->pGP1TIMx->CCR2 = pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Duty;

		}
		else if(pTIMHandle->Channel == GP1_TIM_CHANNEL_3)
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC3E);
			temp &= ~(1 << GP1_TIM_CCER_CC3NP);
			temp &= ~(1 << GP1_TIM_CCER_CC3P);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Polarity << GP1_TIM_CCER_CC3P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR2;
			temp &= ~(3 << GP1_TIM_CCMR2_CC3S);
			temp |= (1 << GP1_TIM_CCMR2_OC3PE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC3FE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC3CE);
			temp &= ~(15 << GP1_TIM_CCMR2_OC3M);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_PWMMode << GP1_TIM_CCMR2_OC3M);
			pTIMHandle->pGP1TIMx->CCMR2 = temp;

			pTIMHandle->pGP1TIMx->CCR3 = pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Duty;

		}
		else
		{
			temp = pTIMHandle->pGP1TIMx->CCER;
			temp &= ~(1 << GP1_TIM_CCER_CC4E);
			temp &= ~(1 << GP1_TIM_CCER_CC4NP);
			temp &= ~(1 << GP1_TIM_CCER_CC4P);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Polarity << GP1_TIM_CCER_CC4P);
			pTIMHandle->pGP1TIMx->CCER = temp;

			temp = pTIMHandle->pGP1TIMx->CCMR2;
			temp &= ~(3 << GP1_TIM_CCMR2_CC4S);
			temp |= (1 << GP1_TIM_CCMR2_OC4PE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC4FE);
			temp &= ~(1 << GP1_TIM_CCMR2_OC4CE);
			temp &= ~(15 << GP1_TIM_CCMR2_OC4M);
			temp |= (pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_PWMMode << GP1_TIM_CCMR2_OC4M);
			pTIMHandle->pGP1TIMx->CCMR2 = temp;

			pTIMHandle->pGP1TIMx->CCR4 = pTIMHandle->GP1_TIM_PWM_Config.GP1TIM_Duty;

		}

	}
}


void GP1TIM_PWM_Start(GP1_TIM_Handle_t *pTIMHandle)
{
    GP1TIM_OC_Start(pTIMHandle);   // enable channel
}



void GP1TIM_PWM_Stop(GP1_TIM_Handle_t *pTIMHandle)
{
    GP1TIM_OC_Stop(pTIMHandle);
}


void GP1TIM_PWM_SetDuty(GP1_TIM_Handle_t *pTIMHandle, uint32_t Duty)
{
    GP1TIM_OC_SetCompare(pTIMHandle, Duty);
}


void GP1TIM_DeInit(GP1_TIM_Handle_t *pTIMHandle)
{
	if(pTIMHandle->pGP1TIMx == TIM2)
	{
		TIM2_REG_RST();
	}
	else if(pTIMHandle->pGP1TIMx == TIM3)
	{
		TIM3_REG_RST();
	}
	else if(pTIMHandle->pGP1TIMx == TIM4)
	{
		TIM4_REG_RST();
	}

	pTIMHandle->State = GP1TIM_STATE_RST;
}
