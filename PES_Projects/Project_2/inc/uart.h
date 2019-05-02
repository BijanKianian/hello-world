/*****************************************************************************
* Copyright (C) 2019 by Ismail Yesildirek & Bijan Kianian
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Ismail Yesildirek, Bijan Kianian, and the University of Colorado are not
* liable for any misuse of this material.
*
*****************************************************************************/
/**
* @file uart.h
* @brief This header file provides the uart prototypes and include files.
*
* @authors: Ismail Yesildirek & Bijan Kianian
* @date April 21 2019
* @version 1.1
*
*/

/*========================================================================*/
#define BLOCKING 1
/*========================================================================*/

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "ring.h"

//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}} Functions Prototype - Start {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{

void uart_config(void);							// UART register/clock configuration
void tx_Status(void);							// check for transmit (tx)
void uart_tx(char*);							// transmit char (tx)
void rx_Status (void);							// check for receive (rx)
uint8_t uart_rx(void);							// receive char (rx)
void gpio_config(void);
void led(void);
void delay (uint8_t);
void print_ASCII (void);
uint32_t charCounts(char , ring_t*);			// Find frequency of characters in a string
void report (ring_t*, ring_t*, char*);			// Report on screen
void echo (char, ring_t*, ring_t*, uint32_t*);	// Echo input character, used in manual mode
void UART_Read(char*, int32_t, ring_t*);
void UART_Write(char*, int32_t, ring_t*);

//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}} Functions Prototype - End {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{

