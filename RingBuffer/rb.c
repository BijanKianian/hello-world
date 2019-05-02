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


/***************************************** main() - Start ************************************/
int main()
{
    char First_Data_In[100];				    // Place holder for the first string data by user. (for insert() operation)
	char Second_Data_In[100];			    // Place holder for the second string data by user. (for insert() operation)
	char data_out[100];							// Place holder for out string from buffer. (for remov() operation)
	uint32_t length, removal;					// length of ring buffer and number of characters to ne removed defined by user.
	char temp;											// Used for flushing keyboard.
	/*******************************************************
	**		Asking user for buffer size and data	**
	********************************************************/

	printf("Please enter a string to be written into the ring buffer:  ");
	scanf("%[^\n]", First_Data_In);

    printf("You entered: %s\n\n", First_Data_In);

	do			// Loop for chacking power of two input for length of buffer
	{
		printf("Please enter the size of the ring buffer < in powers of 2 >: ");
		FLUSH
		scanf("%d", &length);

		if( Power_Of_Two (length) == 1)
			printf(" Length is not a power of 2 number, please try again!\n");
	}while(Power_Of_Two(length));

	printf("Please enter the number of data characters to be removed from Buffer: ");
	scanf("%d", &removal);

	printf("Please enter the second string of data to be written: ");
	FLUSH
	scanf("%[^\n]", Second_Data_In);

	printf("You entered: %s\n\n", Second_Data_In);

	/************************************
	 **  Testing insert() and remov()  **
	 ************************************/

	ring_t *sample = init(length);     						// Initialize RingBuffer and return a pointer (sample) pointing to RingBuffer.
	uint32_t count_1 = strlen(First_Data_In);
	uint32_t count_2 = strlen(Second_Data_In);

	insert_test(sample, count_1, First_Data_In);	          		    // pushing characters from input string First_Data_In[100], to the buffer.
	printf("Current Buffer contents: %s\n", RingBuffer.Buffer);	// Display the result on buffer contents.
	printf("Tail: %-5d	Head: %-5d	Entries: %-d\n\n", RingBuffer.Outi & (RingBuffer.Length-1), RingBuffer.Ini & (RingBuffer.Length-1), entries( sample));

	remov_test(sample, removal, data_out);
	printf("*** Data-out Buffer contents ***:%s\n", data_out);
	printf("Current Buffer contents: %s\n", RingBuffer.Buffer);
    printf("Tail: %-5d	Head: %-5d	Entries: %-d\n\n", RingBuffer.Outi & (RingBuffer.Length-1), RingBuffer.Ini & (RingBuffer.Length-1), entries( sample));

	insert_test(sample, count_2, Second_Data_In);			// Testing insert after removing data from buffer.
	printf("Current Buffer contents: %s\n", RingBuffer.Buffer);
	printf("Tail: %-5d	Head: %-5d	Entries: %-d\n\n", RingBuffer.Outi & (RingBuffer.Length-1), RingBuffer.Ini & (RingBuffer.Length-1), entries( sample));

	/*CU_ASSERT(*init( test_ring.Length  ) != NULL);

	CU_ASSERT(insert(*ring, 'H' ) != -1);
	CU_ASSERT(insert(*ring, 'H' ) != -2);

	CU_ASSERT(remove( *ring, *data ) != -1);
	CU_ASSERT(remove( *ring, *data ) != -2);*/
	free(array);
	return 0;
}
/******************************************* main() - End **************************************/

/**######################################### init() - Start ###################################*/

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

/**######################################### init() - End ######################################*/

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

/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ Power_Of_Two() $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/

/******************************************************************
  This is a check for 'length' value given by user,		*
  making sure it's a power of 2.									*
*******************************************************************/

uint8_t Power_Of_Two (uint32_t num)
{
	while (num !=1)
	{
		if(num%2 != 0)
			return 1;

		num = num / 2;
	}
	return 0;
}

/**======================================= insert_test() - Start ====================================**/

/************************************************************************
  This function is for testing insert().									*
  If the buffer is full or not initialized, it will alert the user	*
*************************************************************************/


void insert_test(ring_t *ring, uint32_t count, char* data)
{
	for (uint32_t i = 0; i <= count-1; i++)
	{
		int8_t check_insert = insert(ring, data[i]);
		switch (check_insert)
		{
			case 0:
				printf("Data= %c inserted at location %d\n", data[i], ((ring->Ini-1) & (ring->Length-1)));
				break;

			case -1:
				{
					printf("ERROR!... Buffer is not initialized!\n");
					i = count;
					break;
				}

			case -2:
				{
					printf("Buffer is full!\n");
					i = count;
					break;
				}
		}
	}
}

/**======================================= insert_test() - End ====================================**/

/**======================================= remov_test() - Start ====================================**/

/************************************************************************
  This function is for testing remov().									*
  If the buffer is empty or not initialized, it will alert the user	*
*************************************************************************/


void remov_test(ring_t *ring, uint32_t count, char* data)
{
	for (uint32_t i = 0; i <= count-1; i++)
	{
		int8_t check_remov = remov(ring, data+i);
		switch (check_remov)
		{
			case 0:
				printf("Data= %c removed from location %d\n", data[i], ((ring->Outi-1) & (ring->Length-1)));
				break;

			case -1:
				{
					printf("ERROR!... Buffer is not initialized!\n");
					i = count;
					break;
				}

			case -2:
				{
					printf("Buffer is empty!\n");
					i = count;
					break;
				}
		}
	}
}

/**======================================= remov_test() - End ====================================**/


