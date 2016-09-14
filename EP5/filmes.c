/*
\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__

   AO PREENCHER ESSE CABEÇALHO COM O MEU NOME E O MEU NÚMERO USP, 
   DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESSE PROGRAMA. 
   TODAS AS PARTES ORIGINAIS DESSE EXERCÍCIO PROGRAMA (EP) FORAM 
   DESENVOLVIDAS E IMPLEMENTADAS POR MIM SEGUINDO AS INSTRUÇÕES DESSE EP
   E QUE PORTANTO NÃO CONSTITUEM PLÁGIO. DECLARO TAMBÉM QUE SOU RESPONSÁVEL
   POR TODAS AS CÓPIAS DESSE PROGRAMA E QUE EU NÃO DISTRIBUI OU FACILITEI A
   SUA DISTRIBUIÇÃO. ESTOU CIENTE QUE OS CASOS DE PLÁGIO SÃO PUNIDOS COM 
   REPROVAÇÃO DIRETA NA DISCIPLINA.

   Nome: Rodrigo Alves Souza 6800149

   IMDB: filmes.c


   Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
   de aula, caso você tenha utilizado alguma refência, liste-as abaixo
   para que o seu programa não seja considerada plágio.
   Exemplo:
   - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

   \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
   */


   /*----------------------------------------------------------*/
   /* filmes.h e a interface para as funcoes neste modulo      */
#include "filmes.h" 

   /*----------------------------------------------------------*/
#include <stdlib.h>  /* NULL, free() */
#include <stdio.h>   /* printf(), scanf() */ 
#include <string.h>  /* strlen(), strncpy(), strcmp() */

#include "utils.h"     /* Bool, mallocSafe() */
#include "iofilmes.h"



   /*----------------------------------------------------------------------
   crieFilme(dist, votos, nota, nome, ano)

   Recebe informacoes dobre um filme 

   - dist  : distribuicao de notas
   - votos : numero de votos
   - nota  : nota do filme 
   - ano   : ano de producao do filme

   e cria uma celula do tipo Filme para armazenar essa informacao. 
   A funcao retorna o endereco da celula criada.
   */

Filme *
crieFilme (char dist[], int votos, float nota, char *nome, int ano)
{
   Filme *flm;
   int    len = strlen(nome) + 1; /* +1 para o '\0' */

   flm = mallocSafe(sizeof *flm);

   strncpy(flm->dist, dist, TAM_DIST+1); /* +1 para o '\0' */

   flm->votos = votos;
   flm->nota  = nota;

   flm->nome = mallocSafe(len*sizeof(char));
   strncpy(flm->nome, nome, len);

   flm->ano  = ano;

   flm->prox = flm->ant = NULL; /* paranoia */

   return flm;

   }



   /*----------------------------------------------------------------------
   crieListaFilmes()

   Cria uma estrutura que representa lista de filmes vazia.
   A funcao retorna o endereco dessa estrutura.

   Um lista de filmes e representada por uma lista encadeada 
   com cabeca duplamente ligada. 
   */

ListaFilmes *
crieListaFilmes()
{
   ListaFilmes *lst;

   lst =  mallocSafe(sizeof *lst);

   lst->nFilmes = 0;   
   lst->cab = mallocSafe(sizeof *lst->cab);

   lst->cab->ant  = lst->cab->prox = lst->cab;

   return lst;
}


/*----------------------------------------------------------------------
libereListaFilmes(lst)

Recebe um ponteiro lst para uma estrutura que representa uma lista 
de filmes e libera toda a memoria alocada para a lista.

Esta funcao utiliza a funcao libereFilme().


*/

void
libereListaFilmes(ListaFilmes *lst)
{
	Filme *filme, *p;

    filme = lst->cab->prox;

    while(filme!=lst->cab)
    {
        p = filme->prox;
        libereFilme(filme);
        filme = p;
    }

}


/*----------------------------------------------------------------------
libereFilme(flm)

Recebe um ponteiro flm para uma estrutura que representa um 
filme e libera a area alocada.

*/

void 
libereFilme(Filme *flm)
{
   free(flm->nome);
   flm->prox = flm->ant = NULL;
   free(flm);
}

/*----------------------------------------------------------------------
insiraFilme(lst, flm)

Recebe um ponteito lst para uma estrutura que representa
uma lista de filmes e um ponteiro para uma estrutura
que representa uma filme.

A funcao insere o filme na lista.

*/

void 
insiraFilme(ListaFilmes *lst, Filme *flm)
{
	if(!contemFilme(lst, flm))
	{
	    flm->prox = lst->cab->prox;
        flm->ant = lst->cab;
        lst->cab->prox = flm;
        flm->prox->ant = flm;

        lst->nFilmes++; 
     }
}


/*---------------------------------------------------------------------
contemFilme(lst, flm)

Recebe um ponteito lst para uma estrutura que representa
uma lista de filmes e um ponteiro para uma estrutura
que representa uma filme.

A funcao retorna  TRUE se o filme esta na lista e 
FALSE em caso contrario. 

Consideramos que dois filmes f e g sao iguais se

- f->nome  e' igual a g->nome )
- f->nota  e' igual a g->nota
- f->ano   e' igual a g->ano 

Para comparar dois nomes voce pode usar alguma funcao da 
bibliteca do c  como strcmp, strncmp (string,h) 
ou a funcao strCmp (utils.h).

*/

