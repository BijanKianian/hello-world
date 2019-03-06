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
* @date February 24 2019
* @version 1.3
*
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "allocate.h"
#include "display.h"
#include "free.h"
#include "help.h"
#include "invert.h"
#include "write.h"
#include "pattern.h"
#include "verify.h"

/* Prototype list */

int inputCheck(void);
void pattern_Time(int ,int ,int );
int addressCheck(char*, int);
int valueCheck(char*);
int offsetCheck(char*);
int lengthCheck(char*, int);
int alloc_test(char*, char*, char*);
void invert_Time(int, int);
int seedCheck(char*);


/* End prototype list */
