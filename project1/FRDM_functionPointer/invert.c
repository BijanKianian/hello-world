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
* @file invert.c
* @brief This source file contains code that provides the invert() function definition
* and inverts all memory bits in a specified area of memory. This function also provides
* the time taken to perform the operation.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 24 2019
* @version 1.0
*
*/

#include "memtest.h"
#include "invert.h"

void invert(int32_t* address, int32_t offset)
{
	if(address ==NULL)
	{
		printf("Null pointer provided try again.\n");
		return;
	}
	else
	{
	int32_t temp = *(address + offset);
	//printf(" Current Value: %x written at address: %p\n\n", *(address + offset), address + offset);
	int32_t bitPosition;
    for (int32_t i = 0; i < 32; i++)
	{
		bitPosition = 1<<i;
		temp = (temp ^ bitPosition);
	}

	int32_t value = temp;

	/*write to memory section*/
	*(address + offset) = value;
	//printf("\n");
	}
	return;
}
