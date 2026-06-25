/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : nrf52840.h
Purpose : MCU header file

*/

#define __vo volatile
#include <stdint.h>

/******************************************************************************
 * Some Common Macros
 ******************************************************************************/

#define ENABLE              1
#define DISABLE             0
#define SET                 ENABLE
#define RESET               DISABLE

/******************************************************************************
 * Peripheral Base Addresses
 ******************************************************************************/


// 0x1000xxxx - Configuration Registers (FICR / UICR)

#define NRF_FICR_BASE               0x10000000U  /* Factory Information Configuration Registers */
#define NRF_UICR_BASE               0x10001000U  /* User Information Configuration Registers    */


// 0x4000xxxx - Core Peripherals

#define NRF_APPROTECT_BASE          0x40000000U  /* Access Port Protection Control             */
#define NRF_CLOCK_BASE              0x40000000U  /* Clock Control                              */
#define NRF_POWER_BASE              0x40000000U  /* Power Control                              */

#define NRF_RADIO_BASE              0x40001000U  /* 2.4 GHz Radio                              */
#define NRF_UARTE0_BASE             0x40002000U  /* UART with EasyDMA, Unit 0                  */

// Shared Memory Block 0x40003000
#define NRF_SPIM0_BASE              0x40003000U  /* SPI Master 0 with EasyDMA                  */
#define NRF_SPIS0_BASE              0x40003000U  /* SPI Slave 0                                */
#define NRF_TWIM0_BASE              0x40003000U  /* Two-Wire Interface Master 0 (I2C)          */
#define NRF_TWIS0_BASE              0x40003000U  /* Two-Wire Interface Slave 0                 */

// Shared Memory Block 0x40004000
#define NRF_SPIM1_BASE              0x40004000U  /* SPI Master 1 with EasyDMA                  */
#define NRF_SPIS1_BASE              0x40004000U  /* SPI Slave 1                                */
#define NRF_TWIM1_BASE              0x40004000U  /* Two-Wire Interface Master 1 (I2C)          */
#define NRF_TWIS1_BASE              0x40004000U  /* Two-Wire Interface Slave 1                 */

#define NRF_NFCT_BASE               0x40005000U  /* Near Field Communication Tag               */
#define NRF_GPIOTE_BASE             0x40006000U  /* GPIO Tasks and Events Block                */
#define NRF_SAADC_BASE              0x40007000U  /* Successive Approximation ADC (12-bit)       */

// Hardware Timers & Counters
#define NRF_TIMER0_BASE             0x40008000U  /* Hardware Timer 0                           */
#define NRF_TIMER1_BASE             0x40009000U  /* Hardware Timer 1                           */
#define NRF_TIMER2_BASE             0x4000A000U  /* Hardware Timer 2                           */
#define NRF_RTC0_BASE               0x4000B000U  /* Real-Time Counter 0 (LFCLK domain)         */

#define NRF_TEMP_BASE               0x4000C000U  /* Internal Die Temperature Sensor            */
#define NRF_RNG_BASE                0x4000D000U  /* Hardware Random Number Generator           */
#define NRF_ECB_BASE                0x4000E000U  /* AES Electronic Code Book Mode Encryption   */
#define NRF_AAR_BASE                0x4000F000U  /* Accelerated Address Resolver Block         */
#define NRF_CCM_BASE                0x4000F000U  /* AES Counter with CBC-MAC Encryption        */
#define NRF_WDT_BASE                0x40010000U  /* Watchdog Timer                             */
#define NRF_RTC1_BASE               0x40011000U  /* Real-Time Counter 1                        */
#define NRF_QDEC_BASE               0x40012000U  /* Quadrature Decoder                         */

// Analog Comparators
#define NRF_COMP_BASE               0x40013000U  /* General Purpose Comparator                 */
#define NRF_LPCOMP_BASE             0x40013000U  /* Low Power Comparator                       */

// Event Generator Units & Software Interrupts
#define NRF_EGU0_BASE               0x40014000U  /* Event Generator Unit 0                     */
#define NRF_SWI0_BASE               0x40014000U  /* Software Interrupt 0                       */
#define NRF_EGU1_BASE               0x40015000U  /* Event Generator Unit 1                     */
#define NRF_SWI1_BASE               0x40015000U  /* Software Interrupt 1                       */
#define NRF_EGU2_BASE               0x40016000U  /* Event Generator Unit 2                     */
#define NRF_SWI2_BASE               0x40016000U  /* Software Interrupt 2                       */
#define NRF_EGU3_BASE               0x40017000U  /* Event Generator Unit 3                     */
#define NRF_SWI3_BASE               0x40017000U  /* Software Interrupt 3                       */
#define NRF_EGU4_BASE               0x40018000U  /* Event Generator Unit 4                     */
#define NRF_SWI4_BASE               0x40018000U  /* Software Interrupt 4                       */
#define NRF_EGU5_BASE               0x40019000U  /* Event Generator Unit 5                     */
#define NRF_SWI5_BASE               0x40019000U  /* Software Interrupt 5                       */


