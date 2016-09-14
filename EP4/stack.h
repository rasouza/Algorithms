#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void stackPush(CelUtil *iniPilha, CelUtil *nova);
CelUtil* stackTop(CelUtil *iniPilha);
CelUtil* stackPop(CelUtil *iniPilha);
void stackFree(CelUtil *iniPilha);
