CC=gcc
DEBUG = -g 
CFLAGS=-Wall $(DEBUG)
LFLAGS=-Wall $(DEBUG) 

Lisp: main.o 
	$(CC) $(LFLAGS) main.o -o Lisp

LispReader.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(ODIR)/*.o alm
