CC=gcc
CFLAGS=-c -Wall -Werror

memtest: memtest.o help.o allocate.o free.o display.o write.o invert.o pattern.o verify.o
	$(CC) -o  memtest memtest.o help.o allocate.o free.o display.o write.o invert.o pattern.o verify.o
	$(CC) $(CFLAGS) memtest.c
help.o: help.c help.h
	$(CC) $(CFLAGS) help.c
allocate.o: allocate.c allocate.h
	$(CC) $(CFLAGS) allocate.c
free.o: free.c free.h
	$(CC) $(CFLAGS) free.c
display.o: display.c display.h
	$(CC) $(CFLAGS) display.c
write.o: write.c write.h
	$(CC) $(CFLAGS) write.c
invert.o: invert.c invert.h
	$(CC) $(CFLAGS) invert.c
pattern.o: pattern.c pattern.h
	$(CC) $(CFLAGS) pattern.c
verify.o: verify.c verify.h
	$(CC) $(CFLAGS) verify.c
test: memtest test.txt
	./memtest<test.txt>outputFile.txt
clean:
	rm -rf *o memtest
	rm -rf outputFile.txt
