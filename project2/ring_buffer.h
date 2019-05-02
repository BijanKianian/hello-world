/*========================================================================
** ring_buffer.h
** Circular buffer header
** ECEN5813
**========================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdint.h>

#define FLUSH 	fflush(stdin); scanf("%c", &temp);

typedef struct
{
char *Buffer;
uint32_t Length;
uint32_t Ini;
uint32_t Outi;
} ring_t;

ring_t RingBuffer; //{"", 0, 0, 0};             //Global declaration of a buffer called RingBuffer.

uint8_t Buffer_Full, Buffer_Empty;					// A flag to indicate the buffer state. 0 == empty. 1 == full

ring_t *init ( uint32_t  );
int8_t insert ( ring_t *, char  );
int8_t read ( ring_t *, char * );
int32_t entries ( ring_t * );
uint8_t Power_Of_Two (uint32_t);
void insert_test (ring_t*, uint32_t, char*);
void read_test (ring_t*, uint32_t, char*);
