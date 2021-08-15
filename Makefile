CC=gcc
CFLAGS=-lm
all : lab4 lab4.o	

lab3: lab4.c funciones.c funciones.h
	$(CC) funciones.c lab4.c -o lab4 $(CFLAGS)

clean:
	rm -f *.o all
.PHONY : clean
