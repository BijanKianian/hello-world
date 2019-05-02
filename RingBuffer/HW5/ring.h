/*========================================================================
** ring.h
** Circular buffer testing
** ECEN5813
**========================================================================*/

#ifndef RING_H
#define RING_H

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define FLUSH 	fflush(stdin); scanf("%c", &temp);		// Flushing key board buffer


typedef struct
{
	char *Buffer;
	uint32_t Length;
	uint32_t Ini;
	uint32_t Outi;
} ring_t;

uint32_t length;				//Note:  arbitrary length, could be interactively defined.
uint32_t read_out;				   // Number of characters to be readeeeed using readeee() function
char data_in[50];		   // For insert test
//char data_in_2[50];	
char data_out[50];				// For read test
char temp;					// Used in FLUSH

//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}} Functions Prototype - Start {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{

ring_t *init( uint32_t  );
int8_t insert( ring_t *, char  );
int8_t read( ring_t *, char * );
int32_t entries( ring_t * );
uint8_t Power_Of_Two(uint32_t);

//}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}} Functions Prototype - End {{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{

#endif