Bool 
contemFilme(ListaFilmes *lst, Filme *flm)
{

   Filme *filme = lst->cab->prox;
   while(filme != lst->cab)
   {
      if(!strCmp(filme->nome, flm->nome) && filme->nota == flm->nota && filme->ano == flm->ano)
         return TRUE;
      filme = filme->prox;
   }
   return FALSE;
}


/*----------------------------------------------------------------------
removaFilme(lst, flm)

Remove da lista e filmes lst o filme dado por flm.

Pre-condicao: a funcao supoe que o filme flm esta 
  na lista lst.
*/

void 
removaFilme(ListaFilmes *lst, Filme *flm)
{
   Filme *filme;
   filme = lst->cab->prox;
   while(filme != flm)
      filme = filme->prox;
   filme->ant->prox = filme->prox;
   filme->prox->ant = filme->ant;
   lst->nFilmes = lst->nFilmes - 1;
   
   libereFilme(filme);
}


/*----------------------------------------------------------------------
mergeSortFilmes(lst, criterio)

Ordena uma lista de filmes utilizando o algoritmo mergeSort 
recursivo adaptado para listas encadeadas duplamente ligadas.

Se criterio == NOTA, entao a lista deve ser ordenada
em ordem decrescente de nota.

Se criterio == NOME, entao a lista deve ser ordenada
em ordem crescente de nome (ordem alfabetica).

------------------------------------------------------------------
A ordenacao deve ser feita 'in-place', ou seja   
o conteudo das celulas nao deve ser copiado,  
apenas os ponteiros devem ser alterados.

A funcao so deve utilizar espaco extra O(1).
Hmmm, ok, sem levar em consideracao o espaco O(lg n)
utilizado pela pilha da recursao).
Em outras palavras, a funcao pode conter apenas declaracoes
de umas poucas variaveis (um vetor v[0..n] conta como 
n variaveis).

------------------------------------------------------------------
Para ordenar por nome, veja a funcao strCmp em utils.[h|c].
*/

void 
mergeSortFilmes(ListaFilmes *lst, Criterio criterio)
{

	ListaFilmes *lista;
	Filme *aux, *p, *q;
	int i, limite;
   
	if(lst->nFilmes > 1)
	{
		lista = mallocSafe(sizeof(ListaFilmes));
		lista->cab = mallocSafe(sizeof(Filme));
		      
		lista->cab->ant = lst->cab->prox;
		lista->cab->prox = lst->cab->prox;
      
		aux = lst->cab->prox;

		lst->cab->prox = lst->cab->prox->prox;
		lst->cab->prox->ant = lst->cab;

		aux->prox = lista->cab;
		aux->ant = lista->cab;
      
		for(i = 1; i < lst->nFilmes/2; i++)
		{
			p = lst->cab->prox;
			lst->cab->prox = lst->cab->prox->prox;
			lst->cab->prox->ant = lst->cab;
			q = lista->cab->ant;
			q->prox = p;
			p->prox = lista->cab;
			p->ant = q;
			lista->cab->ant = p;
		}
      
		if(lst->nFilmes % 2) 
			limite = lst->nFilmes/2 + 1;
		else 
			limite = lst->nFilmes/2;
      	
		lista->nFilmes = lst->nFilmes/2;
		lst->nFilmes = limite;

		mergeSortFilmes(lista, criterio);
		mergeSortFilmes(lst, criterio);
		intercala(lst, lista, criterio);

		free(lista->cab);
		free(lista);
	}
}


/*----------------------------------------------------------------------
quickSortFilmes(lst, criterio) [opcional]

Ordena uma lista de filmes utilizando o algoritmo quickSort 
adaptado para listas encadeadas duplamente ligadas.

Se criterio == NOTA, entao a lista deve ser ordenada
em ordem decrescente de nota.

Se criterio == NOME, entao a lista deve ser ordenada
em ordem crescente de nome (ordem alfabetica).

------------------------------------------------------------------
A ordenacao deve ser feita 'in-place', ou seja   
o conteudo das celulas nao deve ser copiado,  
apenas os ponteiros devem ser alterados.

A funcao so deve utilizar espaco extra O(1).
Hmmm, ok, sem levar em consideracao o espaco O(lg n)
utilizado pela pilha da recursao).
Em outras palavras, a funcao pode conter apenas declaracoes
de umas poucas variaveis (um vetor v[0..n] conta como 
n variaveis).

------------------------------------------------------------------
Para ordenar por nome, veja a funcao strCmp em utils.[h|c].
*/

