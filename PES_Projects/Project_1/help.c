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
* @date March 10 2019
* @version 1.3
*
*/

#include "memtest.h"
#include "help.h"

  void help (void)
  {
    printf("\n\tmem_test commands\n\n");
    printf("\thelp - this message\n\n");
    printf("\tallocate <word> - allocate <words> of memory\n\n");
    printf("\tfree - free previously allocated memory\n\n");
    printf("\tread <-i> <address> <words> -\n");
    printf("\tread from <address> for one or <words> [<-i> immediate addressing]\n\n");
    printf("\twrite <-i> <address> <value>] -\n");
    printf("\twrite <value> to <address> [<-i> immediate addressing]\n\n");
    printf("\tinvert <-i> <address> <words> -\n");
    printf("\tinvert bits starting from <address> for <words> [<-i> immediate addressing]\n\n");
    printf("\tpattern <-i> <address> <words> [<seed>] -\n");
    printf("\twrite pseudorandom pattern at <address> for <words> using <seed> [<-i> immediate addressing]\n\n");
    printf("\tverify <-i> <address> <words> [<seed>] -\n");
    printf("\tverify pseudorandom pattern at <address> for <words> using <seed> [<-i> immediate addressing]\n\n");
    printf("\texit - exit the program\n\n");
    printf("\tNote: Please enter hexadecimal numbers without '0x'\n\n");
    return;
  }
