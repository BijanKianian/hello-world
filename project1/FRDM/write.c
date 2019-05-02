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
* @file write.c
* @brief This source file contains a c program to manipulate and test memory.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 23 2019
* @version 1.0
*
*/
#include "memtest.h"
#include "write.h"

void write(int32_t* address, int32_t offset, int32_t value)
{
    *(address + offset) = value;
#if FRDM
    printf(" Value: %lx written at address: %p\n\n", value, address + offset);
#else
    printf(" Value: %x written at address: %p\n\n", value, address + offset);
#endif
    printf("PES_Prj1 >> ");
    return;
}
