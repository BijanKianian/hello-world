int immediate_addressing(char* str1, char* str2)
{
	int Block_Address_lo;             /* lower 32 bit portion of Block_Address, used in immediate addressing to claculate address offset from start of block*/
	int memoryAddress;                /* Starting address for immediate addressing < -i >  in write() and read()*/
	
	int validInput = strcspn(str1, "ghijklmnopqrstuvwxyz.GHIJKLMNOPQRSTUVWXYZ,][{}`+-*/"); /* Validating start address for correct hex number*/

						if((validInput < strlen(str1) || (validInput> 16)))
							{
								printf("Please enter a valid 64bit hex number for the memory address\n");
								printf("PES_Prj1 >> ");
								return 0;
							}

						memoryAddress = strtol(str1, NULL, 16); /* Converting input address string to hex,*/

						Block_Address_lo =  (int64_t)Block_Address; /* Seperating the lower 32 bits of block address
																	to compare with user input address at Token[2] */

						/* Validating the starting address being in the range of allocated block */

						if (memoryAddress- Block_Address_lo > 4*(memoryOffsetValue-1))	/* 4 bytes distance between two immediate memory addresses*/
							{
								printf("Please enter the starting memory address between %p and %p\n", Block_Address, Block_Address + memoryOffsetValue-1);
								printf("PES_Prj1 >> ");
								return 0;
							}


						int* Start = Block_Address + (memoryAddress - Block_Address_lo)/4;
						int length = atoi (str2);
						display (Start, length);
			return 1;
}