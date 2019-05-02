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
* @file project_2.c
* @brief This header file provides the uart prototypes and include files.
*
* @authors: Ismail Yesildirek & Bijan Kianian
* @date April 21 2019
* @version 1.1
*
*/

/*========================================================================*/
#include <UART.h>
/*========================================================================*/

char temp_TX_char [MAX_LENGTH] = {'\0'} ;
char temp_RX_char ;

#if !BLOCKING
char data_in      [MAX_LENGTH] = {'\0'} ;

char data_out     [MAX_LENGTH] = {'\0'} ;

static uint32_t Old_RX_Head ;
uint32_t bufferSize = MAX_LENGTH ;
int32_t RX_Entries, TX_Entries ;
ring_t *RX_rb = NULL ;			/* Receive ring buffer handler */
ring_t *TX_rb = NULL ;			/* Transmit ring buffer */

#endif

int main(void)
{
	/************************
	 * Init board hardware.	*
	 ************************/
	BOARD_InitBootPins();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

#if BLOCKING

	gpio_config();
    /* Start UART for tx and rx*/
    uart_config();
    print_ASCII();
	temp_TX_char[0] = '\n';
    uart_tx(temp_TX_char);

#else

    __disable_irq();
    uart_config();
    gpio_config();
    __enable_irq();



    RX_rb = init(bufferSize);
    TX_rb = init(bufferSize);

    uint32_t RX_Head = RX_rb->Ini;
    Old_RX_Head = RX_Head;				/* Since current ring buffer head is pointing
     	 	 	 	 	 	 	 	 	 * to the next available (empty) space, the previous
     	 	 	 	 	 	 	 	 	 * head is used echo which is pointing to a valid data.*/

    char* RX_Buffer = RX_rb->Buffer;

	printf("\n\r### Please enter a string then press 'Enter' to see the report ###\n\n\r");

#endif
    while (1)
    {
#if !BLOCKING
    	TX_Entries = entries(TX_rb);
    	RX_Entries = entries(RX_rb);

    	UART_Read(data_in, RX_Entries, RX_rb);
    	echo(*(RX_Buffer + Old_RX_Head), RX_rb, TX_rb, &Old_RX_Head);		// To echo the characters on screen

		if ((RX_rb->Buffer_Full)||(temp_RX_char == 13))
		{
			if (RX_Entries == bufferSize)
				printf("\n\n\rYou have reached to the end of the receiver buffer!\n\r");

			printf("\n\n\rReport\r");
			printf("\n______\n\r");

			UART0->C2 &= ~UART_C2_RIE_MASK;
			UART0->C2 &= ~(UART_C2_TIE_MASK|UART_C2_TCIE_MASK);

			report(RX_rb, TX_rb, data_out);


			RX_Entries = 0;				/* Resetting the RX/TX ring buffers */
			RX_rb->Buffer_Full = 0;
			RX_rb->Ini = 0;
			RX_rb->Outi = 0;
			temp_RX_char = '\0';		/* Reseting the temp input char to prevent looping */

			for(uint32_t k = 0 ; k < bufferSize ; k++)
				*(RX_Buffer+k) = '\0';
			//delay(20);
		}

		/* Blink LED */

    	led();
    	delay(20);
#else

		temp_RX_char = uart_rx();
    	delay(1);
   	temp_TX_char[0] = temp_RX_char;
    	uart_tx(temp_TX_char);
    	led();

#endif

	}
}
//
////############################## uart_config() - Start ##################################
//
///*UART0 Register Configuration per Ch12 & 39 of manual*/
//void uart_config(void)
//{
//	/******************************************
//	 * Clock configuration
//	 *****************************************/
//	SIM->SCGC4 |= SIM_SCGC4_UART0_MASK;;		/* Enable UART0 clock */
//	SIM->SOPT2 &= ~SIM_SOPT2_UART0SRC_MASK;		/* Select a clock source*/
//	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);        /* FLL/PLL source*/
//
//	/******************************************
//	 * Baud Rate Configuration
//	 * To set baud rate we divide selected clock
//	 * by the SBR (BDH:BDL) and OSR (in C4)
//	 * baud clock/((OSR+1) × BR)
//	 * Base clock is 20.97 MHz / 13 / 14
//	 * = 115200 Baud Rate
//	 ******************************************/
//
//	UART0->BDH = 0x00;	/*Set BDH to 0bxxx00000*/
//	UART0->BDL = 0x0D;	/*Set SBR to 0bxxxx1101 or 13 decimal*/
//	UART0->C4 = 0x0E;	/* Set data bit mode to 8 or 9 and over sampling ratio
//	 	 	 	 	 	 * By writing 0bxxx01110 (or 14 OSR) to reg C4*/
//
//#if BLOCKING
//
//	UART0->C2 = 0x0C;	/* Enable both tx and rx */
//	/*Enable port B clock */
//
//	SIM->SCGC5 |= 0x0400;
//	PORTB->PCR[17] = 0x0300; //for tx
//	PORTB->PCR[16] = 0x0300; //for rx
//
//#else
//
//	/******************************
//	 * Enable tx, rx, and IRQ rx
//	 * by sending 0b00101100 to reg
//	 ******************************/
//
//	/* Select "Alt 2" usage to enable UART0 Tx/Rx*/
//
//	UART0->C2 = 0;
//    UART0->C1 = 0;
//    UART0->C3 = 0;
//
//	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;			/* Enable PORTA clock */
//
//	PORTA->PCR[1] = PORT_PCR_MUX(2);
//	PORTA->PCR[2] = PORT_PCR_MUX(2);
//
//	UART0->C2 = UARTLP_C2_RE_MASK | UARTLP_C2_TE_MASK | UART_C2_RIE_MASK;
//	NVIC_EnableIRQ(UART0_IRQn);
//
//#endif
//
//}
////############################## uart_config() - End ##################################
//
///********************** gpio_config() - Start ******************/
//void gpio_config(void)
//{
//#if BLOCKING
//
//	/*Enable RGB - Green LED PTB19 as GPIO and output*/
//
//	SIM->SCGC5 |= 0x400;
//	PORTB->PCR[19] = 0x100;
//	PTB->PDDR |= 0x80000;
//
//#else
//
//	/*Enable RGB - Blue LED PTD1 as GPIO and output*/
//
//	SIM->SCGC5 |= 0x1000;
//	PORTD->PCR[1] = 0x100;
//	PTD->PDDR = 0x02;
//	PTD->PTOR |= 0x02;
//
//#endif
//}
///********************** gpio_config() - End ********************/
//
////############# Transmission - Start ###########
//
///* Hold until buffer is empty (TDRE = 1),
// * and no transmission in progress (TC = 1)*/
//
//void tx_Status(void)
//{
//	while(!(UART0->S1 & 0xC0)) { }
//}
//
///* Data transmission */
//
//void uart_tx(char* temp)
//{
//	tx_Status();
//	UART0->D = *temp;
//}
////############# Transmission - End ###########
//
////{{{{{{{{{{{{{ Receiving - Start }}}}}}}}}}}}
//
//void rx_Status(void)
//{
//	while(!(UART0->S1 & 0x20)) { }	/* hold until rx buffer is full */
//}
//
///* Data reception */
//
//uint8_t uart_rx(void)
//{
//	rx_Status();
//	uint8_t temp = UART0->D;
//	return temp;
//}
////{{{{{{{{{{{{{ Receiving - End }}}}}}}}}}}}}
//
//void led(void)
//{
//#if BLOCKING
//
//	PTB->PTOR |=  0x80000;	/* Toggle pin 19 Green LED */
//
//#else
//
//	PTD->PTOR |= 0x02;	/* Toggle pin 1 Blue LED */
//
//#endif
//}
//
///******************* delay () - Start *******************/
//
//void delay (uint8_t num)	/* Delay n milliseconds @ 20.97 MHZ clock*/
// {
// 	for(uint16_t i =0; i < num ; i++)
// 	{
// 		for (uint16_t j = 0; j< 2000; j++)
// 		{
// 		}
// 	}
// }
///******************* delay () - End *********************/
//#if BLOCKING
////((((((((((((( print_ASCII() - Start )))))))))))))))))))))))
//
//void print_ASCII(void)
//{
//		/*### Printing the ASCII table ###*/
//
//	for (uint16_t k=33; k <256 ; k++ )
//		{
//			temp_TX_char[0] = k;
//			uart_tx(temp_TX_char);
//			delay(1);
//		}
//	temp_TX_char[0] = '\n' ;
//	uart_tx(temp_TX_char)  ;
//
//	temp_TX_char[0] = '\r' ;
//	uart_tx(temp_TX_char)  ;
//}
////((((((((((((( print_ASCII() - End )))))))))))))))))))))))
//#else

