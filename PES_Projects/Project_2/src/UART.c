
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
* @file UART.c
* @brief This header file provides the ring buffer prototypes, and buffer structure.
*
* @authors: Ismail Yesildirek & Bijan Kianian
* @date April 21 2019
* @version 1.0
*
*/

/*========================================================================*/
#include "UART.h"
#include "ring.h"
/*========================================================================*/

//############################## uart_config() - Start ##################################

/*UART0 Register Configuration per Ch12 & 39 of manual*/
void uart_config(void)
{
	/******************************************
	 * Clock configuration
	 *****************************************/
	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;;		/* Enable UART0 clock */
	SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;		/* Select a clock source*/
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);        /* FLL/PLL source*/

	/******************************************
	 * Baud Rate Configuration
	 * To set baud rate we divide selected clock
	 * by the SBR (BDH:BDL) and OSR (in C4)
	 * baud clock/((OSR+1) × BR)
	 * Base clock is 20.97 MHz / 13 / 14
	 * = 115200 Baud Rate
	 ******************************************/

	UART0->BDH = 0x00;	/*Set BDH to 0bxxx00000*/
	UART0->BDL = 0x0D;	/*Set SBR to 0bxxxx1101 or 13 decimal*/
	UART0->C4 = 0x0E;	/* Set data bit mode to 8 or 9 and over sampling ratio
	 	 	 	 	 	 * By writing 0bxxx01110 (or 14 OSR) to reg C4*/

#if BLOCKING

	UART0->C2 = 0x0C;	/* Enable both tx and rx */
	/*Enable port B clock */

	SIM->SCGC5 |= 0x0400;
	PORTB->PCR[17] = 0x0300; //for tx
	PORTB->PCR[16] = 0x0300; //for rx

#else

	/******************************
	 * Enable tx, rx, and IRQ rx
	 * by sending 0b00101100 to reg
	 ******************************/

	/* Select "Alt 2" usage to enable UART0 Tx/Rx*/

	UART0->C2 = 0;
    UART0->C1 = 0;
    UART0->C3 = 0;

	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;			/* Enable PORTA clock */

	PORTA->PCR[1] = PORT_PCR_MUX(2);
	PORTA->PCR[2] = PORT_PCR_MUX(2);

	UART0->C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UART_C2_RIE_MASK;
	NVIC_EnableIRQ(UART0_IRQn);

#endif

}
//############################## uart_config() - End ##################################

/********************** gpio_config() - Start ******************/
void gpio_config(void)
{
#if BLOCKING

	/*Enable RGB - Green LED PTB19 as GPIO and output*/

	SIM->SCGC5 |= 0x400;
	PORTB->PCR[19] = 0x100;
	PTB->PDDR |= 0x80000;

#else

	/*Enable RGB - Blue LED PTD1 as GPIO and output*/

	SIM->SCGC5 |= 0x1000;
	PORTD->PCR[1] = 0x100;
	PTD->PDDR = 0x02;
	PTD->PTOR |= 0x02;

#endif
}
/********************** gpio_config() - End ********************/

//############# Transmission - Start ###########

/* Hold until buffer is empty (TDRE = 1),
 * and no transmission in progress (TC = 1)*/

void tx_Status(void)
{
	while(!(UART0->S1 & 0xC0)) { }
}

/* Data transmission */

void uart_tx(char* temp)
{
	tx_Status();
	UART0->D = *temp;
}
//############# Transmission - End ###########

//{{{{{{{{{{{{{ Receiving - Start }}}}}}}}}}}}

void rx_Status(void)
{
	while(!(UART0->S1 & 0x20)) { }	/* hold until rx buffer is full */
}

/* Data reception */

uint8_t uart_rx(void)
{
	rx_Status();
	uint8_t temp = UART0->D;
	return temp;
}
//{{{{{{{{{{{{{ Receiving - End }}}}}}}}}}}}}

void led(void)
{
#if BLOCKING

	PTB->PTOR |=  0x80000;	/* Toggle pin 19 Green LED */

#else

	PTD->PTOR |= 0x02;	/* Toggle pin 1 Blue LED */

#endif
}

//((((((((((((( print_ASCII() - Start )))))))))))))))))))))))

void print_ASCII(void)
{
		/*### Printing the ASCII table ###*/

	char temp[1];
	for (uint16_t k=33; k <256 ; k++ )
		{
			temp[0] = k;
			uart_tx(temp);
			delay(1);
		}
	temp[0] = '\n' ;
	uart_tx(temp)  ;

	temp[0] = '\r' ;
	uart_tx(temp)  ;
}
//((((((((((((( print_ASCII() - End )))))))))))))))))))))))


