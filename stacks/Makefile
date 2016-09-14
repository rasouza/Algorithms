CFLAGS = -g  -Wall -ansi -pedantic -Wno-unused-result
CC = gcc
###########################################################################

stack: stack.o implementacao.o
	$(CC) stack.o implementacao.o -o $@

stack.o: stack.c
	$(CC) $(CFLAGS) -c $<

implementacao.o: implementacao.c
	$(CC) $(CFLAGS) -c $<

