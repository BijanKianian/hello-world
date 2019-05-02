CC=gcc
CFLAGS=-c -Wall -Werror

ringBuffer: ringBuffer.o
	$(CC) -o ringBuffer ringBuffer.o
	
ringBuffer.o: ringBuffer.c ringBuffer.h
	$(CC) $(CFLAGS) ringBuffer.c
	
clean:
	rm -rf *.o ringBuffer
