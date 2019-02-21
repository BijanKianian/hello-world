CC=gcc
CFLAGS=-c -Wall -Werror

memtest: memtest.o help.o allocate.o free.o
	$(CC) -o  memtest memtest.o help.o allocate.o free.o
	$(CC) $(CFLAGS) memtest.c
help.o: help.c
	$(CC) $(CFLAGS) help.c
allocate.o:
	$(CC) S(CFLAGS) allocate.c
free.o: free.c
	$(CC) S(CFLAGS) free.c
clean:
	rm -rf *o memtest
