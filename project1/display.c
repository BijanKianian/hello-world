/***************************************************************************
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
* @file display.c
* @brief This source file contains code that provides the display() function definition
* and displays content of memory in terms of 32 bit words in hexadecimal format.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 24 2019
* @version 1.4
*
*/

#include "memtest.h"
#include "display.h"

void display(int* address, int offset)
{
    printf("\n   Address                     Value \t Index\n");
    printf("  ------------               ----------\t ------\n");
    for(int i = 0 ; i < offset ; i++)
    {
        printf(" %p              0x%08x    %d\n" , address + i, *(address + i),i);
    }
    printf("\n");
	printf("PES_Prj1 >> ");
    return;
}