#if !BLOCKING

/*////////////////////// UART0 interrupt handler - Start////////// */

void UART0_IRQHandler(void)
{

	/****************
	 * RX ISR Handler
	 * **************/

	if ((UART0->S1 & UART0_S1_RDRF_MASK) && !RX_rb->Buffer_Full)
	{
		temp_RX_char = uart_rx();			// Read the characters from UART per RDRF = 1 interrupt.
		insert(RX_rb, temp_RX_char);		// insert the character to the RX ring buffer

		if(RX_rb->Buffer_Full)				// RX ring buffer is full, then disable receive interrupt.
			UART0->C2 &= ~UART_C2_RIE_MASK;

	}

	/****************
	 * TX ISR Handler
	 * **************/

	if ((UART0->S1 & (UART0_S1_TDRE_MASK|UART0_S1_TC_MASK)) && !TX_rb->Buffer_Empty)
	{
		read (TX_rb, data_out);			// To echo input characters.
		uart_tx(data_out);				// Write to the TX ring buffer, then data_out[] for further Apps.

		if(TX_rb->Buffer_Empty)			// TX ring buffer is empty, then disable transmit interrupt.
			UART0->C2 &= ~(UART_C2_TIE_MASK | UART_C2_TCIE_MASK);
	}
}
/*//////////////////// UART0 interrupt handler - End ////////// */

