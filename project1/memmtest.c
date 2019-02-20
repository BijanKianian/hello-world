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
* @file Main.C
* @brief This source file contains a c program to xxxx. 
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 16 2019
* @version 1.0
*
*/

#include "memtest.h"

int main()
{
  char input[50];  // array to store input command line string
  char *cmds[]={"help", "exit"}; // constant strings to be compared with user input commands
  char *sub_texts[10];  //array of strings for saving sub texts after parsing user input line
  char *pToken;  // Token pointer to be used in parsing command line input string
  int tokenCount;  // counter used in parsing procedure
  char **str[10];  // array of strings pointed to by the token
  
 
       printf("This is a simple program for testing memory.\n");
       printf("Type 'help' for more details.\n");
      
  while(1)
    {
      strcpy(input,"");  //  clear array
      scanf("%[^\n]%*c",input);  // accepting user command line string by eliminating '\n' 
     
      
  
      ////////////////////// parsing procedure (Start) ///////////////////////
      tokenCount = 0;           
       pToken = strtok (input," ");
       str[0] = &pToken;
	     
	     while (pToken)
	       {
		 
		 sub_texts[tokenCount] = *str[tokenCount];        // saving the parsed sub texts into *str[] array
		 pToken = strtok (NULL, " ");
	        	 
		 tokenCount++;
		 str[tokenCount] = &pToken;   
	       }
        //////////////////////////// parsing procedure (End) ///////////////////

	    

	     if ((strcmp(sub_texts[0], *cmds) == 0))                        /*Detecting the user input command: The first string (sub_texts[0]) 
                                                                              shall be compared with the list of command strings saved in *cmds[] array*/
	       {
		 
		 help();
		 
	       }
	     		
             else if(strcmp(sub_texts[0], *(cmds+1)) == 0)   // exit program
	       {
		 printf("\nGood Bye!\n\n");
		 break;
	       }
	     else      // exit if "Enter" is hit w/o any command input
	       break;
      }
  
return 0;
}


     
