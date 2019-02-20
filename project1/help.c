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
* @file help.c
* @brief This source file contains code that provides the help function definition. 
*
* @author Ismail Yesildirek & Bijan Kianian
* @date February 17 2019
* @version 1.1
*
*/

#include "memtest.h"

  void help (void)
  {
    printf(" mem_test commands:\n");
    printf("\thelp - this message\n");
    printf("\tallocate <word> - allocate <words> of memory\n");
    printf("\tfree - free previously allocated memory\n");
    printf("\tread <address> [<words>] - read from <address> for one or <words>\n");
    printf("\twrite <address> <value>] - write <value> to <address>\n");
    printf("\tinvert <address> <words>] -invert bits starting from <address> for <words>\n");
    printf("\tpattern <address> <words> [<seed>] - write pseudorandom pattern at <address> for <words> using <seed>\n");
    printf("\tverify <address> <words> [<seed>] - verify pseudorandom pattern at <address> for <words> using <seed>\n");
    printf("\texit - exit the program\n");
    
    return;
  }
  
    
