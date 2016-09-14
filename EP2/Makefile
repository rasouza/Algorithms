CC     = gcc
CFLAGS = -Wall -O2 -ansi -pedantic -Wno-unused-result
GLLIB  = -lGL -lGLU -lglut

#------------------------------------------------

ep2: main.o graphic.o imagem.o io.o
	$(CC) main.o graphic.o imagem.o io.o -o ep2 -lGL -lGLU -lglut

main.o: main.c imagem.h graphic.h io.h  
	$(CC) $(CFLAGS) -c main.c 

graphic.o: graphic.c graphic.h imagem.h  
	$(CC) $(CFLAGS) -c graphic.c 

imagem.o: imagem.c imagem.h
	$(CC) $(CFLAGS) -c imagem.c 

io.o:   io.c io.h imagem.h
	$(CC) $(CFLAGS) -c io.c 

