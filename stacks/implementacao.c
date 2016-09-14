#include <stdio.h>
#include <stdlib.h>

typedef struct stackNode *Link;
typedef struct stack *Stack;

struct stackNode {
	int conteudo;
	Link prox;
};

struct stack {
	Link topo;
};

void
stackDump(Stack s)
{
    Link ini = s->topo;
	if (ini == NULL)
		printf("\n[DUMP] A pilha esta vazia.\n\n");
	else {
		printf("\n[DUMP] Conteudo da pilha:\n");
		printf("endereco      elemento   prox\n");
		while (ini != NULL) {
			printf("%p     %5d      %p\n", (void*)ini, ini->conteudo, (void*)ini->prox);
			ini = ini->prox;
		}
		printf("\n");
	}
}

Stack stackInit()
{
	Stack s = malloc(sizeof *s);
	s->topo = NULL;

	printf("Pilha inicializada \n");

	return s;
}

void stackPush(Stack s, int v)
{

	Link p = malloc(sizeof *p);
	p->conteudo = v;
	p->prox = s->topo;
	s->topo = p;

	printf("Colocando o item %d na pilha \n", v);
}

int stackPop(Stack s)
{
	Link p = s->topo;
	int conteudo;

	if (p == NULL) printf("Tentando stackPop() em uma pilha ja vazia\n");

	else {
		conteudo = p->conteudo;
		s->topo = p->prox;	
		free(p);
		printf("Retirando o item %d da pilha \n", conteudo);
	}

	

	return conteudo;
}

int stackTop(Stack s)
{
	if (s->topo != NULL) {
		printf("\nRetornando o topo da pilha: %d\n", s->topo->conteudo);
		return s->topo->conteudo;
	}

	return 0;
}

void stackFree(Stack s)
{	
	while (s->topo != NULL) {
		Link p = s->topo;
		s->topo = p->prox;
		free(p);	
	}
	free(s);
}
