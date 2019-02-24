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
* @brief This source file contains code that provides the help function definition.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 21  2019
* @version 1.0
*
*//*===================================*/
/*          free_memory()           */
/*===================================*/

#include "memtest.h"

void free_memory(int *pointer)
{
    free(pointer);
   return;
}
