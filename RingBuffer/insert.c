#includde "ringBuffer.h"
/****************************************** insert() -Start *****************************************/

int8_t insert( ring_t *ring, char data )
{
	//assert(ring);								    // assert error if the ring is null (no buffer is initialized).

	if (ring == NULL)
		return -1;

	//assert(!(((next_input_index && ring->length-1) > ring->Outi)&&(next_input_index >= ring->Length)));	// assert error if head is more than length.(Buffer is ful).

		/* *******************************************************************************************************************
		 * The head index which is [ring->Ini & (ring->Length-1)] will remain always between				*
		 * 0 and [Length - 1]. If it passes or equals the tail index (Outi) while the head pointer is			*
	     *  euqual or above 'Length',	it means that the pointer has traveled a full circle which implies	*
		 * "Buffer Full". Then the amount of 'Length'	has to be subtracted from the head pointer to	*
		 * keep it between 0 and length again 																								*
		 *********************************************************************************************************************/
	if(((ring->Ini & (ring->Length-1)) == ring->Outi) && (ring->Ini >= ring->Length))
	{
		//ring->Ini = ring->Ini & (ring->Length-1);		// Subtracting the 'Length' value from the head pointer after 'Buffer Full" situation.(see the comment above)
		return -2;
	}

	ring->Buffer[ring->Ini & (ring->Length-1)] = data;
	ring->Ini = ring->Ini + 1; //& (ring->Length-1);

	return 0;
}

/*************************************************************** insert()- End ******************************************************/