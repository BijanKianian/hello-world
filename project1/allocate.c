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
* @file allocate.c
* @brief This source file contains a c program to manipulate and test memory.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 23 2019
* @version 1.3
*
*/
/*===================================*/
/*            allocate()             */
/*===================================*/
#include "memtest.h"

int* allocate(int offset)
{
  int *ptr;
  ptr =(int*) calloc(offset, sizeof(int));  // assigning an int pointer to the block of memory with requested size

  if (ptr == NULL)                          // check if there is a room available in the heap
    printf("Allocation failed!\n\n");

  return ptr;
 }

