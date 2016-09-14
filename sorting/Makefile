CFLAGS = -g  -Wall -ansi -pedantic -Wno-unused-result
CC = gcc
###########################################################################

sort: main.o sorting.o
	$(CC) sorting.o main.o  -o $@
	
sorting.o: sorting.c
	$(CC) $(CFLAGS) -c $<
	
main.o: main.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f *.o
