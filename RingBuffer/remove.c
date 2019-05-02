#includde "ringBuffer.h"
/**--------------------------------------------------------------------- remov() -Start -----------------------------------------------------------**/

int8_t remov( ring_t *ring, char* data )
{
	//assert(ring);									// assert error if the ring is null (no buffer is initialized).
	if (ring == NULL)
		return -1;

	//assert(!(((next_output_index && ring->length-1) > ring->Ini)&&(next_Output_index >= ring->Length)))			// Buffer is empty.

	if(((ring->Outi & (ring->Length-1)) == ring->Ini) && (ring->Outi >= ring->Length))		// Buffer is empty
	{
		//ring->Outi = ring->Outi & (ring->Length-1);
		return -2;
	}

	*data = ring->Buffer[ring->Outi & (ring->Length-1)];
	ring->Outi = ring->Outi+1; // & (ring->Length-1);

	return 0;
}


/**-------------------------------------------------------------------- remov() - End -----------------------------------------------------------------**/