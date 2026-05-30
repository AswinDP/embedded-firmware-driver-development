/*
 * stm32f303xx_nvic_driver.c
 *
 *  Created on: Dec 27, 2025
 *      Author: aswin
 */

#include "stm32f303xx.h"


/* Enable an interrupt or exception */
void NVIC_EnableIRQ(IRQn_Type IRQn)
{
	if (IRQn < 0)
	    return;

	NVIC->ISER[IRQn / 32] |= (1 << (IRQn % 32));
}


/* Disable an interrupt or exception */
void NVIC_DisableIRQ(IRQn_Type IRQn)
{
	if (IRQn < 0)
	    return;

	NVIC->ICER[IRQn / 32] |= (1 << (IRQn % 32));
}


/* Set pending status of an interrupt or exception */
void NVIC_SetPendingIRQ(IRQn_Type IRQn)
{
	if (IRQn < 0)
	    return;

	NVIC->ISPR[IRQn / 32] |= (1 << (IRQn % 32));
}


/* Clear pending status of an interrupt or exception */
void NVIC_ClearPendingIRQ(IRQn_Type IRQn)
{
	if (IRQn < 0)
	    return;

	NVIC->ICPR[IRQn / 32] |= (1 << (IRQn % 32));
}


/* Get pending status of an interrupt or exception
 * Returns non-zero if pending, 0 otherwise
 */
uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn)
{
	if (IRQn < 0)
		return 0;

	return ((NVIC->ISPR[IRQn / 32]) & (1 << (IRQn % 32)));
}


/* Set priority of an interrupt or exception */
void NVIC_SetPriority(IRQn_Type IRQn, uint8_t priority)
{
    if (IRQn < 0)
        return;

    uint8_t ipr_index  = IRQn / 4;
    uint8_t byte_shift = (IRQn % 4) * 8;
    uint8_t shift      = byte_shift + (8 - NO_PR_BITS_IMPLEMENTED);

    /* Clear existing priority */
    NVIC->IPR[ipr_index] &= ~(0xF << shift);

    /* Set new priority */
    NVIC->IPR[ipr_index] |= ((priority & 0xF) << shift);
}



/* Get priority of an interrupt or exception */
uint8_t NVIC_GetPriority(IRQn_Type IRQn)
{
    if (IRQn < 0)
        return 0;

    uint8_t ipr_index  = IRQn / 4;
    uint8_t byte_shift = (IRQn % 4) * 8;

    uint8_t raw_priority =
        (NVIC->IPR[ipr_index] >> byte_shift) & 0xFF;

    return (raw_priority >> (8 - NO_PR_BITS_IMPLEMENTED));
}


















