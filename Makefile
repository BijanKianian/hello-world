CC=gcc
CFLAGS=-c -Wall -Werror 

C_Etude_2: C_Etude_2.o
	$(CC) -o  C_Etude_2 C_Etude_2.c
C_Etude_2.o: C_Etude_2.c
	$(CC) $(CFLAGS) C_Etude_2.c
clean:
	rm -rf *o C_Etude_2

