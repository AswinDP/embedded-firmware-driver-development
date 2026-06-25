/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : 001_spim_test.c
Purpose : SPIM test main file

*/

#include <stdio.h>
#include <stdlib.h>
#include "nrf52840.h"
#include "tw_nrf52840_board.h"
#include "nrf52840_spim.h"

/*********************************************************************
*
*       main()
*
*  Function description
*   Application entry point.
*/


#define CS_PIN          
#define SCK_PIN         
#define MOSI_PIN        
#define MISO_PIN        

int main(void)
{
    SPIM_Instance_t spim = SPIM_INSTANCE(0);
    SPIM_Config_t cfg = SPIM_FLASH_CONFIG(SCK_PIN, MOSI_PIN, MISO_PIN);
    uint8_t tx[4] = {0x9F, 0, 0, 0};   /* JEDEC ID command */
    uint8_t rx[4] = {0};

    NRF_P0->DIRSET = (1UL << CS_PIN);
    NRF_P0->OUTSET = (1UL << CS_PIN);   /* CS idle high */

    SPIM_Init(&spim, &cfg);

    NRF_P0->OUTCLR = (1UL << CS_PIN);   /* CS low */
    SPIM_Transfer(&spim, tx, rx, 4);
    NRF_P0->OUTSET = (1UL << CS_PIN);   /* CS high */

    /* rx[1]=Manufacturer(0xEF) rx[2]=MemType(0x40) rx[3]=Capacity(0x17) */

    while (1) { __NOP(); }
}


/******************************* END OF FILE *********************************/