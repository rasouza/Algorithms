typedef struct stack *Stack;

Stack stackInit();
void stackDump(Stack s);
void stackPush(Stack s, int v);
int stackPop(Stack s);
int stackTop(Stack s);
void stackFree(Stack s);


