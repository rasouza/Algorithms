#include <stdlib.h>
#include <stdio.h>
#include "interface.h"

int main() {
	Stack s1;	

	s1 = stackInit();	

	stackDump(s1);

	stackPush(s1, 2);
	stackPush(s1, 3);
	stackTop(s1);

	stackDump(s1);

	stackPop(s1);
	stackPop(s1);

	stackDump(s1);

	stackPop(s1);	

	

	return 0;
}


