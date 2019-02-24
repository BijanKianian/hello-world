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
* @file memtest.h
* @brief This header file provides user interface interaction
* response via functions
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 23 2019
* @version 1.3
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Prototype list */

void help(void);
int inputCheck(void);
int* allocate(int);
void free_memory(int*);
void display(int*, int);
void write(int*, int, int);

/* End prototype list */
