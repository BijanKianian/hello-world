
#include <stdio.h>
#include <stdlib.h>


/*=================== Function Prototypes ===============*/

int* allocate(void);
void free_memory(int*);

/*=======================================================*/

void  main ()

{
  int *memBlock_pointer;
  int choice, validInput;
  char Exit;
 
  
  printf("Please select the requred operation from the listand hit 'Enter'\n");

  do
    {
      printf("1. Allocate memory\n");
      printf("2. Free memory\n");
      
      validInput = scanf("%d",&choice);
     
      if((choice < 1) || (choice >2) ||( validInput != 1))
	{
	  while (getchar() != '\n')   // flush the keyboard buffer
	    ;
	  
	  printf("\n Invalid choice! Try again Or press  'q' to quit.");
	  Exit = getchar();
	  if (Exit == 'q')
	    break;
	}
    } while ((choice < 1) || (choice >2) ||( validInput != 1));
  
  switch(choice)
    {
  case 1:
    memBlock_pointer =  allocate();
    break;

    case 2:
    free_memory(memBlock_pointer);
    break;

    }

  return;
}

/*===================================*/
/*            allocate()             */
/*===================================*/

int* allocate(void)
{
  int bytesOfMemory=0;
  int i;
  int *ptr;
 
  
  printf("\nEnter the memory block size in bytes:");
  scanf("%d", &bytesOfMemory);                       // asking user to enter the size of memory block in bytes for allocation
  
  ptr =(int*) malloc(bytesOfMemory * sizeof(char));  // assigning an int pointer to the block of memory with requested size

  if (ptr == NULL)   // check if there is a room available in the heap
    {
      printf("Allocation failed!\n");
      exit(0);
    }
    
  printf("\nInitialization of %d bytes of memory\n\n",bytesOfMemory);   // validating the allocated locations
                                                                        // by writing into the locations and printing the address
                                                                        // and corresponded value (optional)
  printf("   Address       Value   \n");
  printf("_____________________\n");
   for(i = 0 ; i < bytesOfMemory ; i++)
    {
     
      *(ptr+i) = i;
      
      printf("%p ->  %d\n", ptr + i,*(ptr + i)); // 
      
      }
 
   printf("\nAllocation complete!\n\n");

   return ptr;
 }

/*===================================*/
/*          free_memory()           */
/*===================================*/

void free_memory(int *pointer)
{
    free(pointer);
    printf("Memory block released");
   return;
}
  
