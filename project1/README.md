# ECEN5813_SP19_Project1
## Project 1: Interactive Memory Manipulation
02/16/2019:
memtest.c, help.c, memtest.h and Makefile commited (BK)
02/21/2019:
memtest.c updated to impliment parsing command line input, free.c and allocate.c included to the project.
2/23/2019:
Aded write.c and display.c to the develop branch, memtest.c bugs removed.(BK)

### Functions Created: 

Help - The initial greeting on startup must minimally indicate how to invoke the help function. 
Invoking the help function will minimally list, to standard output, the available commands and how to invoke them.

Allocate memory - Uses malloc() to allocate a block of memory for use by the application. 
The user specifies the number of bytes or words of memory to allocate.

Free memory - Uses free() to release the previously allocated block.

Display memory words - Display contents of memory in terms of 32-bit words in hexadecimal format. 
The user may specify an address and the number of words to display.

Write memory words - User specifies an address and the 32-bit value to write. 
Memory at the indicated location is modified accordingly.

Invert block - Use an XOR operation to invert all memory bits in a specified area of memory. 
On completion, this command should report the amount of time taken to perform the operation.

Write pattern - Write a pseudo-random pattern in a user specified (address and length) area of memory using a 
user specified seed value. On completion, this command should report the amount of time taken to perform the 
operation.

Verify pattern - Verify a pseudo-random pattern in a specified (address and length) area of memory using a 
specified seed value. If pattern does not match, command should print expected and actual value and memory 
address where the discrepancy was found. On successful completion, this command should report the amount of 
time taken to perform the operation.

Functions should do bounds checking and warn the user if they attempt to read or write memory outside the 
allocated range (or if no memory block has been allocated) but should give users the option to ignore the warnings.
