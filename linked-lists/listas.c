#include <stdio.h>
#include <stdlib.h>

typedef struct celula Celula;
struct celula {
	int conteudo;
	Celula *prox;
};

void imprima(Celula *ini);
void insere(Celula *ini, int v);
void buscaRemova(Celula *ini, int x);
void buscaInsere(int x, int y, Celula *ini);
void inverte(Celula **ini);

int main() {

Celula *ini;

/* Inicializa celula com cabeca */
ini = malloc(sizeof(Celula));
ini->prox = NULL;

imprima(ini);
insere(ini, 4);
insere(ini, 3);
insere(ini, 2);
imprima(ini);
buscaRemova(ini, 2);
imprima(ini);
buscaInsere(2, 3, ini);
imprima(ini);
inverte(&ini->prox);
imprima(ini);

return 0;
}

/*
 * A funcao imprime recebe o apontador para a celula cabeca de 
 * uma lista ligada e imprime o endereco, campo conteudo, e campo prox,
 * de cada celula da lista ligada, exceto a celula cabeca.
 */
void
imprima(Celula *ini)
{
  if (ini->prox == NULL)
    printf("A lista esta vazia.\n");
  else {
    printf("Conteudo da lista:\n");
    printf("endereco      elemento   prox\n");
    for (ini=ini->prox; ini != NULL; ini=ini->prox)
      printf("%p     %5d      %p\n", 
	     (void*)ini, ini->conteudo, (void*)ini->prox);
    printf("\n");
  }
}

void insere(Celula *ini, int v) {
	Celula *nova;
	nova = malloc(sizeof(Celula));

	nova->conteudo = v;
	nova->prox = ini->prox;
	ini->prox = nova;
}
void remova (Celula *p) {
	Celula *morta;

	morta = p->prox;
	p->prox = morta->prox;
	free(morta);
}
void buscaRemova(Celula *ini, int x) {
	Celula *p;
	
	for(p = ini; ini != NULL && ini->conteudo != x; ini = ini->prox) {
		p = ini;
	}
	if (ini != NULL)
		remova(p);
}

void buscaInsere(int x, int y, Celula *ini) {
	Celula *nova, *p, *q;
	nova = malloc(sizeof(Celula));
	nova->conteudo = x;
		
	p = ini;
	q = p->prox;
	while (q != NULL && q->conteudo != y) {
		p = q;
		q = q->prox;
	}
	p->prox = nova;
	nova->prox = q;
}

void inverte(Celula **ini) {
	Celula *p, *q, *r;

	p = NULL;
	q = *ini;

	while (q != NULL) {
		r = q->prox;
		q->prox = p;
		p = q;
		q = r;		
	}

	*ini = p;
}
