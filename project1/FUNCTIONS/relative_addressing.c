
int relativeAddressing(char* str1, char* str2)
{
	int startOffset = atoi (str1);        /* Starting memory location offset from Block_Address*/
	int numberOfwords = atoi ( str2);       /* Number of locations (words) to display */

					/* Condtion check for valid offset between 0 to block size (memoryOffsetValue) */

						if((startOffset < 0 ) || (startOffset > (memoryOffsetValue-1)))
							{
								printf("Please enter valid offset between 0 to %d\n", memoryOffsetValue-1);
								printf("PES_Prj1 >> ");
								return 0;
							}


						if(numberOfwords > (memoryOffsetValue - startOffset))
							{
								printf("Please enter valid number of words between 1 to %d\n", \
								memoryOffsetValue-startOffset);
								printf("PES_Prj1 >> ");
								return 0;
							}

						display(Block_Address+startOffset, numberOfwords);
				return 1;		
}