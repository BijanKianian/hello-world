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
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "allocate.h"
#include "display.h"
#include "free.h"
#include "help.h"
#include "invert.h"
#include "write.h"
#include "pattern.h"
#include "verify.h"
#include <time.h>


#define FRDM 0

 #if FRDM          /* Substitutions for platform */


#define LSB_WORD int32_t	/* Lower 32 bits of address are used to make immediate*/
							/*  addressing offset (a.k.a Block_Address_lo), passed to addressCheck(char*, int) */
#define ADDRESS_LENGTH 8	/* Parameter for address length (PC = 12, FRDM = 8)*/
#define SYSTICK_MAX 16000000		/* Maximum value for 24 bit Systick register*/


#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "core_cm0plus.h"

#else


#include <time.h>
#define LSB_WORD int64_t	/* int64_t is casting Block_Address*/
#define ADDRESS_LENGTH 12	/* 12 byte addressing for PC */

#endif


/* Prototype list */

int32_t inputCheck(void);
void pattern_Time(int32_t ,int32_t ,int32_t );
int32_t addressCheck(char*, int32_t);
int32_t valueCheck(char*);
int32_t offsetCheck(char*);
int32_t lengthCheck(char*, int32_t);
int32_t alloc_test(char*, char*, char*, char*, char*);
void invert_Time(int32_t, int32_t);
int32_t seedCheck(char*);

/* End prototype list */
