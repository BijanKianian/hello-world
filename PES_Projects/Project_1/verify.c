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
/*
* @file verify.c
* @brief This source file contains code that provides the verify() function definition
* and is used to validate the linear Congruential Generator pattern(). 
*
* @author Ismail Yesildirek & Bijan Kianian
* @date March 10 2019
* @version 1.02
*/

#include "memtest.h"
#include "verify.h"

void verify(int32_t* Block_Address, int32_t StartOffset, int32_t NumberOfwords, int32_t userSeed)
{
	uint32_t a = 1664525;    /* Multiplier */
    uint32_t c = 1013904223; /* Increment */
    uint32_t m = (uint32_t)pow(2,32);       /* Modulus */
	int32_t Seed = userSeed;
	uint8_t identical =0;
	//pattern(Block_Address + StartOffset, NumberOfwords, userSeed);

#if FRDM
	 uint32_t count = 0;			/* Counter value */
	 uint32_t elapsedTime = 0;		/* time value in micro or nano seconds */
	 uint16_t done = SysTick_Config(16000000);		/* Enable the counting, every 1 microsec the counter 'count' will increment */
	 if(done)
	{
	 printf("Reset Systick");
	}
#else
	clock_t executionT;
	executionT = clock();
#endif

	for (int32_t i = 0; i < NumberOfwords-1; i++)
		{
		/*Re-Generate Seed and compare with exiting memory block*/
			Seed = (a * Seed + c) % m;
			int32_t value = *(Block_Address + StartOffset + i);
			if (value != Seed)
			{
				printf("Discrepancy at address: %p\n", Block_Address+StartOffset + i);
#if FRDM
				printf("Expected value: %lx, Actual value: %lx\n", Seed, *(Block_Address + StartOffset + i));
				identical = 1;
#else
				printf("Expected value: %x, Actual value: %x\n", Seed, *(Block_Address + StartOffset + i));
				identical = 1;	
#endif
			}
		}

#if FRDM
	count = SYSTICK_MAX - SysTick->VAL;		/* SysTick->VAL holds the decremented value of systick timer register */
											/* 'count' holds number of ticks, each tick takes ~21 nanosecond (48 MHZ clock)*/
	SysTick->CTRL = 4 ;						/* Disable couting = 0b100 */

	if ((21*count) >=100000)
		{
			elapsedTime = 21*count / 1000;	/* For demonstrating 3 digit in micro seconds */
			printf("Verify function execution time is %ld microseconds\n", elapsedTime);
		}
	else
		{
			elapsedTime = 21*count;
			printf("Verify function execution time is %ld nanoseconds\n", elapsedTime);
		}
#else
	executionT = clock() - executionT;
    double time = ((double)executionT)/CLOCKS_PER_SEC;
    printf("Pattern function execution time is milli: %fsec.\n",time*1000);
	
#endif
		if (identical == 0)
		{
			printf("The expected and actual values are identical!\n");
		}
		printf("Enter another command \n\n");
		printf("PES_Prj1 >> ");
		return;
}


