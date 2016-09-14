CFLAGS = -g  -Wall -ansi -pedantic -Wno-unused-result
CC = gcc
###########################################################################

pointers: pointers.c
	$(CC) $(CFLAGS) $<  -o $@
	
clean:
	rm pointers
	find . -name \*.o -delete
