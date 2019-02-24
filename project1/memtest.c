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
* @date February 21 2019
* @version 1.2
*
*/

#include "memtest.h"

    int memoryOffsetValue  = 0;        /* Offset value for the memory block to be allocated*/
    int* Block_Address = NULL;            /* Place holder for block address*/

int main()
{
	printf("This is a simple program for testing memory.\n");
	printf("Type 'help' for more details or 'exit' to leave the program: \n");

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
    char *cmds[] = { "help", "exit", "allocate", "free", "display", "write"};         /* Constant strings to be compared with user input commands */
    char *Token[10] = {};               /* Array of strings for saving tokens in command line after parsing user input line*/
    char userInput[50] = {}, temp;      /* Array to store input command line string */
    int memoryValue;                    /* Value to be written at memory locaion defined by write()*/
    int location =0;                       /* Memory location offset from start of the block */
    int compareResult;
        /***** Parsing variables ******/
     char *pToken;                 /* Token pointer to be used in parsing command line input string*/
     int tokenCount;               /* Counter used in parsing procedure*/
     char **str[10];               /* Array of strings pointed to by the token*/
        /*******************************/

     fflush(stdin);                 /* Flushing keyboard buffer from previous input*/
     strcpy(userInput," ");         /* Reseting userInput string array*/

     scanf("%[^\n]", userInput);	/* Accepting user Input*/
     scanf("%c", &temp);            /* Flushing '\n' character from the stdin buffer after user hit the 'Enter' */
     compareResult = strcmp(userInput,"");
     while(compareResult == 32)      /* Validating user input, No input = 'SPACE' (i.e decimal value 32)*/
      {
        int value = 0;
        printf("Please enter a valid command, or <help> for details\n\n");
        return value;
      }



/**************************************** Parsing Start *************************************************/
    tokenCount = 0;
    pToken = strtok (userInput," ");
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
			}
		else if (strcmp(Token[0], cmds[1]) == 0)      /*     exit()      */
			{
				valid = 1;
				printf("\nGood Bye!\n\n");
			}

		else if (strcmp(Token[0], cmds[2]) == 0)        /*     allocate()    */
			{
			   valid = 0;

		       if (Token[1]==0)             /* No offset enterred*/
                    {
                         printf("Please enter a valid offset value, or <help> for details\n");
                         return valid;
                    }

			   memoryOffsetValue = atoi(Token[1]);      /* Converting string to interger*/
			   Block_Address = allocate(memoryOffsetValue);

                if (Block_Address)
                    {
                        printf("\nMemory block allocated.\n\n");
                        printf("Address: %p    size: %d   (%d Bytes)\n\n", Block_Address, \
                        memoryOffsetValue, 4 * memoryOffsetValue);
                    }

			}

		else if (strcmp(Token[0], cmds[3]) == 0)        /*    free()    */
			{
				valid = 0;

				if(!Block_Address)
					printf("Memory is not allocated yet!\n");

				else
					{
						free_memory(Block_Address);
						printf(" %d Bytes of heap released from address %p to %p\n\n", \
					           4 * memoryOffsetValue,Block_Address, Block_Address + memoryOffsetValue-1);
                        Block_Address = NULL;
					}
			}


		else if (strcmp(Token[0], cmds[4]) == 0)        /*    display()    */
		    {
                valid = 0;

                if(!Block_Address)
                    printf("Memory is not allocated yet!\n\n");

                else
                    display(Block_Address, memoryOffsetValue);

            }

		else if (strcmp(Token[0], cmds[5]) == 0)        /*    write()    */
		    {
                valid = 0;

                if(!Block_Address)
                    printf("Memory is not allocated yet!\n\n");

                /* Condition to check if user entered correct number of arguments*/

                else  if (Token[1]==0 || Token[2] == 0)     /* No offset/value enterred*/
                    {
                         printf("Please enter a valid memory location and value, or <help> for details\n");
                         return valid;
                    }


                else
                    {

                        memoryValue = atoi (Token[2]);      /* Converting string to interger*/
                        location = atoi (Token[1]);         /* *(address + location) = place to write the value*/

                        /* A condition to check the correct offset value between 0 and maximum offset derived by allocate() */

                        if ((location > memoryOffsetValue-1) || (location < 0))
                            {
                                printf("Please enter a location value between 0 and %d\n", memoryOffsetValue-1);
                                return valid;
                            }

                        write(Block_Address, location, memoryValue);
                    }

            }
		else
		    {
		        valid = 0;
                printf("Invalid input, please try again: \n");
		    }

	return valid;
}
/*###################################### inputCheck () End #############################################*/

