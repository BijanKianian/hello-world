/**######################################### init() - Start ###################################*/
#include "ringBuffer.h"
ring_t *init( uint32_t length )
{
	array = malloc(sizeof(char));
	if (length == 0)
	{
		printf("ERROR!... Buffer length cannot be 0.");
		return NULL;
	}
    ring_t *p_Ring;
    p_Ring = &RingBuffer;
	p_Ring->Length = length; 	       // initialize the length of the buffer.
	p_Ring->Buffer = array;
	p_Ring->Ini = 0;                    // head = 0.
	p_Ring->Outi = 0;                   // tail = 0.

	return p_Ring;			// returns the pointer which is pointing to the buffer (a.k.a ring).
}
