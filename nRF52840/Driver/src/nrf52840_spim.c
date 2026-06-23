/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : nrf52840_spim.c
Purpose : SPIM source file

*/

#include "nrf52840_spim.h"
//#include "customconfig.h"     yet to be created

#if (SPIM_DEBUG_LOG_ENABLED == 1)
    #include "SEGGER_RTT.h"
#endif


/******************************************************************************
 * Debug Log Macros
 *
 * These compile to nothing unless SPIM_DEBUG_LOG_ENABLED is set to 1 in
 * customconfig.h. This keeps the driver footprint (flash/RAM/CPU cycles
 * spent formatting + pushing to RTT) at zero by default, since RTT
 * logging is not free, especially inside time critical transfer paths.
 *
 * SPIM_DEBUG_LOG_VERBOSE gates the extra-chatty logs (e.g. per call
 * buffer dumps) separately, since those are useful for deep debugging
 * but too noisy/expensive to leave on all the time.
 ******************************************************************************/

#if (SPIM_DEBUG_LOG_ENABLED == 1)

    #define SPIM_LOG(fmt, ...)              SEGGER_RTT_printf(0, "[SPIM] " fmt "\r\n", ##__VA_ARGS__)
    #define SPIM_LOG_ERR(fmt, ...)          SEGGER_RTT_printf(0, "[SPIM][ERR] " fmt "\r\n", ##__VA_ARGS__)

    #if (SPIM_DEBUG_LOG_VERBOSE == 1)
        #define SPIM_LOG_V(fmt, ...)        SEGGER_RTT_printf(0, "[SPIM][V] " fmt "\r\n", ##__VA_ARGS__)
    #else
        #define SPIM_LOG_V(fmt, ...)
    #endif

#else

    #define SPIM_LOG(fmt, ...)
    #define SPIM_LOG_ERR(fmt, ...)
    #define SPIM_LOG_V(fmt, ...)

#endif


/******************************************************************************
 * Private Defines
 ******************************************************************************/

/* Generic, conservative spin-wait bound for EVENTS_END polling.
 * Not an accurate timeout in time units, just a runaway guard so a
 * dead/unclocked peripheral can never hang the CPU forever.            */
#define SPIM_END_EVENT_WAIT_LIMIT       0xFFFFFUL

/* GPIO pin config bitfields used when configuring SCK/MOSI/MISO PSEL.
 * Bit 31 selects connect(0)/disconnect(1) for the PSEL register.       */
#define SPIM_PSEL_DISCONNECTED          (1UL << 31)


/******************************************************************************
 * Private Helper Functions
 ******************************************************************************/

/**
 * @brief  Configures a single PSEL register (SCK/MOSI/MISO) for an
 *         instance, handling the "not connected" sentinel.
 */
static void SPIM_ConfigurePin(volatile uint32_t *p_psel_reg, uint32_t pin)
{
    if (pin == SPIM_PIN_NOT_CONNECTED)
    {
        *p_psel_reg = SPIM_PSEL_DISCONNECTED;
    }
    else
    {
        *p_psel_reg = pin;
    }
}

/**
 * @brief  Polls EVENTS_END with a runaway guard and clears it on exit.
 * @return SPIM_SUCCESS or SPIM_ERROR_TIMEOUT
 */
static SPIM_Status_t SPIM_WaitForEnd(SPIM_Instance_t *p_instance)
{
    uint32_t guard = 0;

    while (p_instance->Instance->EVENTS_END == 0)
    {
        guard++;
        if (guard >= SPIM_END_EVENT_WAIT_LIMIT)
        {
            SPIM_LOG_ERR("Inst%u: EVENTS_END timeout waiting for transfer to finish", p_instance->drv_inst_idx);
            return SPIM_ERROR_TIMEOUT;
        }
    }

    p_instance->Instance->EVENTS_END = 0;

    SPIM_LOG_V("Inst%u: EVENTS_END observed after %lu poll cycles", p_instance->drv_inst_idx, (unsigned long)guard);

    return SPIM_SUCCESS;
}


