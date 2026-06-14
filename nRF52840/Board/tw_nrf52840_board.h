/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : tw_nrf52840_board.h
Purpose : custom board header file

*/

#ifndef TW_NRF52840_BOARD_H
#define TW_NRF52840_BOARD_H

#include "nrf52840_gpio.h"


/******************************************************************************
 * Board Information
 ******************************************************************************/

#define BOARD_NAME              "WIFI_BLE_ID_V_3.5"
#define BOARD_MCU               "nRF52840"



/******************************************************************************
 * Pin Mappings
 ******************************************************************************/


// LED Pins
#define LED_RED              P0_24
#define LED_BLUE             P1_15


// Button Pins
#define BTN_LEFT             P1_14
#define BTN_RIGHT            P0_11
                             
                         
// Buzzer Pins               
#define BUZZ_CPM1            P1_06
#define BUZZ_CPM2            P1_11
#define BUZZ_OUT_PWM         P1_13            
                             
                             
// Motor Pins                
#define MOTOR_OUT            P0_16
                             
                             
// Accelerometer             
#define ACC_INT              P1_00
#define ACC_SCLK             P0_22
#define ACC_SDA              P0_20
                             
                             
// External Flash/SPI           
#define XMEM_RST             P0_04
#define XMEM_CS              P1_09
#define XMEM_SCLK            P1_10
#define XMEM_MISO            P0_29
#define XMEM_MOSI            P1_04
                             
                             
// Display/SPI                   
#define DISP_EN              P0_13
#define DISP_RST             P1_01
#define DISP_CS              P1_02
#define DISP_SCLK            P0_17
#define DISP_MOSI            P1_07
#define DISP_BUSY            P0_08
#define DISP_DC              P0_12 
                             
                             
// ESP/UART1                 
#define ESP_EN               P0_26
#define ESP_RXD1             P0_31
#define ESP_TXD1             P0_15
                             
                             
// Others                    
#define ADC                  P0_28
#define SENSOR               P0_02
#define CHARGE_IND           P0_05



#endif /* TW_NRF52840_BOARD_H */

/******************************* END OF FILE *********************************/