///*@@@@@@@@@@@@@@@@@@@@@@ charCounts() - Start @@@@@@@@@@@@@@@@@@@@*/
//
///* This function is a helper to return the number of one character
// * in a given string, here Rx input ring buffer. */
//
//uint32_t charCounts(char ascii)
//
//{
//	char* rb;
//	uint32_t num = 0 ;
//	rb = RX_rb->Buffer;
//
//	for (uint32_t n = 0; n < RX_Entries; n++)
//		if (*(rb+n) == ascii)
//			num++;
//
//	return num;
//}
//
///*@@@@@@@@@@@@@@@@@@@@@@ charCounts() - End @@@@@@@@@@@@@@@@@@@@*/
//
///*%%%%%%%%%%%%%%%%%%%%%% report() - Start %%%%%%%%%%%%%%%%%%%%%%*/
//
///* This function will compare the input characters with 256 ASCII codes
// * one by one and saves the report string in a format of "char - count"
// * into data-out[] array. Then delivers the report to the Transmitter in-
// * -order to show on screen.
// */
//
//
//void report (void)
//{
//	/* Making TX buffer & data_out ready for reporting */
//
//	TX_Entries = 0;
//	TX_rb->Buffer_Full = 0;
//	TX_rb->Ini = 0;
//	TX_rb->Outi = 0;
//
//	for(uint32_t i ; i < MAX_LENGTH ; i++)
//		data_out  [i] = '\0';
//
//	for (uint32_t i = 33 ; i < 256 ; i++)
//	 {
//		uint32_t rept = charCounts(i);		// Repetition count for each character
//
//		if (rept != 0)
//		{
//			sprintf(data_out, "%c - %d\n\r", i, rept);
//			UART_Write(data_out, MAX_LENGTH);
//
//			delay(25);
//		}
//
//	 }
//
//	insert(TX_rb,'\n');			// Adding one line to the end of the report (just cosmetics)
//	UART0->C2 |= (UART_C2_TIE_MASK|UART_C2_TCIE_MASK);
//}
//
///*/*%%%%%%%%%%%%%%%%%%%%%% report() - End %%%%%%%%%%%%%%%%%%%%%%*/
//
///*(((((((((((((((((((((((((((( echo () - Start ))))))))))))))))))*/
//
//void echo(char ch)
//{
//	if(ch != '\0')
//		if ((Old_RX_Head != RX_rb->Ini) && !TX_rb->Buffer_Full)
//		{
//			insert(TX_rb,ch);
//			UART0->C2 |= (UART_C2_TIE_MASK|UART_C2_TCIE_MASK);
//		}
//	Old_RX_Head = RX_rb->Ini;
//}
//
///*(((((((((((((((((((((((((((( echo () - End ))))))))))))))))))*/
//
// /*------------------------- UART_Read () - Start ---------------------*/
//
//void UART_Read(char* input, int32_t entries)
//{
//	strncpy(input, RX_rb->Buffer, entries);
//	UART0->C2 |= UART_C2_RIE_MASK;	/* Enable Rx interrupt for RDRF */
//}
///*------------------------- UART_Read () - End -------------------------*/
//
///*__________________________ UART_Write () - Start _____________________*/
//
//void UART_Write(char* output, int32_t Size)
//{
//	for(uint32_t m = 0 ; m < Size ; m++)
//		if(*(output + m) != '\0')
//			insert(TX_rb, *(output + m));
//
//	UART0->C2 |= (UART_C2_TIE_MASK | UART_C2_TCIE_MASK);	/* Enable Tx interrupt for for TDRE and TC */
//}
///*__________________________ UART_Write () - End _______________________*/
//
#endif // Non-Blocking
//
