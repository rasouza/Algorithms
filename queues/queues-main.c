#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main() 
{
	Queue q1;
	
	q1 = queueInit();
	
	queueDump(q1);
	
	queuePut(q1, 2);
	queuePut(q1, 3);
	queuePut(q1, 4);
	queuePut(q1, 5);
	
	queueDump(q1);
	
	queueGet(q1);
	queueGet(q1);
	
	queueDump(q1);
	
	queueGet(q1);
	queueGet(q1);
	
	queueDump(q1);
	
	printf("\nA fila esta vazia? %d\n",queueEmpty(q1));
	
	queueFree(q1);

	return 0;
}
