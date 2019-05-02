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
* @date March 10 2019
* @version 1.5
*
*/

#include "memtest.h"
#include "display.h"

void display(int32_t* address, int32_t offset)
{
#if FRDM
	printf("\n Address                   Value     Index\n");	/* Column width correction for FRDM vs PC platforms*/
	printf("------------             ----------  ------\n");
#else
	printf("\n   Address                     Value \t Index\n");
    printf("  ------------               ----------\t ------\n");
#endif
    for(int16_t i = 0 ; i < offset ; i++)
    {
#if FRDM
        printf(" %p              0x%08lx    %d\n" , address + i, *(address + i),i);
#else
        printf(" %p              0x%08x    %d\n" , address + i, *(address + i),i);
#endif
    }
    printf("\n");
	printf("PES_Prj1 >> ");
    return;
}
