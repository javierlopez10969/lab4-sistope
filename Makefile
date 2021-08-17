CC=gcc
CFLAGS=-lm
all : lab4 lab4.o	

lab4: lab4.c funciones.c funciones.h
	$(CC) funciones.c funciones.h lab4.c -o lab4 $(CFLAGS)
funciones : 

clean:
	rm -f *.o all
.PHONY : clean
