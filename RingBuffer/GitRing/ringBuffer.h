/*========================================================================
** ring_test.c
** Circular buffer testing
** ECEN5813
**========================================================================*/

//#include <CUnit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdint.h>

#define FLUSH 	fflush(stdin); scanf("%c", &temp);

//#ifndef RING.H
//#define RING.H

typedef struct
{
char *Buffer;
uint32_t Length;
uint32_t Ini;
uint32_t Outi;
} ring_t;

ring_t RingBuffer={"", 0, 0, 0};             //Global declaration of a buffer called RingBuffer.
char *array =NULL;

ring_t *init( uint32_t  );
int8_t insert( ring_t *, char  );
int8_t remov( ring_t *, char * );
int32_t entries( ring_t * );
uint8_t Power_Of_Two(uint32_t);
void insert_test(ring_t*, uint32_t, char*);
void remov_test(ring_t*, uint32_t, char*);