/*@@@@@@@@@@@@@@@@@@@@@@ charCounts() - Start @@@@@@@@@@@@@@@@@@@@*/

/* This function is a helper to return the number of one character
 * in a given string, here Rx input ring buffer. */

uint32_t charCounts(char ascii, ring_t* ringBuffer)

{
	char* rb;
	int32_t Entries;
	uint32_t num = 0 ;

	Entries = entries (ringBuffer);
	rb = ringBuffer->Buffer;

	for (uint32_t n = 0; n < Entries; n++)
		if (*(rb+n) == ascii)
			num++;

	return num;
}

/*@@@@@@@@@@@@@@@@@@@@@@ charCounts() - End @@@@@@@@@@@@@@@@@@@@*/

/*%%%%%%%%%%%%%%%%%%%%%% report() - Start %%%%%%%%%%%%%%%%%%%%%%*/

/* This function will compare the input characters with 256 ASCII codes
 * one by one and saves the report string in a format of "char - count"
 * into data-out[] array. Then delivers the report to the Transmitter in-
 * -order to show on screen.
 */


void report (ring_t* RX_ringBuffer, ring_t* TX_ringBuffer, char* dataOut)
{
	/* Making TX buffer & data_out ready for reporting */

	UART0->C2 &= ~UART_C2_RIE_MASK;		//  Disabling Receiver during report
	TX_ringBuffer->Buffer_Full = 0;
	TX_ringBuffer->Ini = 0;
	TX_ringBuffer->Outi = 0;

	for(uint32_t i ; i < MAX_LENGTH ; i++)
		dataOut [i] = '\0';

	for (uint32_t i = 33 ; i < 256 ; i++)
	 {
		uint32_t rept = charCounts(i, RX_ringBuffer);		// Repetition count for each character

		if (rept != 0)
		{
			sprintf(dataOut, "%c - %d\n\r", i, rept);
			UART_Write(dataOut, MAX_LENGTH, TX_ringBuffer);

			delay(25);
		}
	 }

	insert(TX_ringBuffer,'\n');			// Adding one line to the end of the report (just cosmetics)
	UART0->C2 |= (UART_C2_TIE_MASK|UART_C2_TCIE_MASK);
}

/*/*%%%%%%%%%%%%%%%%%%%%%% report() - End %%%%%%%%%%%%%%%%%%%%%%*/

/*(((((((((((((((((((((((((((( echo () - Start ))))))))))))))))))*/

void echo(char ch, ring_t* RX_ringBuffer, ring_t* TX_ringBuffer,uint32_t* RX_PreviousHead)
{
	if(ch != '\0')
		if ((*RX_PreviousHead != RX_ringBuffer->Ini) && !TX_ringBuffer->Buffer_Full)
		{
			insert(TX_ringBuffer,ch);
			UART0->C2 |= (UART_C2_TIE_MASK|UART_C2_TCIE_MASK);
		}
	*RX_PreviousHead = RX_ringBuffer->Ini;
}

/*(((((((((((((((((((((((((((( echo () - End ))))))))))))))))))*/

 /*------------------------- UART_Read () - Start ---------------------*/

void UART_Read(char* input, int32_t entries, ring_t* RX_ringBuffer)
{
	strncpy(input, RX_ringBuffer->Buffer, entries);
	UART0->C2 |= UART_C2_RIE_MASK;	/* Enable Rx interrupt for RDRF */
}
/*------------------------- UART_Read () - End -------------------------*/

/*__________________________ UART_Write () - Start _____________________*/

void UART_Write(char* output, int32_t Size, ring_t* TX_ringBuffer)
{
	for(uint32_t m = 0 ; m < Size ; m++)
		if(*(output + m) != '\0')
			insert(TX_ringBuffer, *(output + m));

	UART0->C2 |= (UART_C2_TIE_MASK | UART_C2_TCIE_MASK);	/* Enable Tx interrupt for for TDRE and TC */
}
/*__________________________ UART_Write () - End _______________________*/


/******************* delay () - Start *******************/

void delay (uint8_t num)	/* Delay n milliseconds @ 20.97 MHZ clock*/
 {
 	for(uint16_t i =0; i < num ; i++)
 	{
 		for (uint16_t j = 0; j< 2000; j++)
 		{
 		}
 	}
 }
/******************* delay () - End *********************/
