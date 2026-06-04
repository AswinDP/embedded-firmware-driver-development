/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : nrf52840_gpio.h
Purpose : GPIO header file

*/

#include "nrf52840.h"



/******************************************************************************
 * Some Common Macros
 ******************************************************************************/

/* ---------------------------- GPIO Pin No ---------------------------- */

#define P0_00  				            0
#define P0_01  				            1
#define P0_02  				            2
#define P0_03  				            3
#define P0_04  				            4
#define P0_05  				            5
#define P0_06  				            6
#define P0_07  				            7
#define P0_08  				            8
#define P0_09  				            9
#define P0_10                           10
#define P0_11 				            11
#define P0_12                           12
#define P0_13 				            13
#define P0_14 				            14
#define P0_15 				            15
#define P0_16  			                16
#define P0_17  			                17
#define P0_18  			                18
#define P0_19  			                19
#define P0_20  			                20
#define P0_21  			                21
#define P0_22  			                22
#define P0_23  			                23
#define P0_24  			                24
#define P0_25 			                25
#define P0_26  			                26
#define P0_27 			                27
#define P0_28  			                28
#define P0_29 				            29
#define P0_30 				            30
#define P0_31 				            31
                                        
                                        
#define P1_00  				            32
#define P1_01  				            33
#define P1_02  				            34
#define P1_03  				            35
#define P1_04  				            36
#define P1_05  				            37
#define P1_06  				            38
#define P1_07  				            39
#define P1_08  				            40
#define P1_09  				            41
#define P1_10                           42
#define P1_11 				            43
#define P1_12                           44
#define P1_13 				            45
#define P1_14 				            46
#define P1_15 				            47
#define P1_16  			                48
#define P1_17  			                49
#define P1_18  			                50
#define P1_19  			                51
#define P1_20  			                52
#define P1_21  			                53
#define P1_22  			                54
#define P1_23  			                55
#define P1_24  			                56
#define P1_25 			                57
#define P1_26  			                58
#define P1_27 			                59
#define P1_28  			                60
#define P1_29 				            61
#define P1_30 				            62
#define P1_31 				            63

/* ---------------------------- GPIO Pin Type ---------------------------- */

#define GPIO_PIN_INPUT                   0
#define GPIO_PIN_OUTPUT                  1

/* ---------------------------- GPIO Pin Drive ---------------------------- */

#define GPIO_PIN_DRIVE_S0S1              0
#define GPIO_PIN_DRIVE_H0S1              1
#define GPIO_PIN_DRIVE_S0H1              2
#define GPIO_PIN_DRIVE_H0H1              3
#define GPIO_PIN_DRIVE_D0S1              4
#define GPIO_PIN_DRIVE_D0H1              5
#define GPIO_PIN_DRIVE_S0D1              6
#define GPIO_PIN_DRIVE_H0D1              7

/* Standard GPIO */
#define GPIO_DRIVE_STANDARD         GPIO_PIN_DRIVE_S0S1

/* High Drive GPIO */
#define GPIO_DRIVE_HIGH             GPIO_PIN_DRIVE_H0H1

/* Open Drain */
#define GPIO_DRIVE_OPEN_DRAIN_STD   GPIO_PIN_DRIVE_S0D1
#define GPIO_DRIVE_OPEN_DRAIN_HIGH  GPIO_PIN_DRIVE_H0D1

/* Open Source */
#define GPIO_DRIVE_OPEN_SRC_STD     GPIO_PIN_DRIVE_D0S1
#define GPIO_DRIVE_OPEN_SRC_HIGH    GPIO_PIN_DRIVE_D0H1

/* Asymmetric Drive */
#define GPIO_DRIVE_PULLUP_STRONG    GPIO_PIN_DRIVE_S0H1
#define GPIO_DRIVE_PULLDOWN_STRONG  GPIO_PIN_DRIVE_H0S1
                                         
/* ---------------------------- GPIO Pin PUPD ---------------------------- */

#define GPIO_PIN_NO_PUPD                 0
#define GPIO_PIN_PULLDOWN                1
#define GPIO_PIN_PULLUP                  3

/* ---------------------------- GPIO Pin In Buff ---------------------------- */

#define GPIO_PIN_INPUT_CONNECT           0
#define GPIO_PIN_INPUT_DISCONNECT        1

/* ---------------------------- GPIO Pin Sense ---------------------------- */

#define GPIO_PIN_SENSE_DISABLE           0
#define GPIO_PIN_SENSE_HIGH              2
#define GPIO_PIN_SENSE_LOW               3

/* ---------------------------- Internal Helpers ---------------------------- */

#define GPIO_GET_PORT(pin)    (((pin) < 32U) ? GPIOP0 : GPIOP1)
#define GPIO_GET_PIN(pin)     ((pin) & 0x1FU)

/* ---------------------------- Bit Position Macros ---------------------------- */

#define GPIO_PIN_CNF_DIR_POS      0U
#define GPIO_PIN_CNF_INPUT_POS    1U
#define GPIO_PIN_CNF_PULL_POS     2U
#define GPIO_PIN_CNF_DRIVE_POS    8U
#define GPIO_PIN_CNF_SENSE_POS    16U



