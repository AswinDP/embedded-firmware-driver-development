/*********************************************************************
*                             Aswin D P                              *
*                           The Dual Rook                            *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : tw_nrf52840_board_config.h
Purpose : custom board config header file

*/



/* Master switch for SPIM driver RTT debug logs.
 * 1 = compile logs in (uses RAM/flash + RTT bandwidth + CPU cycles)
 * 0 = fully compiled out, zero footprint                              */
#define SPIM_DEBUG_LOG_ENABLED          1

/* Optional: separate, finer switch for very chatty per-byte logs
 * (transfer start/end is cheap, this one can be noisy on big buffers) */
#define SPIM_DEBUG_LOG_VERBOSE          0