CFLAGS= -g -Wall -O2 -ansi -pedantic -Wno-unused-result
CC = gcc
RM = rm
#-------------------------------------------------

imdb:  main.o  utils.o iofilmes.o filmes.o  main.o 
	$(CC) main.o utils.o iofilmes.o filmes.o -o imdb

main.o: main.c filmes.h utils.h iofilmes.h
	$(CC) $(CFLAGS) -c main.c

filmes.o: filmes.c filmes.h utils.h iofilmes.h
	$(CC) $(CFLAGS) -c filmes.c

iofilmes.o: iofilmes.h iofilmes.c
	$(CC) $(CFLAGS) -c iofilmes.c

utils.o: utils.h utils.c
	$(CC) $(CFLAGS) -c utils.c

clean: 
	$(RM) *.o *~