void 
quickSortFilmes(ListaFilmes *lst, Criterio criterio)
{
	ListaFilmes *lista;
	Filme *q, *p, *aux, *aux2;
	int i = 1;
   
	if(lst->nFilmes > 1)
	{
		lista = mallocSafe(sizeof(ListaFilmes));
		lista->cab = mallocSafe(sizeof(Filme));
		
		q = separa(lst, criterio);
		
		lista->cab->prox = lista->cab->ant = lst->cab->prox;
		p = lst->cab->prox;
		
		lst->cab->prox = lst->cab->prox->prox;
		lst->cab->prox->ant = lst->cab;
		
		p->ant = lista->cab;
		p->prox = lista->cab;

		while(lista->cab->prox != q && lst->cab->prox != q)
		{
			aux = lst->cab->prox;
			aux2 = lista->cab->ant;
			
			lst->cab->prox = lst->cab->prox->prox;
			lst->cab->prox->ant = lst->cab;
			
			aux->prox = lista->cab;
			aux->ant = aux2;
			aux2->prox = aux;
			
			lista->cab->ant = aux;
			i++;
		}
      
		if(lista->cab->prox != q)
		{
			lst->cab->prox = lst->cab->prox->prox;
			lst->cab->prox->ant = lst->cab;
		}
      
		lista->nFilmes = i;
		lst->nFilmes = lst->nFilmes - i;
		
		quickSortFilmes(lista, criterio);
		quickSortFilmes(lst, criterio);

		if(lista->cab->prox != q)
		{
			aux = lista->cab->ant;
			aux->prox = q;
			
			q->ant = aux;
			q->prox = lista->cab;
			
			lista->cab->ant = q;
			lista->nFilmes++;
		}
		
		lista->cab->ant->prox = lst->cab->prox;
		lst->cab->prox->ant = lista->cab->ant;
		lista->cab->prox->ant = lst->cab;
		lst->cab->prox = lista->cab->prox;
		lst->nFilmes = lst->nFilmes + lista->nFilmes;
		
		free(lista->cab);
		free(lista);
	}
}


void intercala(ListaFilmes *lst1, ListaFilmes *lst2, Criterio criterio)
{
	Filme *p, *q, *aux;
	p = lst1->cab->prox;
	q = lst2->cab->prox;

	while(p != lst1->cab && q != lst2->cab)
	{
		if(criterio == NOTA)
		if(p->nota > q->nota)
			p = p->prox;
		else
		{
			aux = q;
			q = q->prox;
			aux->ant = p->ant;
			p->ant->prox = aux;
			aux->prox = p;
			p->ant = aux;
         }

		else
			if(strCmp(p->nome, q->nome) < 0)
        	    p = p->prox;
		else
		{
			aux = q;
			q = q->prox;
			aux->ant = p->ant;
			p->ant->prox = aux;
			aux->prox = p;
			p->ant = aux;
		}
	}
	while(p != lst1->cab) 
		p = p->prox;
	while(q != lst2->cab)
	{
		aux = q;
		q = q->prox;
		aux->ant = p->ant;
		p->ant->prox = aux;
		aux->prox = p;
		p->ant = aux;
	}
   
	lst1->nFilmes = lst1->nFilmes + lst2->nFilmes;
}


Filme *separa(ListaFilmes *lst, Criterio criterio)
{
	Filme *i, *p, *q, *j, *anterior, *prox;
	i = lst->cab->prox;
	q = lst->cab->ant;
	p = i->prox;
	while(lst->cab != p && p->ant != q)
	{
		if(criterio == NOTA)
			if(p->nota >= i->nota) 
				p = p->prox;
			else if(i->nota > q->nota) 
				q = q->ant;
			else
				if(p->prox == q)
				{
				   p->prox = q->prox;
				   q->prox->ant = p;
				   p->ant->prox = q;
				   q->ant = p->ant;
				   p->ant = q;
				   q->prox = p;
				}
				else
				{
					anterior = p->ant;
					prox = p->prox;
					p->prox = q->prox;
					p->ant = q->ant;
					q->ant->prox = q->prox->ant = p;
					q->ant = anterior;
					q->prox = prox;
					anterior->prox = prox->ant = q;
					j = p;
					p = q;
					q = j;
		        }
      
		else
		{
			if(strCmp(p->nome, i->nome) < 0)
				p = p->prox;
			else if(strCmp(i->nome, q->nome) < 0)
				q = q->ant;
			else
				if(p->prox == q)
		        {
					p->prox = q->prox;
					q->prox->ant = p;
					p->ant->prox = q;
					q->ant = p->ant;
					p->ant = q;
					q->prox = p;
		        }
				else
				{
					anterior = p->ant;
					prox = p->prox;
					p->prox = q->prox;
					p->ant = q->ant;
					q->ant->prox = q->prox->ant = p;
					q->ant = anterior;
					q->prox = prox;
					anterior->prox = prox->ant = q;
					j = p;
					p = q;
					q = j;
				}
      }
   }
   
	if(i->prox == q)
	{
		i->prox = q->prox;
		q->prox->ant = i;
		i->ant->prox = q;
		i->ant = i;
		q->prox = i;
	}
	else
	{
		prox = i->prox;
		i->ant = q->ant;
		i->prox = q->prox;
		q->prox->ant = q->ant->prox = i;
		q->ant = lst->cab;
		q->prox = prox;
		lst->cab->prox = q;
	}
	return i;
}
