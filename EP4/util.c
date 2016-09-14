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

  util.c
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

#include "util.h" /* interface para este modulo */

#include <stdlib.h> /* exit(), malloc(), EXIT_FAILURE */ 
#include <stdio.h>  /* fprinf(), stderr */
#include <string.h>  /* strlen() */


/*----------------------------------------------------------*/
/* a 'tabela' operador esta definida em lexer.c             */
extern char *operador[MAX_OPERADORES];

/*-----------------------------------------------------------*/
/* ATENCAO: a ordem dos strings a seguir devem ser compativeis 
   com a ordem das tabelas de operadores e com a enumeracao 
   das classes. 
 
   A tabela a seguir serve para exibirmos os nomes dos 
   itens ou operadores.
*/

static char *nomeClasse[MAX_CLASSES] =
{
    /* 4 operadores relacionais com 2 simbolos */
    /* "==" */  "operador relacional igual"
    /* "!=" */ ,"operador relacional diferente"
    /* ">=" */ ,"operador relacional maior ou igual"
    /* "<=" */ ,"operador relacional menor ou igual"
 
    /* 2 operadores relacionais com 1 simbolo */
    /* ">"  */ ,"operador relacional maior"
    /* "<"  */ ,"operador relacional menor"

    /* 7 operadores aritmeticos */
    /* "^"  */ ,"operador aritmetico exponenciacao" 
    /* "%" */  ,"operador aritmetico resto de divisao"
    /* "*"  */ ,"operador aritmetico multiplicacao"
    /* "/"  */ ,"operador aritmetico divisao"
    /* "+"  */ ,"operador aritmetico adicao"
    /* "-"  */ ,"operador aritmetico subtracao"
    /* "_"  */ ,"operador aritmetico \"menos unario\""

    /* 3 operadores logicos */
    /* "&&" */ ,"operador logico e" 
    /* "||" */ ,"operador logico ou"
    /* "!"  */ ,"operador logico negacao"

    /* atribuicao */ 
    /* "=" */  ,"operador de atribuicao" 

    /* EP4: parenteses */ 
    /* "(" */  ,"abre parenteses" 
    /* ")" */  ,"fecha parenteses" 

    /* constante */
    ,"string representando um float"
    ,"constante float"

    /* identificador */
    ,"nome de um identificador" 
    ,"ponteiro para um identificador na TS" 
};


/*-------------------------------------------------------------
  mostreUtil(pUtil, tipo)

  Recebe um ponteiro pUtil para uma celula do tipo CelUtil 
  e imprime o seu conteudo. 

  O conteudo depende do parametro tipo:

     - tipo == VALOR ou tipo == PILHA
       
       se a classe for de um operador, a precedencia 
       pUtil->prec do operador e' mostrado (%d);  

       se a classe for FLOAT, o valor do float pUtil->vFloat
       e' mostrado (%f)

       se a classe for ID_STR, o nome do identificador e 
       exibido (%s)

    - tipo == ITEM_LEXICO

       os strings correspondentes ao item lexico pUtil->pStr 
       e o nome da classe nomeClasse[pUtil->classe])
       sao mostrados.


    - tipo == POSFIXA

      se a classe for FLOAT o valor do float pUtil->vFloat é 
      mostrado (%g) 

      se a classe for ID_STR o nome do identificado e'
      exibido
            
      se a classe for a de um operador, o operador sera
      mostrado.
*/
	