// 0x4001Axxx to 0x4002Dxxx - High-Speed Peripherals & Audio

#define NRF_TIMER3_BASE             0x4001A000U  /* Hardware Timer 3                           */
#define NRF_TIMER4_BASE             0x4001B000U  /* Hardware Timer 4                           */
#define NRF_PWM0_BASE               0x4001C000U  /* Pulse Width Modulation Unit 0              */
#define NRF_PDM_BASE                0x4001D000U  /* Pulse Density Modulation Audio Interface   */
#define NRF_ACL_BASE                0x4001E000U  /* Access Control Lists                       */
#define NRF_NVMC_BASE               0x4001E000U  /* Non-Volatile Memory Controller             */
#define NRF_PPI_BASE                0x4001F000U  /* Programmable Peripheral Interconnect       */
#define NRF_MWU_BASE                0x40020000U  /* Memory Watch Unit                          */
#define NRF_PWM1_BASE               0x40021000U  /* Pulse Width Modulation Unit 1              */
#define NRF_PWM2_BASE               0x40022000U  /* Pulse Width Modulation Unit 2              */

// Shared Memory Block 0x40023000
#define NRF_SPIM2_BASE              0x40023000U  /* SPI Master 2 with EasyDMA                  */
#define NRF_SPIS2_BASE              0x40023000U  /* SPI Slave 2                                */

#define NRF_RTC2_BASE               0x40024000U  /* Real-Time Counter 2                        */
#define NRF_I2S_BASE                0x40025000U  /* Inter-IC Sound Audio Interface             */
#define NRF_FPU_BASE                0x40026000U  /* Floating Point Unit Interrupt Control      */
#define NRF_USBD_BASE               0x40027000U  /* Universal Serial Bus Device Controller      */
#define NRF_UARTE1_BASE             0x40028000U  /* UART with EasyDMA, Unit 1                  */
#define NRF_QSPI_BASE               0x40029000U  /* Quad SPI External Flash Interface          */
#define NRF_PWM3_BASE               0x4002D000U  /* Pulse Width Modulation Unit 3              */
#define NRF_SPIM3_BASE              0x4002F000U  /* High-Speed SPI Master 3 (Up to 32 MHz)     */


// 0x500xxxxx - High-Speed Ports & Security Subsystems

#define NRF_P0_BASE                 0x50000000U  /* GPIO Port 0 Configuration Blocks           */
#define NRF_P1_BASE                 0x50000300U  /* GPIO Port 1 Configuration Blocks           */

// ARM CryptoCell 310 Subsystems
#define NRF_CRYPTOCELL_BASE         0x5002A000U  /* Cryptocell Hardware Security Subsystem     */
#define NRF_CC_AES_BASE             0x5002B000U  /* CryptoCell AES Core Submodule              */
#define NRF_CC_CHACHA_BASE          0x5002B000U  /* CryptoCell CHACHA Stream Cipher            */
#define NRF_CC_CTL_BASE             0x5002B000U  /* CryptoCell Control Interface               */
#define NRF_CC_DIN_BASE             0x5002B000U  /* CryptoCell DMA Source Interface            */
#define NRF_CC_DOUT_BASE            0x5002B000U  /* CryptoCell DMA Destination Interface       */
#define NRF_CC_HASH_BASE            0x5002B000U  /* CryptoCell HASH/SHA Engine                 */
#define NRF_CC_HOST_RGF_BASE        0x5002B000U  /* CryptoCell Host Register Interface         */
#define NRF_CC_MISC_BASE            0x5002B000U  /* CryptoCell Miscellaneous Control           */
#define NRF_CC_PKA_BASE             0x5002B000U  /* CryptoCell Public Key Accelerator (PKA)    */
#define NRF_CC_RNG_BASE             0x5002B000U  /* CryptoCell Hardware True Random Number Gen */
#define NRF_CC_RNG_SRAM_BASE        0x5002B000U  /* CryptoCell RNG Private Internal SRAM       */



/******************************************************************************
 * GPIO
 ******************************************************************************/

/* ------------------------- GPIO Register Definition ----------------------- */

typedef struct {
    uint32_t RESERVED_0[321];      // Padding from base 0x000 to 0x504 (1284 bytes)
    
    __vo uint32_t OUT;             // Offset 0x504
    __vo uint32_t OUTSET;          // Offset 0x508
    __vo uint32_t OUTCLR;          // Offset 0x50C
    __vo uint32_t IN;              // Offset 0x510
    __vo uint32_t DIR;             // Offset 0x514
    __vo uint32_t DIRSET;          // Offset 0x518
    __vo uint32_t DIRCLR;          // Offset 0x51C
    __vo uint32_t LATCH;           // Offset 0x520
    __vo uint32_t DETECTMODE;      // Offset 0x524
    
    uint32_t RESERVED_1[118];      // Padding from 0x528 to 0x700 (472 bytes)
    
    __vo uint32_t PIN_CNF[32];     // Offset 0x700 to 0x77C

} GPIO_Reg_def_t;


