
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
* @file memtest.c
* @brief This source file contains a c program to manipulate and test memory.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 23 2019
* @version 1.3
*
*/

#include "memtest.h"

void display(int* address, int offset)
{

    printf("\n   Address                     Value \n");
    printf("  ------------               ----------\n");

    for(int i = 0 ; i < offset ; i++)
    {
        printf(" %p              0x%08x\n" , address + i, *(address + i));
    }

    printf("\n");
    return;
}
