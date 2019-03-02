/*
* @file allocate.c
* @brief This source file contains code that provides the allocate() function definition
* and frees the space allocated in the memory pointed by ptr.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date March 1 2019
* @version 1.0
*
*/

#include "memtest.h"
#include "validate.h"

void validate(int* Block_Address, int StartOffset, int NumberOfwords, unsigned int userSeed)
{
	unsigned int a = 1664525;    /* Multiplier */
    unsigned int c = 1013904223; /* Increment */
    unsigned long int m = pow(2,32);       /* Modulus */
	int Seed = userSeed;
	clock_t executionT;
	int identical =0;

	pattern(Block_Address + StartOffset, NumberOfwords, userSeed);
	executionT = clock();
	for (int i = 0; i < NumberOfwords-1; i++)
		{
			Seed = (a * Seed + c) % m;
			int value = *(Block_Address + StartOffset + i);
			if (value != Seed)
			{
				printf("Discrepancy at address: %p\n", Block_Address+StartOffset + i);
				printf("Expected value: %x, Actual value: %x\n", Seed, *(Block_Address + StartOffset + i));
				identical = 1;
			}
		}
		  executionT = clock() - executionT;
          double time = ((double)executionT)/CLOCKS_PER_SEC;
		if (identical == 0)
			printf("The expected and actual values are identical!\n");

		printf("Pattern function execution time is milli: %fsec.\n",time*1000);
		printf("Enter another command \n\n");
		printf("PES_Prj1 >> ");

		return;
}


