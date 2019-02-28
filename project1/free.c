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
* @file free.c
* @brief This source file contains code that provides the free() function definition
* and reserves a block of memory of the specified number of bytes.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 24 2019
* @version 1.1
*
*/

#include "memtest.h"
#include "free.h"

void free_memory(int *pointer)
{
	if (*pointer) /* use for calloc */
/*	if (!*pointer) // user for malloc */
	{
		printf("Null pointer was provided. Previous released memory: \n");
	}
	else {
		free(pointer);
	}
	return;
}
