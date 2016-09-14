CC     = gcc
CFLAGS = -g -Wall -ansi -pedantic -Wno-unused-result
RM     = rm
#------------------------------------------------

# chama o linker
pitao:  main.o eval.o lexer.o util.o posfixa.o ts.o stack.o
	$(CC) main.o eval.o lexer.o util.o posfixa.o ts.o stack.o -o pitao -lm

main.o: main.c eval.h lexer.h util.h classes.h ts.h 
	$(CC) $(CFLAGS) -c main.c 

eval.o: eval.c eval.h util.h classes.h ts.h
	$(CC) $(CFLAGS) -c eval.c  

posfixa.o: posfixa.c posfixa.h util.h 
	$(CC) $(CFLAGS) -c posfixa.c

ts.o: ts.c ts.h util.h
	$(CC) $(CFLAGS) -c ts.c 

lexer.o: lexer.c lexer.h util.h classes.h 
	$(CC) $(CFLAGS) -c lexer.c 

util.o: util.c util.h classes.h
	$(CC) $(CFLAGS) -c util.c 
	
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
	 
clean: 
	rm -f *.o 
