/*
 * stm32f303xx_rcc_driver.c
 *
 *  Created on: Dec 27, 2025
 *      Author: aswin
 */

#include "stm32f303xx.h"

void SysClk_Config(void)
{
    /* 1. Enable HSI (bit 0) */
    RCC->CR |= (1 << 0);              // HSION

    /* 2. Wait until HSI is ready (bit 1) */
    while(!(RCC->CR & (1 << 1)));     // HSIRDY

    /* 3. Select HSI as system clock
       SW[1:0] = 00 (bits 1:0) */
    RCC->CFGR &= ~(0x3 << 0);         // Clear SW bits

    /* 4. Wait until HSI is used as system clock
       SWS[1:0] = 00 (bits 3:2) */
    while(((RCC->CFGR >> 2) & 0x3) != 0x0);

    /* 5. AHB prescaler = 1
       HPRE[3:0] = 0000 (bits 7:4) */
    RCC->CFGR &= ~(0xF << 4);

    /* 6. APB1 prescaler = 1
       PPRE1[2:0] = 000 (bits 12:10) */
    RCC->CFGR &= ~(0x7 << 10);

    /* 7. APB2 prescaler = 1
       PPRE2[2:0] = 000 (bits 15:13) */
    RCC->CFGR &= ~(0x7 << 13);
}