/******************************************************************************
 * Structures
 ******************************************************************************/

/* ---------------------------- Config Structure ---------------------------- */

typedef struct{

    uint8_t GPIO_PinNo;
    uint8_t GPIO_PinType;
    uint8_t GPIO_PinDrive;
    uint8_t GPIO_PinPuPd;
    uint8_t GPIO_PinInBuff;
    uint8_t GPIO_PinSense;

}GPIO_PinConfig_t;



/******************************************************************************
 * Basic Configuration Macros
 ******************************************************************************/


 #define GPIO_CFG_OUTPUT            \
{                                  \
    .GPIO_PinType      = GPIO_PIN_OUTPUT, \
    .GPIO_PinDrive     = GPIO_DRIVE_STANDARD, \
    .GPIO_PinPuPd      = GPIO_PIN_NO_PUPD, \
    .GPIO_PinInBuff = GPIO_PIN_INPUT_DISCONNECT, \
    .GPIO_PinSense     = GPIO_PIN_SENSE_DISABLE \
}

#define GPIO_CFG_INPUT             \
{                                  \
    .GPIO_PinType      = GPIO_PIN_INPUT, \
    .GPIO_PinDrive     = GPIO_DRIVE_STANDARD, \
    .GPIO_PinPuPd      = GPIO_PIN_NO_PUPD, \
    .GPIO_PinInBuff = GPIO_PIN_INPUT_CONNECT, \
    .GPIO_PinSense     = GPIO_PIN_SENSE_DISABLE \
}

#define GPIO_CFG_INPUT_PULLUP      \
{                                  \
    .GPIO_PinType      = GPIO_PIN_INPUT, \
    .GPIO_PinDrive     = GPIO_DRIVE_STANDARD, \
    .GPIO_PinPuPd      = GPIO_PIN_PULLUP, \
    .GPIO_PinInBuff = GPIO_PIN_INPUT_CONNECT, \
    .GPIO_PinSense     = GPIO_PIN_SENSE_DISABLE \
}

#define GPIO_CFG_INPUT_PULLDOWN    \
{                                  \
    .GPIO_PinType      = GPIO_PIN_INPUT, \
    .GPIO_PinDrive     = GPIO_DRIVE_STANDARD, \
    .GPIO_PinPuPd      = GPIO_PIN_PULLDOWN, \
    .GPIO_PinInBuff = GPIO_PIN_INPUT_CONNECT, \
    .GPIO_PinSense     = GPIO_PIN_SENSE_DISABLE \
}

#define GPIO_CFG_OPEN_DRAIN        \
{                                  \
    .GPIO_PinType      = GPIO_PIN_OUTPUT, \
    .GPIO_PinDrive     = GPIO_DRIVE_OPEN_DRAIN_STD, \
    .GPIO_PinPuPd      = GPIO_PIN_NO_PUPD, \
    .GPIO_PinInBuff = GPIO_PIN_DISCONNECT, \
    .GPIO_PinSense     = GPIO_PIN_SENSE_DISABLE \
}

#define GPIO_CFG_WAKEUP_LOW        \
{                                  \
    .GPIO_PinType      = GPIO_PIN_INPUT, \
    .GPIO_PinDrive     = GPIO_DRIVE_STANDARD, \
    .GPIO_PinPuPd      = GPIO_PIN_PULLUP, \
    .GPIO_PinInBuff = GPIO_PIN_INPUT_CONNECT, \
    .GPIO_PinSense     = GPIO_PIN_SENSE_LOW \
}

#define GPIO_CFG_WAKEUP_HIGH       \
{                                  \
    .GPIO_PinType      = GPIO_PIN_INPUT, \
    .GPIO_PinDrive     = GPIO_DRIVE_STANDARD, \
    .GPIO_PinPuPd      = GPIO_PIN_PULLDOWN, \
    .GPIO_PinInBuff = GPIO_PIN_INPUT_CONNECT, \
    .GPIO_PinSense     = GPIO_PIN_SENSE_HIGH \
}

#define GPIO_CFG(mode,pull,drive,input,sense) \
{                                             \
    .GPIO_PinType      = (mode),              \
    .GPIO_PinPuPd      = (pull),              \
    .GPIO_PinDrive     = (drive),             \
    .GPIO_PinInBuff = (input),             \
    .GPIO_PinSense     = (sense)              \
}



/******************************************************************************
 * Function Declaration
 ******************************************************************************/

void GPIO_Init(GPIO_PinConfig_t *pGPIOConfig);
void GPIO_DeInit(uint8_t PinNo);

void GPIO_SetPin(uint8_t PinNo);
void GPIO_ClearPin(uint8_t PinNo);

void GPIO_WritePin(uint8_t PinNo,
                   uint8_t Value);

uint8_t GPIO_ReadPin(uint8_t PinNo);

void GPIO_TogglePin(uint8_t PinNo);




/******************************* END OF FILE *********************************/