/******************************************************************************
 * Public Function Definitions
 ******************************************************************************/

/**
 * @brief  Initializes a SPIM instance: pins, frequency, mode, bit order.
 */
SPIM_Status_t SPIM_Init(SPIM_Instance_t *p_instance, SPIM_Config_t *p_config)
{
    if ((p_instance == NULL) || (p_config == NULL))
    {
        SPIM_LOG_ERR("Init: NULL pointer passed (inst=%p, cfg=%p)", (void *)p_instance, (void *)p_config);
        return SPIM_ERROR_NULL_PTR;
    }

    if (p_instance->Instance == NULL)
    {
        SPIM_LOG_ERR("Init: instance %u has no peripheral bound", p_instance->drv_inst_idx);
        return SPIM_ERROR_INVALID_PARAM;
    }

    if (p_instance->State != SPIM_READY)
    {
        SPIM_LOG_ERR("Init: instance %u not in READY state (state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);
        return SPIM_ERROR_BUSY;
    }

    SPIM_LOG("Init: starting instance %u (SCK=%lu MOSI=%lu MISO=%lu Freq=0x%08lX Mode=%d Order=%d)",
             p_instance->drv_inst_idx,
             (unsigned long)p_config->SCK_Pin,
             (unsigned long)p_config->MOSI_Pin,
             (unsigned long)p_config->MISO_Pin,
             (unsigned long)p_config->Frequency,
             (int)p_config->Mode,
             (int)p_config->BitOrder);

    /* Disable peripheral while reconfiguring */
    p_instance->Instance->ENABLE = 0;

    /* Pin configuration */
    SPIM_ConfigurePin(&p_instance->Instance->PSEL.SCK, p_config->SCK_Pin);
    SPIM_ConfigurePin(&p_instance->Instance->PSEL.MOSI, p_config->MOSI_Pin);
    SPIM_ConfigurePin(&p_instance->Instance->PSEL.MISO, p_config->MISO_Pin);

    SPIM_LOG_V("Inst%u: PSEL registers written", p_instance->drv_inst_idx);

    /* Frequency */
    p_instance->Instance->FREQUENCY = (uint32_t)p_config->Frequency;

    /* Mode -> CONFIG.CPHA / CONFIG.CPOL
     * MODE0: CPOL=0 CPHA=0   MODE1: CPOL=0 CPHA=1
     * MODE2: CPOL=1 CPHA=0   MODE3: CPOL=1 CPHA=1                     */
    uint32_t config_reg = 0;

    switch (p_config->Mode)
    {
        case SPIM_MODE0: config_reg = 0x00; break;
        case SPIM_MODE1: config_reg = 0x01; break;
        case SPIM_MODE2: config_reg = 0x02; break;
        case SPIM_MODE3: config_reg = 0x03; break;
        default:
            SPIM_LOG_ERR("Inst%u: invalid Mode %d", p_instance->drv_inst_idx, (int)p_config->Mode);
            return SPIM_ERROR_INVALID_PARAM;
    }

    /* Bit order -> CONFIG.ORDER (bit 2): 0 = MSB first, 1 = LSB first */
    if (p_config->BitOrder == SPIM_LSB_FIRST)
    {
        config_reg |= (1UL << 2);
    }
    else if (p_config->BitOrder != SPIM_MSB_FIRST)
    {
        SPIM_LOG_ERR("Inst%u: invalid BitOrder %d", p_instance->drv_inst_idx, (int)p_config->BitOrder);
        return SPIM_ERROR_INVALID_PARAM;
    }

    p_instance->Instance->CONFIG = config_reg;

    SPIM_LOG_V("Inst%u: CONFIG register = 0x%08lX", p_instance->drv_inst_idx, (unsigned long)config_reg);

    /* Default ORC (over-read character) - sane default, no spec for it
     * in the header so leaving hardware default behaviour explicit    */
    p_instance->Instance->ORC = 0xFF;

    /* Enable peripheral. SPIM peripherals on nRF52840 use ENABLE = 7   */
    p_instance->Instance->ENABLE = 7;

    p_instance->State = SPIM_READY;

    SPIM_LOG("Init: instance %u ready", p_instance->drv_inst_idx);

    return SPIM_SUCCESS;
}

/**
 * @brief  De-initializes a SPIM instance: disables peripheral and
 *         disconnects all pins.
 */
SPIM_Status_t SPIM_DeInit(SPIM_Instance_t *p_instance)
{
    if (p_instance == NULL)
    {
        SPIM_LOG_ERR("DeInit: NULL instance pointer");
        return SPIM_ERROR_NULL_PTR;
    }

    if (p_instance->Instance == NULL)
    {
        SPIM_LOG_ERR("DeInit: instance %u has no peripheral bound", p_instance->drv_inst_idx);
        return SPIM_ERROR_INVALID_PARAM;
    }

    if ((p_instance->State == SPIM_BUSY_TX) ||
        (p_instance->State == SPIM_BUSY_RX) ||
        (p_instance->State == SPIM_BUSY_TXRX))
    {
        SPIM_LOG_ERR("DeInit: instance %u busy (state=%d), stopping first", p_instance->drv_inst_idx, (int)p_instance->State);
        SPIM_Stop(p_instance);
    }

    SPIM_LOG("DeInit: tearing down instance %u", p_instance->drv_inst_idx);

    p_instance->Instance->ENABLE = 0;

    SPIM_ConfigurePin(&p_instance->Instance->PSEL.SCK, SPIM_PIN_NOT_CONNECTED);
    SPIM_ConfigurePin(&p_instance->Instance->PSEL.MOSI, SPIM_PIN_NOT_CONNECTED);
    SPIM_ConfigurePin(&p_instance->Instance->PSEL.MISO, SPIM_PIN_NOT_CONNECTED);

    p_instance->State = SPIM_READY;

    SPIM_LOG("DeInit: instance %u done", p_instance->drv_inst_idx);

    return SPIM_SUCCESS;
}

/**
 * @brief  Blocking transmit-only transfer.
 */
SPIM_Status_t SPIM_Transmit(SPIM_Instance_t *p_instance, uint8_t *p_tx_buf, uint16_t length)
{
    if ((p_instance == NULL) || (p_tx_buf == NULL))
    {
        SPIM_LOG_ERR("Transmit: NULL pointer passed (inst=%p, buf=%p)", (void *)p_instance, (void *)p_tx_buf);
        return SPIM_ERROR_NULL_PTR;
    }

    if (length == 0)
    {
        SPIM_LOG_ERR("Inst%u: Transmit called with length 0", p_instance->drv_inst_idx);
        return SPIM_ERROR_INVALID_PARAM;
    }

    if (p_instance->State != SPIM_READY)
    {
        SPIM_LOG_ERR("Inst%u: Transmit rejected, instance busy (state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);
        return SPIM_ERROR_BUSY;
    }

    SPIM_LOG("Inst%u: Transmit starting, %u bytes", p_instance->drv_inst_idx, length);
    SPIM_LOG_V("Inst%u: TX buf @ %p, first byte = 0x%02X", p_instance->drv_inst_idx, (void *)p_tx_buf, p_tx_buf[0]);

    p_instance->State = SPIM_BUSY_TX;

    p_instance->Instance->TXD.PTR    = (uint32_t)p_tx_buf;
    p_instance->Instance->TXD.MAXCNT = length;
    p_instance->Instance->RXD.PTR    = 0;
    p_instance->Instance->RXD.MAXCNT = 0;

    p_instance->Instance->EVENTS_END = 0;
    p_instance->Instance->TASKS_START = 1;

    SPIM_Status_t status = SPIM_WaitForEnd(p_instance);

    p_instance->State = SPIM_READY;

    if (status == SPIM_SUCCESS)
    {
        SPIM_LOG("Inst%u: Transmit complete (%u bytes, txd.amount=%lu)",
                 p_instance->drv_inst_idx, length, (unsigned long)p_instance->Instance->TXD.AMOUNT);
    }
    else
    {
        SPIM_LOG_ERR("Inst%u: Transmit failed, status=%d", p_instance->drv_inst_idx, (int)status);
    }

    return status;
}

/**
 * @brief  Blocking receive-only transfer.
 */
SPIM_Status_t SPIM_Receive(SPIM_Instance_t *p_instance, uint8_t *p_rx_buf, uint16_t length)
{
    if ((p_instance == NULL) || (p_rx_buf == NULL))
    {
        SPIM_LOG_ERR("Receive: NULL pointer passed (inst=%p, buf=%p)", (void *)p_instance, (void *)p_rx_buf);
        return SPIM_ERROR_NULL_PTR;
    }

    if (length == 0)
    {
        SPIM_LOG_ERR("Inst%u: Receive called with length 0", p_instance->drv_inst_idx);
        return SPIM_ERROR_INVALID_PARAM;
    }

    if (p_instance->State != SPIM_READY)
    {
        SPIM_LOG_ERR("Inst%u: Receive rejected, instance busy (state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);
        return SPIM_ERROR_BUSY;
    }

    SPIM_LOG("Inst%u: Receive starting, %u bytes requested", p_instance->drv_inst_idx, length);

    p_instance->State = SPIM_BUSY_RX;

    p_instance->Instance->TXD.PTR    = 0;
    p_instance->Instance->TXD.MAXCNT = 0;
    p_instance->Instance->RXD.PTR    = (uint32_t)p_rx_buf;
    p_instance->Instance->RXD.MAXCNT = length;

    p_instance->Instance->EVENTS_END = 0;
    p_instance->Instance->TASKS_START = 1;

    SPIM_Status_t status = SPIM_WaitForEnd(p_instance);

    p_instance->State = SPIM_READY;

    if (status == SPIM_SUCCESS)
    {
        SPIM_LOG("Inst%u: Receive complete (%u bytes, rxd.amount=%lu)",
                 p_instance->drv_inst_idx, length, (unsigned long)p_instance->Instance->RXD.AMOUNT);
        SPIM_LOG_V("Inst%u: first byte received = 0x%02X", p_instance->drv_inst_idx, p_rx_buf[0]);
    }
    else
    {
        SPIM_LOG_ERR("Inst%u: Receive failed, status=%d", p_instance->drv_inst_idx, (int)status);
    }

    return status;
}

/**
 * @brief  Blocking full-duplex transfer.
 */
SPIM_Status_t SPIM_Transfer(SPIM_Instance_t *p_instance, uint8_t *p_tx_buf, uint8_t *p_rx_buf, uint16_t length)
{
    if ((p_instance == NULL) || (p_tx_buf == NULL) || (p_rx_buf == NULL))
    {
        SPIM_LOG_ERR("Transfer: NULL pointer passed (inst=%p, tx=%p, rx=%p)",
                      (void *)p_instance, (void *)p_tx_buf, (void *)p_rx_buf);
        return SPIM_ERROR_NULL_PTR;
    }

    if (length == 0)
    {
        SPIM_LOG_ERR("Inst%u: Transfer called with length 0", p_instance->drv_inst_idx);
        return SPIM_ERROR_INVALID_PARAM;
    }

    if (p_instance->State != SPIM_READY)
    {
        SPIM_LOG_ERR("Inst%u: Transfer rejected, instance busy (state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);
        return SPIM_ERROR_BUSY;
    }

    SPIM_LOG("Inst%u: Full-duplex transfer starting, %u bytes", p_instance->drv_inst_idx, length);
    SPIM_LOG_V("Inst%u: TX buf @ %p, RX buf @ %p", p_instance->drv_inst_idx, (void *)p_tx_buf, (void *)p_rx_buf);

    p_instance->State = SPIM_BUSY_TXRX;

    p_instance->Instance->TXD.PTR    = (uint32_t)p_tx_buf;
    p_instance->Instance->TXD.MAXCNT = length;
    p_instance->Instance->RXD.PTR    = (uint32_t)p_rx_buf;
    p_instance->Instance->RXD.MAXCNT = length;

    p_instance->Instance->EVENTS_END = 0;
    p_instance->Instance->TASKS_START = 1;

    SPIM_Status_t status = SPIM_WaitForEnd(p_instance);

    p_instance->State = SPIM_READY;

    if (status == SPIM_SUCCESS)
    {
        SPIM_LOG("Inst%u: Transfer complete (tx.amount=%lu, rx.amount=%lu)",
                 p_instance->drv_inst_idx,
                 (unsigned long)p_instance->Instance->TXD.AMOUNT,
                 (unsigned long)p_instance->Instance->RXD.AMOUNT);
        SPIM_LOG_V("Inst%u: first byte received = 0x%02X", p_instance->drv_inst_idx, p_rx_buf[0]);
    }
    else
    {
        SPIM_LOG_ERR("Inst%u: Transfer failed, status=%d", p_instance->drv_inst_idx, (int)status);
    }

    return status;
}

/**
 * @brief  Immediately stops any in-progress transfer and forces the
 *         instance back to READY.
 */
void SPIM_Stop(SPIM_Instance_t *p_instance)
{
    if (p_instance == NULL)
    {
        SPIM_LOG_ERR("Stop: NULL instance pointer");
        return;
    }

    SPIM_LOG("Inst%u: Stop requested (was state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);

    p_instance->Instance->TASKS_STOP = 1;
    p_instance->Instance->EVENTS_END = 0;
    p_instance->State = SPIM_READY;

    SPIM_LOG("Inst%u: Stop complete, state forced to READY", p_instance->drv_inst_idx);
}

/**
 * @brief  Suspends an in-progress transfer (pauses, can be resumed).
 */
void SPIM_Suspend(SPIM_Instance_t *p_instance)
{
    if (p_instance == NULL)
    {
        SPIM_LOG_ERR("Suspend: NULL instance pointer");
        return;
    }

    if ((p_instance->State != SPIM_BUSY_TX) &&
        (p_instance->State != SPIM_BUSY_RX) &&
        (p_instance->State != SPIM_BUSY_TXRX))
    {
        SPIM_LOG_ERR("Inst%u: Suspend ignored, instance not busy (state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);
        return;
    }

    SPIM_LOG("Inst%u: Suspending active transfer (state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);

    p_instance->Instance->TASKS_SUSPEND = 1;

    SPIM_LOG_V("Inst%u: TASKS_SUSPEND triggered", p_instance->drv_inst_idx);
}

/**
 * @brief  Resumes a previously suspended transfer.
 */
void SPIM_Resume(SPIM_Instance_t *p_instance)
{
    if (p_instance == NULL)
    {
        SPIM_LOG_ERR("Resume: NULL instance pointer");
        return;
    }

    if ((p_instance->State != SPIM_BUSY_TX) &&
        (p_instance->State != SPIM_BUSY_RX) &&
        (p_instance->State != SPIM_BUSY_TXRX))
    {
        SPIM_LOG_ERR("Inst%u: Resume ignored, instance not in a suspended-capable state (state=%d)",
                      p_instance->drv_inst_idx, (int)p_instance->State);
        return;
    }

    SPIM_LOG("Inst%u: Resuming transfer (state=%d)", p_instance->drv_inst_idx, (int)p_instance->State);

    p_instance->Instance->TASKS_RESUME = 1;

    SPIM_LOG_V("Inst%u: TASKS_RESUME triggered", p_instance->drv_inst_idx);
}


/******************************* END OF FILE *********************************/