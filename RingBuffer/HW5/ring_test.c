/*========================================================================
** ring_test.c
** Circular buffer testing program: init(), insert(), read(), entries();
** ECEN5813
**========================================================================*/
#include "ring.h"
/*========================================================================*/

ring_t RingBuffer;               //Global declaration of a buffer and it's pointer called RingBuffer/sample respectively.
ring_t *sample =&RingBuffer;
char *array = NULL;


//(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((( init_suite_1() - Start )))))))))))))))))))))))))))))))))))))))))))))))))

int init_suite_1(void)
 {

		printf("Please enter a string to be written into the ring buffer:  ");
		//FLUSH
		scanf("%[^\n]", data_in);

		printf("You entered: %s\n\n", data_in);
		do			// Loop for chacking power of two input for length of buffer
			{
				printf("Please enter the size of the ring buffer < in powers of 2 >: ");
				FLUSH
				scanf("%d", &length);

				if( Power_Of_Two (length) == 1)
					printf(" Length is not a power of 2 number, please try again!\n");

			} while(Power_Of_Two(length));

		printf("Please enter the number of data characters to be removed from Buffer: ");
	    FLUSH
		scanf("%d", &read_out);

	//sample = init(length);			// Initializing buffer with values entered by user and/or program
	array = malloc(sizeof(char));
	// sample->Length = length; 	       // initialize sample. It is declared in ring.h
	// sample->Buffer = array;
	// sample->Ini = 0;                      // head = 0.
	// sample->Outi = 0;                   // tail = 0.
	sample = init(length);     	// Initialize RingBuffer and return a pointer (sample) pointing to RingBuffer.

	return 0;
  }
//(((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((((( init_suite_1() - End )))))))))))))))))))))))))))))))))))))))))))))))))

//################################## clean_suite_1() - Start #################################

int clean_suite_1(void)

{
	free(array);		// array is globally declared in header and initialized in init(); array = malloc(sizeof(char));
	return 0;
}

//################################## clean_suite_1() - End #################################

//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{ test_init_1() - Start }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

void test_init_1(void)		// initializing test; init()
{
	//ring_t *sample = init(length);     						// Initialize RingBuffer and return a pointer (sample) pointing to RingBuffer.
	CU_ASSERT(NULL != init(length));
}

//{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{{ test_init_1() - End }}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}}

// %%%%%%%%%%%%%%%%%%%%% test_insert_1() - Start %%%%%%%%%%%%%%%%%%%%

void test_insert_1(void)		// Insert test insert()
{

	CU_ASSERT(-1 == insert(NULL, data_in[0]));		// Error checking for NULL pointer
	uint32_t count = strlen(data_in);

	for(uint16_t i = 0; i <= count-1; i++)
	{
		uint32_t check_insert = insert(sample, data_in[i]);
		CU_ASSERT(0 == check_insert);									//PASS
		if (check_insert == -2)														//Buffer Full	
		{
			printf("Expected buffer overflow at location: %d...\n", sample->Ini & (sample->Length-1));					
			break;
		}
	}
	printf("Current Buffer contents: %s...\n", sample->Buffer);		
	printf("Tail: %-5d	Head: %-5d	Entries: %-d...", sample->Outi & (sample->Length-1), sample->Ini & (sample->Length-1), entries( sample));
	CU_ASSERT( 0 == strncmp( sample->Buffer , data_in, strlen(sample->Buffer )));		// This line checks if the buffer space is loaded with-																																						//-	correct number of characters from data_in
}
// %%%%%%%%%%%%%%%%%%%%% test_insert_1() - End %%%%%%%%%%%%%%%%%%%%


/*************************************************** test_read_1() - Start ************************************************************/

void test_read_1(void)
{

	CU_ASSERT(-1 == read(NULL, data_out));		// Error checking for NULL pointer

	if (read_out != 0 )
	{
		for (uint16_t i = 0; i<=read_out-1; i++)
		{
			uint32_t check_read = read(sample, data_out+i);
			CU_ASSERT(0 == check_read);			//PASS
			if(check_read == -2)
			{
				printf("Expected buffer empty at location: %d...", sample->Outi & (sample->Length-1));
				break;
			}
		}	
		printf("<<Data-out Buffer contents >>: %s...\n", data_out);
		printf("Current Buffer contents: %s...\n", sample->Buffer);
		printf("Tail: %-5d	Head: %-5d	Entries: %-d\n\n", sample->Outi & (sample->Length - 1), sample->Ini & (sample->Length-1), entries( sample));	
	}
}
/***************************************************************** test_read_1() - End ************************************************/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ test_entries_1() - Start ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void test_entries_1(void)																//entries test; entries()
{
	CU_ASSERT(-1 == entries(NULL));
	CU_ASSERT(-1 != entries(sample));
	printf("Tail: %-5d	Head: %-5d	Entries: %-d\n\n", sample->Outi & (sample->Length-1), sample->Ini & (sample->Length-1), entries( sample));

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ test_entries_1() - End ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


// ########################################### main() - Start #######################################

int main (void)
{
	char cnt = 'c';

	while(cnt == 'c')
	{
		CU_pSuite pSuite1 = NULL;

		// Initialize CUnit test registry

		if (CUE_SUCCESS != CU_initialize_registry())
			return CU_get_error();

		// Add suite1 to registry

		pSuite1 = CU_add_suite("Basic_Test_Suite1\n", init_suite_1, clean_suite_1);
		if (NULL == pSuite1)
		{
			CU_cleanup_registry();
			return CU_get_error();
		}

		 // add test1 to suite1

		if (((NULL == CU_add_test(pSuite1,  " Testing init() function: ", test_init_1))) ||
			  (NULL == CU_add_test(pSuite1,  " Testing insert() function: ", test_insert_1)) ||
			  (NULL == CU_add_test(pSuite1,  " Testing read() function: ", test_read_1)) ||
			  (NULL == CU_add_test(pSuite1,  " Testing entries() function: ", test_entries_1)))

		{
			CU_cleanup_registry();
			return CU_get_error();
		}

		CU_basic_set_mode(CU_BRM_VERBOSE);
		CU_basic_run_tests();									// OUTPUT to the screen
		printf("Please enter (c) for continue, (q) for exit ");
		FLUSH
		scanf("%c", &cnt);
		scanf("%c", &temp);
	}
	CU_cleanup_registry();								// Cleaning the Registry
	return CU_get_error();
}

//########################################## main() - End #######################################
