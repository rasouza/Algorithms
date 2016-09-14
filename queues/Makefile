CFLAGS = -g  -Wall -ansi -pedantic -Wno-unused-result
CC = gcc
###########################################################################

queue: queue.o queues-main.o
	$(CC) queue.o queues-main.o -o $@

queue.o: queue.c
	$(CC) $(CFLAGS) -c $<

queues-main.o: queues-main.c
	$(CC) $(CFLAGS) -c $<

