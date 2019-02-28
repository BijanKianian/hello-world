/*****************************************************************************
* Copyright (C) 2019 by Ismail Yesildirek & Bijan Kianian
*
* Redistribution, modification or use of this software in source or binary
* forms is permitted as long as the files maintain this copyright. Users are
* permitted to modify this and use it to learn about the field of embedded
* software. Ismail Yesildirek, Bijan Kianian, and the University of Colorado are not
* liable for any misuse of this material.
*
*****************************************************************************/
/**
* @file memtest.c
* @brief This source file contains a c program to manipulate and test memory.
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 24 2019
* @version 1.4
*
*/

#include "memtest.h"
#include <stdint.h>

int memoryOffsetValue  = 0;        /* Offset value for the memory block to be allocated*/
int* Block_Address = NULL;            /* Place holder for block address*/
int allocStatus = 0;	/* Malloc Flag */

int main()
{
	printf("This is a simple program for testing memory.\n");
	printf("Type 'help' for more details or 'exit' to leave the program: \n");
    printf("PES_Prj1 >> ");
	int validStatus = 0;

    while(validStatus == 0)
       {
          validStatus = inputCheck();
       }

    return 0;
}
/*########################################## inputCheck() Start #######################################################*/
int inputCheck(void)
{
    char *cmds[] = { "help", "exit", "allocate", "free", "read", "write", "invert", "pattern"};         /* Constant strings to be compared with user input commands */
    char *Token[10] = {};               /* Array of strings for saving tokens in command line after parsing user input line*/
    char userInput[50] = {}, temp;      /* Array to store input command line string */
    int memoryValue;                    /* Value to be written at memory locaion defined by write()*/
    int memoryAddress;                /* Starting address for immediate addressing < -i >  in write() and read()*/
	int Block_Address_lo;             /* lower 32 bit portion of Block_Address, used in immediate addressing to claculate address offset from start of block*/

    int startOffset = 0;
    //int seed = 0;
    int numberOfwords;					       /* Used in Pattern()*/
    int location =0;                         /* Memory location offset from start of the block */
    int compareResult;
	char allocInput[6]; /*For re-alloc question*/
        /***** Parsing variables ******/
     char *pToken;                 /* Token pointer to be used in parsing command line input string*/
     int tokenCount;               /* Counter used in parsing procedure*/
     char **str[10];               /* Array of strings pointed to by the token*/
        /*******************************/

     fflush(stdin);                 /* Flushing keyboard buffer from previous input*/
     strcpy(userInput," ");         /* Reseting userInput string array*/
	 strcpy(allocInput," ");         /* Reseting allocInput string array*/
     scanf("%[^\n]", userInput);	/* Accepting user Input*/
     scanf("%c", &temp);            /* Flushing '\n' character from the stdin buffer after user hit the 'Enter' */
     compareResult = strcmp(userInput,"");
     while(compareResult == 32)      /* Validating user input, No input = 'SPACE' (i.e decimal value 32)*/
      {
        int value = 0;
        printf("Please enter a valid command, or <help> for details\n\n");
        printf("PES_Prj1 >> ");
        return value;
      }


/**************************************** Parsing Start *************************************************/
    tokenCount = 0;
    pToken = strtok (userInput," ");

	/*Check for an user input*/
	while (!pToken)
	{
		printf("Invalid Input. Please try again: \n");
		printf("PES_Prj1 >> ");
		fflush(stdin);
		scanf("%[^\n]s", userInput);	/* Accepting user Input*/
		scanf("%c", &temp);		/* Flushing '\n' character from the stdin buffer */
		pToken = strtok(userInput, " ");
	}

    str[0] = &pToken;
	     while (pToken)
	       {
             Token[tokenCount] = *str[tokenCount];    /* Saving the parsed texts into *str[] array*/
             pToken = strtok (NULL, " ");

             tokenCount++;
             str[tokenCount] = &pToken;
	       }
/****************************************** Parsing End **************************************************/

	int valid = 0;
		if (strcmp(Token[0], cmds[0]) == 0)             /*     help()     */
			{
				valid = 0;
				help();
				printf("PES_Prj1 >> ");
			}
		else if (strcmp(Token[0], cmds[1]) == 0)      /*     exit()      */
			{
				valid = 1;
				printf("\nGood Bye!\n\n");
			}

		else if (strcmp(Token[0], cmds[2]) == 0)        /*   allocate()  */
			{
			   valid = 0;

		        if (Token[1] == 0 || atoi(Token[1]) == 0 || Token[2] != 0)             /* Error if no offset or more than 1 argument enterred*/
                    {
                        printf("Please enter not more than a valid non-zero offset value w/o any extra, or <help> for details\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }

                if (allocStatus == 0)
                    {
                        memoryOffsetValue = atoi(Token[1]);
                        Block_Address = (int*)allocate(memoryOffsetValue);
                        if (Block_Address)
                            {
                                printf("\nMemory block allocated.\n");
                                printf("Address: %p    size: %d   (%ld Bytes)\n", Block_Address, \
                                    memoryOffsetValue, sizeof(int) * memoryOffsetValue);
                                allocStatus = 1;
                                /*One memory allocation performed*/
                                printf("Enter another command \n\n");
                                printf("PES_Prj1 >> ");
                            }
                    }
                else
                    {
                        printf("\nMemory is current allocated in address 0x%p\n", Block_Address);
                        printf("\nDo you wish to override this data? (Y?) \n");
                        printf("PES_Prj1 >> ");
                        fflush(stdin);
                        scanf("%[^\n]s", allocInput);	/* Accepting override Input*/
                        scanf("%c", &temp);		/* Flushing '\n' character from the stdin buffer */
                        //printf("\nYour answer is: %s \n", allocInput);
                            if (strcmp(allocInput, "yes") == 0 || strcmp(allocInput, "YES") == 0 || strcmp(allocInput, "y") == 0 || strcmp(allocInput, "Y") == 0)
                                {
                                    free_memory(Block_Address);
                                    printf(" %ld Bytes of heap released from address %p to %p\n", \
                                    sizeof(int) * memoryOffsetValue, Block_Address, Block_Address + memoryOffsetValue);
                                    allocStatus = 0;
                                    /*system ready to allocate memory again*/
                                    memoryOffsetValue = atoi(Token[1]);

                                    Block_Address = (int*)allocate(memoryOffsetValue);
                                    if (Block_Address)
                                        {
                                            printf("\nMemory block allocated.\n");
                                            printf("Address: %p    size: %d   (%ld Bytes)\n", Block_Address, \
                                            memoryOffsetValue, sizeof(int) * memoryOffsetValue);
                                            allocStatus = 1;
                                            /*One memory allocation performed*/
                                            printf("Enter another command \n\n");
                                            printf("PES_Prj1 >> ");
                                        }
                                }
                            else
                                {
                                    printf("\nMemory allocated remains in address 0x%p\n", Block_Address);
                                    printf("Enter another command \n\n");
                                    printf("PES_Prj1 >> ");
                                }

                    }
			}
		else if (strcmp(Token[0], cmds[3]) == 0)        /*    free()     */
			{
				valid = 0;

				if(!Block_Address)
                    {
                        printf("Memory is not allocated yet!\n");
                        printf("Enter another command \n\n");
                        printf("PES_Prj1 >> ");
                    }
				else
					{
						free_memory(Block_Address);
						printf(" %ld Bytes of heap released from address %p to %p\n\n", \
					           sizeof(int) * memoryOffsetValue,Block_Address, Block_Address + memoryOffsetValue-1);
                        Block_Address = NULL;
						allocStatus = 0;
						/*system ready to allocate memory again*/
						printf("Enter another command \n\n");
						printf("PES_Prj1 >> ");
					}
			}


		else if (strcmp(Token[0], cmds[4]) == 0)        /*    display()   */
		    {
               valid = 0;

                if(!Block_Address)
                    {
                        printf("Memory is not allocated yet!\n\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }

                if (Token[1] == 0 || Token[2] == 0)     /* No offset/value enterred*/
                    {
                        printf("Please enter a valid starting offset and number of words, or <help> for details\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }


									/**  Token[1] != "-i" with relative addressing in which case Token[1] = <offset>, Token[2] = <value>,Token[3] == 0.
									  Token[1] == "-i" with immediate addressing < -i > hence Token[1] = <-i>, Token[2] = <address>, Token[3] = <value>.**/

				if(strcmp(Token[1] , "-i")) /* Relative addressing <offset> < length>*/
					{

						   int startOffset = atoi (Token[1]);        /* Starting memory location offset from Block_Address*/

					/* Condtion check for valid offset between 0 to block size (memoryOffsetValue) */

						if((startOffset < 0 ) || (startOffset > (memoryOffsetValue-1)))
							{
								printf("Please enter valid offset between 0 to %d\n", memoryOffsetValue-1);
								printf("PES_Prj1 >> ");
								return valid;
							}


						int numberOfwords = atoi ( Token[2]);       /* Number of locations (words) to display */

						if(numberOfwords > (memoryOffsetValue - startOffset))
							{
								printf("Please enter valid number of words between 1 to %d\n", \
								memoryOffsetValue-startOffset);
								printf("PES_Prj1 >> ");
								return valid;
							}

						display(Block_Address+startOffset, numberOfwords);
				    }

			/** Immediate addressing **/

	            if(!strcmp(Token[1] , "-i"))    /* immediate addressing : write < -i > < address(hex) > < value(hex) > */
                    {

						int validInput = strcspn(Token[2], "ghijklmnopqrstuvwxyz.GHIJKLMNOPQRSTUVWXYZ,][{}`+-*/"); /* Validating start address for correct hex number*/

						if((validInput < strlen(Token[2]) ||(validInput> 16)))
							{
								printf("Please enter a valid 64bit hex number for the memory address\n");
								printf("PES_Prj1 >> ");
								return valid;
							}

						memoryAddress = strtol(Token[2], NULL, 16); /* Converting input address string to hex,*/

						Block_Address_lo =  (int64_t)Block_Address; /* Seperating the lower 32 bits of block address
																	to compare with user input address at Token[2] */

						/* Validating the starting address being in the range of allocated block */

						if (memoryAddress- Block_Address_lo > 4*(memoryOffsetValue-1))	/* 4 bytes distance between two immediate memory addresses*/
							{
								printf("Please enter the starting memory address between %p and %p\n", Block_Address, Block_Address + memoryOffsetValue-1);
								printf("PES_Prj1 >> ");
								return valid;
							}


						int* Start = Block_Address + (memoryAddress - Block_Address_lo)/4;
						int length = atoi (Token[3]);
						display (Start, length);
					}

			}

		else if (strcmp(Token[0], cmds[5]) == 0)        /*    write()     */
		    {
                valid = 0;

                if(!Block_Address)
                    {
                        printf("Memory is not allocated yet!\n\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }
                /* Condition to check if user entered correct number of arguments for <offset> , < value>*/

                if (Token[1] == 0 || Token[2] == 0)     /* No offset/value enterred*/
                    {
                        printf("Please enter a valid memory location and value, or <help> for details\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }


                        /**  Token[1] != "-i" with relative addressing in which case Token[1] = <offset>, Token[2] = <value>,Token[3] == 0.
                              Token[1] == "-i" with immediate addressing < -i > hence Token[1] = <-i>, Token[2] = <address>, Token[3] = <value>.**/

                        if(strcmp(Token[1] , "-i")) /* Relative addressing <offset> < value>*/
                            {
                                int validInput = strcspn(Token[2], "ghijklmnopqrstuvwxyz.GHIJKLMNOPQRSTUVWXYZ,][{}`+-*/"); /* Validating correct hex number*/

                                if(validInput < strlen(Token[2]) ||(validInput > 8))
                                    {
                                        printf("Please enter a valid 32bit hex number for the value\n");
                                        printf("PES_Prj1 >> ");
                                        return valid;
                                    }

                                memoryValue = strtol(Token[2], NULL, 16); /* Converting string to hex */
                                location = atoi (Token[1]);         /* *(address + location) = place to write the value*/

                                /* A condition to check the correct offset between 0 and maximum offset given to allocate() */

                                if ((location > memoryOffsetValue-1) || (location < 0))
                                    {
                                        printf("Please enter a memory location between 0 and %d\n", memoryOffsetValue-1);
                                        printf("PES_Prj1 >> ");
                                        return valid;
                                    }

                                write(Block_Address, location, memoryValue);

                            }

                        if(!strcmp(Token[1] , "-i"))    /* immediate addressing : write < -i > < address(hex) > < value(hex) > */
                            {

                                int validInput = strcspn(Token[2], "ghijklmnopqrstuvwxyz.GHIJKLMNOPQRSTUVWXYZ,][{}`+-*/"); /* Validating correct hex number*/

                                if(validInput < strlen(Token[2]) ||(validInput > 16))
                                    {
                                        printf("Please enter a valid 64bit hex number for the memory address\n");
                                        printf("PES_Prj1 >> ");
                                        return valid;
                                    }

                                memoryAddress = strtol(Token[2], NULL, 16); /* Converting input address string to hex,
                                                                               produces an int equal to LSB 32 bits */
                                Block_Address_lo =  (int64_t)Block_Address; /* Seperating the lower 32 bits of block address
                                                                            to compare with user input address at Token[2] */

                                /* A condition to check the correct offset value between 0 and maximum offset derived by allocate() */

                                if (memoryAddress - Block_Address_lo > 4*(memoryOffsetValue-1))
                                    {
                                        printf("Please enter a memory address between %p and %p\n", Block_Address, Block_Address + memoryOffsetValue-1);
                                        printf("PES_Prj1 >> ");
                                        return valid;
                                    }
                /** Validating the 32 bit hex value to be written at address **/

                                validInput = strcspn(Token[3], "ghijklmnopqrstuvwxyz.GHIJKLMNOPQRSTUVWXYZ,][{}`+-*/"); /* Validating correct hex number*/

                                if(validInput < strlen(Token[3]) ||(validInput > 8))
                                    {
                                        printf("Please enter a valid 32bit hex number for the value\n");
                                        printf("PES_Prj1 >> ");
                                        return valid;
                                    }

                                memoryValue = strtol(Token[3], NULL, 16); /* Converting string to hex */

                                location = 0;   /* offset = 0 for immediate addressing */
                                write(Block_Address + (memoryAddress - Block_Address_lo)/4, location, memoryValue);
                            }

            }
		else if (strcmp(Token[0], cmds[6]) == 0)        /*    invert()    */
            {
            valid = 0;
                if (!Block_Address)
                    {
                        printf("Memory is not allocated yet!\n\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }
     /* Condition to check if user entered correct number of arguments for <offset> , < value>*/

                if (Token[1] == 0 || Token[2] == 0)     /* No offset/value enterred*/
                    {
                        printf("Please enter a valid starting offset and number of words, or <help> for details\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }
				if(strcmp(Token[1] , "-i")) /* Relative addressing <offset> < value>*/
                     {
						int startOffset = atoi(Token[1]);        /* Starting memory location offset from Block_Address*/

				/* Condtion check for valid offset between 0 to block size (memoryOffsetValue) */

						if ((startOffset < 0) || (startOffset > (memoryOffsetValue - 1)))
							{
								printf("Please enter valid offset between 0 to %d\n", memoryOffsetValue - 1);
								printf("PES_Prj1 >> ");
								return valid;
							}

					int numberOfwords = atoi(Token[2]);

					if(numberOfwords > (memoryOffsetValue - startOffset))
						{
							printf("Please enter valid number of words between 1 to %d\n", \
							memoryOffsetValue-startOffset);
							printf("PES_Prj1 >> ");
							return valid;
						}
                        int wordSize = numberOfwords;
                        /**
                        * Invert Byte Block per wordSize selected
                        * and start timer.
                        **/
                        clock_t executionT;
                        executionT = clock();
                        while ((numberOfwords <= wordSize) && (numberOfwords >=0))
                            {
                                invert(Block_Address+startOffset, numberOfwords-1);
                                numberOfwords--;
                            }
                        executionT = clock() - executionT;
                        double time = ((double)executionT)/CLOCKS_PER_SEC;
                        printf("Invert function execution time is milli: %fsec.\n",time*1000);
                        printf("Enter another command \n\n");
                        printf("PES_Prj1 >> ");


					 }

				  if(!strcmp(Token[1] , "-i"))    /* immediate addressing : write < -i > < address(hex) > < value(hex) > */
					{

						int validInput = strcspn(Token[2], "ghijklmnopqrstuvwxyz.GHIJKLMNOPQRSTUVWXYZ,][{}`+-*/"); /* Validating correct hex number*/

						if(validInput < strlen(Token[2]) ||(validInput > 16))
							{
								printf("Please enter a valid 64bit hex number for the memory address\n");
								printf("PES_Prj1 >> ");
								return valid;
							}

						memoryAddress = strtol(Token[2], NULL, 16); /* Converting input address string to hex,
																	   produces an int equal to LSB 32 bits */
						Block_Address_lo =  (int64_t)Block_Address; /* Seperating the lower 32 bits of block address
																	to compare with user input address at Token[2] */

						int startOffset = (memoryAddress - Block_Address_lo)/4;

						/* A condition to check the correct offset value between 0 and maximum offset derived by allocate() */

						if (memoryAddress - Block_Address_lo > 4*(memoryOffsetValue-1))	/* 4 bytes distance between two immediate memory addresses*/
							{
								printf("Please enter a memory address between %p and %p\n", Block_Address, Block_Address + memoryOffsetValue-1);
								printf("PES_Prj1 >> ");
								return valid;
							}

						int numberOfwords = atoi(Token[3]);



						/* Number of locations (words) to display */
						if (numberOfwords > (memoryOffsetValue - startOffset))
							{
								printf("Please enter valid number of words between 1 to %d\n", \
									memoryOffsetValue - startOffset);
								printf("PES_Prj1 >> ");
								return valid;
							}
                        int wordSize = numberOfwords;
                        /**
                        * Invert Byte Block per wordSize selected
                        * and start timer.
                        **/
                        clock_t executionT;
                        executionT = clock();
                        while ((numberOfwords <= wordSize) && (numberOfwords >=0))
                            {
                                invert(Block_Address+startOffset, numberOfwords-1);
                                numberOfwords--;
                            }
                        executionT = clock() - executionT;
                        double time = ((double)executionT)/CLOCKS_PER_SEC;
                        printf("Invert function execution time is milli: %fsec.\n",time*1000);
                        printf("Enter another command \n\n");
                        printf("PES_Prj1 >> ");
                    }

            }
        else if (strcmp(Token[0], cmds[7]) == 0)        /*    pattern()    */
            {
				valid = 0;
                if(!Block_Address)
                    {
                        printf("Memory is not allocated yet!\n\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }

                if (Token[1] == 0 || Token[2] == 0 || Token[3] == 0)     /* No offset/value enterred*/
                    {
                        printf("Please enter a valid starting offset, number of words and seed, or <help> for details\n");
                        printf("PES_Prj1 >> ");
                        return valid;
                    }

				if(strcmp(Token[1] , "-i")) /* Relative addressing <offset> < value>*/
                     {
						int startOffset = atoi (Token[1]);        /* Starting memory location offset from Block_Address*/

				/* Condtion check for valid offset between 0 to block size (memoryOffsetValue) */

						if((startOffset < 0 ) || (startOffset > (memoryOffsetValue-1)))
							{
								printf("Please enter valid offset between 0 to %d\n", memoryOffsetValue-1);
								printf("PES_Prj1 >> ");
								return valid;
							}

						int numberOfwords = atoi ( Token[2]);       /* Number of locations (words) to write the random # */

						if(numberOfwords > (memoryOffsetValue - startOffset))
							{
								printf("Please enter valid number of words between 1 to %d\n", \
								memoryOffsetValue-startOffset);
								printf("PES_Prj1 >> ");
								return valid;
							}

					  if (Token[3] != 0)
						{
							int validInput = strcspn(Token[3],\
							 "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,][{}`/+-*"); /* Validating correct int number for Seed*/

							if(validInput < strlen(Token[3]) ||(validInput > 10)) /* Check if the number(seed) in larger than 10 digits
																					 (as in max 32 bit interger = 4,294,967,295)*/
								{
									printf("Please enter a valid positive number for the 'Seed' value\n");
									printf("PES_Prj1 >> ");
									return valid;
								}

							int Seed = atoi (Token[3]);        /* Converting string to number */
							pattern_Time( startOffset, numberOfwords,Seed );
						 }
					 }

			  if(!strcmp(Token[1] , "-i"))    /* immediate addressing : write < -i > < address(hex) > < value(hex) > */
				{

					int validInput = strcspn(Token[2], "ghijklmnopqrstuvwxyz.GHIJKLMNOPQRSTUVWXYZ,][{}`+-*/"); /* Validating correct hex number*/

					if(validInput < strlen(Token[2]) ||(validInput > 16))
						{
							printf("Please enter a valid 64bit hex number for the memory address\n");
							printf("PES_Prj1 >> ");
							return valid;
						}

					memoryAddress = strtol(Token[2], NULL, 16); /* Converting input address string to hex,
																   produces an int equal to LSB 32 bits */
					Block_Address_lo =  (int64_t)Block_Address; /* Seperating the lower 32 bits of block address
																to compare with user input address at Token[2] */

					 startOffset = (memoryAddress - Block_Address_lo)/4;

					/* A condition to check the correct offset value between 0 and maximum offset derived by allocate() */

					if (memoryAddress - Block_Address_lo > 4*(memoryOffsetValue-1))	/* 4 bytes distance between two immediate memory addresses*/
						{
							printf("Please enter a memory address between %p and %p\n", Block_Address, Block_Address + memoryOffsetValue-1);
							printf("PES_Prj1 >> ");
							return valid;
						}

					 numberOfwords = atoi(Token[3]);

				  if (Token[4] != 0)
						{
							int validInput = strcspn(Token[4],\
							 "abcdefghijklmnopqrstuvwxyz.ABCDEFGHIJKLMNOPQRSTUVWXYZ,][{}`/+-*"); /* Validating correct int number for Seed*/

							if(validInput < strlen(Token[4]) ||(validInput > 10)) /* Check if the number(seed) in larger than 10 digits
																					 (as in max 32 bit interger = 4,294,967,295)*/
								{
									printf("Please enter a valid positive number for the 'Seed' value\n");
									printf("PES_Prj1 >> ");
									return valid;
								}

							int Seed = atoi (Token[4]);        /* Converting string to number */
							pattern_Time( startOffset,  numberOfwords, Seed );
						 }
				}

            }
		else
		    {
		        valid = 0;
                printf("Invalid input, please try again: \n");
                printf("PES_Prj1 >> ");
		    }

	return valid;
}
 /*###################################### inputCheck () End ###############################################*/

 /**                                   { Functions Decfinision }                                          **/

 /************************************** pattern_Time() [Start]*********************************************/

	void pattern_Time(int StartOffset, int NumberOfwords,int Seed)
	{
               /**
                * Invert Byte Block per wordSize selected
                * and start timer.
                **/
                clock_t executionT;
                executionT = clock();

                pattern(Block_Address + StartOffset, NumberOfwords, Seed);

                executionT = clock() - executionT;
                double time = ((double)executionT)/CLOCKS_PER_SEC;

                printf("Pattern function execution time is milli: %fsec.\n",time*1000);
                printf("Enter another command \n\n");
                printf("PES_Prj1 >> ");
				return;
	}
/************************************** pattern_Time() [End]************************************************/
