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
* @date February 17 2019
* @version 1.1
*
*/

#include "memtest.h"

int main()
{
	int validStatus = 0;  

  while(validStatus == 0)
    {
      validStatus = inputCheck();
    }
  
return 0;
}

int inputCheck(void)
{
	printf("This is a simple program for testing memory.\n");
	printf("Type 'help' for more details or 'exit' to leave the program: \n");
	char userInput[50];  /* array to store input command line string */
	scanf(" %s", userInput);  /* accepting user command line string by eliminating '\n' */

	char *cmds[] = { "help", "exit" }; /* constant strings to be compared with user input commands */
	int valid = 0;

	while (valid == 0)
	{
		if (strcmp(userInput, cmds[0]) == 0)
		{
			valid = 0;
			help();
			printf("Enter a command: \n");
			scanf(" %s", userInput);
		}
		else if (strcmp(userInput, cmds[1]) == 0)
		{
			valid = 1;
			printf("\nGood Bye!\n\n");
			return valid;
		}
		else
		{
			valid = 0;
			printf("Invalid input, please try again: \n");
			scanf(" %s", userInput);
		}
	}
	return 0;
}     
