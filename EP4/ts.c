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

  ts.c
  Pitao II

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO
*/


/* iterface para o uso da funcao deste módulo */
#include "ts.h"     /* tipo CelTS */

#include <stdlib.h> /* free() */
#include <string.h>

#include "util.h"  /* mallocSafe() */

/*-----------------------------------------------------------
    A tabela de simbolos dever ser implementada atraves de uma 
    __lista ligada com cabeca__. 

    Note que todas as listas, filas e pilhas neste EP sao com 
    cabeca.
*/

/* ponteiro para a celula cabeca da lista que representa a tabela
   de simbolos */
static CelTS *ini; 

/* funcao auxiliar */
static CelTS *endVarTS(char *nomeVar);

/*-------------------------------------------------------------
   initTS()

   Funcao que cria uma tabela de simbolos vazia.
   
   Em outras palavras, cria uma lista ligada com cabeca 
   vazia. Cada celula da lista e' do tipo CelTS.

 */

void 
initTS()
{

	ini = mallocSafe(sizeof (CelTS));
	ini->prox = NULL;

}


/*-------------------------------------------------------------
   getValorTS(nomeVar)

   Recebe o nome 'nomeVar' de uma variavel, procura 
   essa variavel na tabela de simbolos e retorna o seu valor.

   Esta funcao deve utilizar a funcao endVarTS().
 */

float
getValorTS(char *nomeVar)
{
	CelTS *p;

    p = endVarTS(nomeVar);

    return p->valor;
}


/*-------------------------------------------------------------
   setValorTS(nomeVar,valor)

   Recebe o nome 'nomeVar' de uma variavel e um numero 'valor', 
   procura essa variavel na tabela de simbolos e atribui o numero 
   a essa variavel.

   Esta funcao deve utilizar a funcao endVarTS().
 */

void
setValorTS(char *nomeVar, float valor)
{

	CelTS *p = endVarTS(nomeVar);

    p->valor=valor;
    p->inic=TRUE;
	
}

/*-------------------------------------------------------------
   freeTS()

   Funcao que libera toda a memoria alocada para a tabela
   de simbolos.

 */

void 
freeTS()
{
	CelTS *p = ini;
    CelTS *morta;

    while(p != NULL)
    {
        free(p->nomeVar);
        morta = p->prox;
        free(p);
        p = morta;
    }
}

/*-------------------------------------------------------------
   showTS()

   Funcao que para cada variavel na tabela de simbolos mostra:

       - o seu nome;
       - se a variavel foi ou nao inicializada
       - o valor atual da variavel.
 */

void
showTS()
{

	CelTS *p = ini->prox;

    printf("\n\n==========================");
    printf("\n   Tabela de Simbolos     \n");
    printf("  nome - inicializada? - valor\n");
    printf("--------------------------\n\n");

    while(p!=NULL)
    {
        if(!(p->inic))
        	printf("%s - nao\n", p->nomeVar);
		else
			printf("%s - sim - %f\n", p->nomeVar, p->valor);
		p=p->prox;
    }

}


/*-------------------------------------------------------------
   endVarTS(nomeVar)

   Recebe um string 'nomeVar' com o nome de uma variavel e retorna
   o endereco da celula na tabela de simbolos que representa a 
   variavel. 

   Se na tabela de simbolos nao for encontrada uma celula que
   representa a variavel de nome 'nomeVar' uma nova celula e
   inserida na tabela para representar essa variavel.

   Esta funcao utiliza a funcao mallocSafe().
   Esta funcao aloca um string para copiar o nome da variavel 
   para o campo nomeVar da celula (strcpy ou strncpy ou ...).
 */

static CelTS *
endVarTS(char *nomeVar)
{
	CelTS *p = ini->prox;
    CelTS *q;
    int length = strlen(nomeVar);

    while(p != NULL)
    {
        if(!strcmp(nomeVar, p->nomeVar))
            return p;

		p = p->prox;
    }


    q = mallocSafe(sizeof *p);
    q->nomeVar = mallocSafe(length +1);
    strncpy(q->nomeVar, nomeVar, length+1);
    q->inic = FALSE;
    q->prox = NULL;

    p = ini->prox;
    ini->prox = q;
    q->prox = p;

    return q;
}
