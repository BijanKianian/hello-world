#include "ringBuffer.h"
/**######################################## entries () - Start ####################################**/
int32_t entries( ring_t *ring )
{
	uint32_t Elements, ini, outi, length;

	ini = ring->Ini;
	outi = ring->Outi;
	length = ring->Length;

	if(ini >= length)
		Elements = length;
	if(ini >= outi)
		Elements = ini - outi;
	else
		Elements = length - outi + ini;	/** If Head is larger or equal to Tail, the
												 ** number of elements are Head - Tail, otherwise
												 ** it's the buffer size minus Tail plus Head **/

	return Elements;
}
/**######################################## entries() - End #######################################**/
