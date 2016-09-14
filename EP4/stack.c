#include "stack.h"
#include "util.h"

void stackPush(CelUtil *iniPilha, CelUtil *nova)
{
		nova->prox = iniPilha->prox;
		iniPilha->prox = nova;		
}

CelUtil* stackTop(CelUtil *iniPilha)
{
		if(iniPilha->prox == NULL)
		{
			fprintf(stderr, "[ERROR] A Pilha esta vazia!\n");
			exit(-1);
		}
		
		return iniPilha->prox;
}

CelUtil* stackPop(CelUtil *iniPilha)
{
		CelUtil *p;

		if(iniPilha->prox == NULL)
		{
			fprintf(stderr, "[ERROR] A Pilha esta vazia!\n");
			exit(-1);
		}
		
		p = iniPilha->prox;
		
		iniPilha->prox = p->prox;

		return p;
}


void stackFree(CelUtil *iniPilha)
{
		CelUtil *morta;
		CelUtil *p = iniPilha->prox;
		p = p->prox;
		while(p != NULL)
		{
			morta = p;
			p = p->prox;
			free(morta);	
		}

}