/* ------------------------- GPIO Peripheral Definition ----------------------- */

#define GPIOP0                        ((GPIO_Reg_def_t*)NRF_P0_BASE)
#define GPIOP1                        ((GPIO_Reg_def_t*)NRF_P1_BASE)



/******************************************************************************
 * SPIM
 ******************************************************************************/

/* ------------------------- SPIM Register Definition ----------------------- */

typedef struct
{
    __vo uint32_t RESERVED0[4];      // 0x000 - 0x00C

    __vo uint32_t TASKS_START;       // 0x010
    __vo uint32_t TASKS_STOP;        // 0x014

    __vo uint32_t RESERVED1;         // 0x018

    __vo uint32_t TASKS_SUSPEND;     // 0x01C
    __vo uint32_t TASKS_RESUME;      // 0x020

    __vo uint32_t RESERVED2[56];     // 0x024 - 0x100

    __vo uint32_t EVENTS_STOPPED;    // 0x104

    __vo uint32_t RESERVED3[2];      // 0x108 - 0x10C

    __vo uint32_t EVENTS_ENDRX;      // 0x110

    __vo uint32_t RESERVED4;         // 0x114

    __vo uint32_t EVENTS_END;        // 0x118

    __vo uint32_t RESERVED5;         // 0x11C

    __vo uint32_t EVENTS_ENDTX;      // 0x120

    __vo uint32_t RESERVED6[10];     // 0x124 - 0x148

    __vo uint32_t EVENTS_STARTED;    // 0x14C

    __vo uint32_t RESERVED7[44];     // 0x150 - 0x1FC

    __vo uint32_t SHORTS;            // 0x200

    __vo uint32_t RESERVED8[64];     // 0x204 - 0x300

    __vo uint32_t INTENSET;          // 0x304
    __vo uint32_t INTENCLR;          // 0x308

    __vo uint32_t RESERVED9[61];     // 0x30C - 0x3FC

    __vo uint32_t STALLSTAT;         // 0x400

    __vo uint32_t RESERVED10[63];    // 0x404 - 0x4FC

    __vo uint32_t ENABLE_SPIM;       // 0x500

    __vo uint32_t RESERVED_15;       // 0x504  

    __vo uint32_t PSEL_SCK;          // 0x508
    __vo uint32_t PSEL_MOSI;         // 0x50C
    __vo uint32_t PSEL_MISO;         // 0x510
    __vo uint32_t PSEL_CSN;          // 0x514

    __vo uint32_t RESERVED11[3];     // 0x518 - 0x520

    __vo uint32_t FREQUENCY;         // 0x524

    __vo uint32_t RESERVED12[3];     // 0x528 - 0x530

    __vo uint32_t RXD_PTR;           // 0x534
    __vo uint32_t RXD_MAXCNT;        // 0x538
    __vo uint32_t RXD_AMOUNT;        // 0x53C
    __vo uint32_t RXD_LIST;          // 0x540

    __vo uint32_t TXD_PTR;           // 0x544
    __vo uint32_t TXD_MAXCNT;        // 0x548
    __vo uint32_t TXD_AMOUNT;        // 0x54C
    __vo uint32_t TXD_LIST;          // 0x550

    __vo uint32_t CONFIG;            // 0x554

    __vo uint32_t RESERVED13[2];     // 0x558 - 0x55C

    __vo uint32_t IFTIMING_RXDELAY;  // 0x560
    __vo uint32_t IFTIMING_CSNDUR;   // 0x564
    __vo uint32_t CSNPOL;            // 0x568
    __vo uint32_t PSELDCX;           // 0x56C
    __vo uint32_t DCXCNT;            // 0x570

    __vo uint32_t RESERVED14[19];    // 0x574 - 0x5BC

    __vo uint32_t ORC;               // 0x5C0

} NRF_SPIM_RegDef_t;


/* ------------------------- SPIM Peripheral Definition ----------------------- */

#define SPIM0                        ((SPIM_Reg_def_t*)NRF_SPIM0_BASE)
#define SPIM1                        ((SPIM_Reg_def_t*)NRF_SPIM1_BASE)
#define SPIM2                        ((SPIM_Reg_def_t*)NRF_SPIM2_BASE)
#define SPIM3                        ((SPIM_Reg_def_t*)NRF_SPIM3_BASE)


/******************************* END OF FILE *********************************/