/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : 001_gpi_test.c
Purpose : GPIO test main file

*/

#include <stdio.h>
#include <stdlib.h>
#include "nrf52840_gpio.h"

/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/

static void delay(void)
{
    volatile uint32_t i;

    for(i = 0; i < 500000; i++);
}

int main(void)
{
    GPIO_PinConfig_t LedCfg = GPIO_CFG_OUTPUT;
    LedCfg.GPIO_PinNo = P0_24;

    GPIO_Init(&LedCfg);

    while(1)
    {
        GPIO_ClearPin(P0_24);
        delay();

        GPIO_SetPin(P0_24);
        delay();
    }
}