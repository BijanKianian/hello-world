int alloc_test(char* str1, char* str2)
{
	
	 if(!Block_Address)
                    {
                        printf("Memory is not allocated yet!\n\n");
                        printf("PES_Prj1 >> ");
                        return 0;
                    }

                if (str1== 0 || str2 == 0)     /* No offset/value enterred*/
                    {
                        printf("Please enter a valid starting offset and number of words, or <help> for details\n");
                        printf("PES_Prj1 >> ");
                        return 0;
                    }
		
	return 1;
}
