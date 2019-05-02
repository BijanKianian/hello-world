/*
* @file allocate.c
* @brief This source file contains code that provides the allocate() function definition
* and frees the space allocated in the memory pointed by ptr.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date March 6 2019
* @version 1.01
*/

#include "memtest.h"
#include "verify.h"

void verify(int32_t* Block_Address, int32_t StartOffset, int32_t NumberOfwords, uint32_t userSeed)
{
	const uint32_t a = 1664525;    /* Multiplier */
    const uint32_t c = 1013904223; /* Increment */
    uint32_t m = (uint32_t)pow(2,32);       /* Modulus */
	uint32_t Seed = userSeed;
	int32_t identical =0;
	//pattern(Block_Address + StartOffset, NumberOfwords, userSeed);

#if FRDM

	 uint32_t count = 0;			/* Counter value */
	 uint32_t elapsedTime = 0;		/* time value in micro or nano seconds */
	 uint16_t done = SysTick_Config(16000000);		/* Enable the counting, every 1 microsec the counter 'count' will increment */
	 if(done)
	   printf("Reset Systick");

	 #else
	clock_t executionT;
	executionT = clock();
#endif

	for (int16_t i = 0; i < NumberOfwords-1; i++)
		{
			Seed = (a * Seed + c) % m;
			uint32_t value = *(Block_Address + StartOffset + i);
			if (value != Seed)
			{
				printf("Discrepancy at address: %p\n", Block_Address+StartOffset + i);
#if FRDM
				printf("Expected value: %lx, Actual value: %lx\n", Seed, *(Block_Address + StartOffset + i));
				identical = 1;
#else
				printf("Expected value: %x, Actual value: %x\n", Seed, *(Block_Address + StartOffset + i));
				identical = 1;
#endif // FRDM
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
			printf("The expected and actual values are identical!\n");

		printf("Enter another command \n\n");
		printf("PES_Prj1 >> ");

		return;
}


