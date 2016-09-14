typedef struct queue *Queue;

Queue queueInit();
void queuePut(Queue q, int v);
int queueGet(Queue q);
int queueEmpty(Queue q);
void queueFree(Queue q);
void queueDump(Queue q);
