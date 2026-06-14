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
#include "tw_nrf52840_board.h"

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
    LedCfg.GPIO_PinNo = LED_RED;

    GPIO_Init(&LedCfg);

    while(1)
    {
        GPIO_ClearPin(LED_RED);
        delay();

        GPIO_SetPin(LED_RED);
        delay();
    }
}


/******************************* END OF FILE *********************************/