void
mostreUtil(CelUtil *pUtil, int tipo)
{
    if (pUtil == NULL)
    {
	AVISO(mostreUtil: NULL recebido como parametro);
	return;    
    }
    
    if (tipo == VALOR || tipo == PILHA) 
    {
	if (pUtil->classe < MAX_OPERADORES) 
	{
	    printf("prec=%d", pUtil->prec);
	}   
	else if (pUtil->classe == FLOAT)
	{
	    printf("%f",  pUtil->vFloat);
	}
	else if (pUtil->classe == ID_STR) /* acrescentado em 04/OUT */
	{
	    printf("%s", pUtil->pNomeID);
	}
	else 
	{
	    AVISO(mostreUtil: classe inesperada);
	}
	printf("  -  %s\n", nomeClasse[pUtil->classe]);
    }
    else if (tipo == ITEM_LEXICO)
    {
	if (pUtil->classe == INDEFINIDA) 
	{
	    printf("\"%s\"  -  INDEFINIDA\n", pUtil->pStr);
	}
	else
	{
	    printf("\"%s\"  -  %s\n", pUtil->pStr, nomeClasse[pUtil->classe]);
	}
    }   
    else if (tipo == POSFIXA)
    {
	if (pUtil->classe == FLOAT)
	{
	    printf(" %g", pUtil->vFloat);
	}
	else if (pUtil->classe == ID_STR)
	{
	    printf(" %s", pUtil->pNomeID);
	}
	else
	{
	    printf(" %s", operador[pUtil->classe]);
	}
    }
}

/*-------------------------------------------------------------
  mostreListaUtil(iniLista, tipo)

  Recebe uma lista ligada iniLista com cabeca de celulas do tipo 
  CelUtil que representa uma fila de objetos do tipo Util.

  Imprime todos os elementos da lista. 
  O parametro tipo indicado o conteudo dos objetos da
  lista que podem ser

      - (TAREFA EP3) ITEM_LEXICO (string);
      - (TAREFA EP3) VALOR (um float ou inteiro..) 
      - (TAREFA EP4) POSFIXA (um float, um string representando 
                     um operador, ou um string contendo 
                     o nome de uma variavel.

  Esta funcao deve usar a funcao mostreUtil.
*/ 

void
mostreListaUtil (CelUtil *iniLista, int tipo)
{
	CelUtil *p = iniLista->prox;

    while(p != NULL)
    {
        mostreUtil(p, tipo);
        printf("\n");
        p = p->prox;
    }
}    



/*-------------------------------------------------------------
  freeUtil(pUtil)

  Recebe um ponteiro pUtil para uma celula do tipo CelUtil 
  e libera a area alocada por esta celula. 

  Se o campo Util contem um ponteiro para um string, entao 
  a area aloca para o string tambem e' liberada.

*/

void
freeUtil(CelUtil *pUtil)
{
    if (pUtil == NULL) 
    {
	AVISO(freeUtil: NULL recebido como parametro);
	return;
    }

    if (pUtil->classe == FLOAT_STR || pUtil->classe == ID_STR)
    {
		if (pUtil->pStr) free(pUtil->pStr);
    }

    free(pUtil);
}

/*-------------------------------------------------------------
  freeListaUtil(iniLista)

  Recebe uma lista com cabeca iniLista de celulas do tipo 
  CelUtil e libera a area alocada por esta lista. 

  Esta funcao deve utilizar a funcao freeUtil().

*/

void
freeListaUtil(CelUtil *iniLista)
{
	CelUtil *p;
	CelUtil *morta;

	p = iniLista;

	while( p != NULL){
		morta = p;
		p = p->prox;
		freeUtil(morta);

	}

}


 
/*-------------------------------------------------------------*/ 
/*  mallocSafe 

   O parâmetro de mallocSafe é do tipo size_t.  
   Em muitos computadores, size_t é equivalente a unsigned int.  
   A função mallocSafe não está em nenhuma biblioteca e é desconhecida 
   fora destas notas de aula. 
   Ela é apenas uma abreviatura conveniente.

   Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 */

void *
mallocSafe (size_t nbytes)
{
   void *ptr;

   ptr = malloc (nbytes);
   if (ptr == NULL) {
     fprintf (stderr, "Socorro! malloc devolveu NULL!\n");
     exit (EXIT_FAILURE);
   }

   return ptr;
}
 
