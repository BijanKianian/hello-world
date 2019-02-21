
/*===================================*/
/*            allocate()             */
/*===================================*/
#include "memtest.h"

int* allocate(int offset)
{
  int *ptr;
  ptr =(int*) calloc(offset, sizeof(int));  // assigning an int pointer to the block of memory with requested size

  if (ptr == NULL)                          // check if there is a room available in the heap
    printf("Allocation failed!\n");

  return ptr;
 }

