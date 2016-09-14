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

  eval.c
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

/*------------------------------------------------------------*/
/* interface para as funcoes deste modulo */
#include "eval.h" 

/*------------------------------------------------------------*/
#include <stdlib.h>  /* free(), atoi(), atof() */
#include <string.h>  /* strncmp(), strlen(), strncpy(), strcpy() */
#include <math.h>    /* pow() */

/*------------------------------------------------------------*/
#include "classes.h" /* tipo Classe */
#include "ts.h"      /* getValorTS() e setValorTS() */

/*------------------------------------------------------------*/
#include "stack.h" /* Implementacao de pilha */

/*------------------------------------------------------------
  Tabela com a preceedencia do operadores

  http://www.ime.usp.br/~pf/algoritmos/apend/precedence.html
*/
static const int precedencia[MAX_OPERADORES] =
{
    /* 4 operadores relacionais com 2 simbolos  */
     4   /* "==" */ /* da esquerda para a direita */
    ,4   /* "!=" */ /* da esquerda para a direita */
    ,5   /* ">=" */ /* da esquerda para a direita */
    ,5   /* "<=" */ /* da esquerda para a direita */
    
    /* 2 operadores relacionais com 1 simbolo */
    ,5  /* ">"  */ /* da esquerda para a direita */
    ,5  /* "<"  */ /* da esquerda para a direita */ 
    
    /* 7 operadores aritmeticos */
    ,8  /* "^" */ /* da direita para a esquerda */
    ,7  /* "%" */ /* da esquerda para a direita */
    ,7  /* "*" */ /* da esquerda para a direita */
    ,7  /* "/" */ /* da esquerda para a direita */
    ,6  /* "+" */ /* da esquerda para a direita */
    ,6  /* "-" */ /* da esquerda para a direita */
    ,8  /* "_" */ /* da direita para a esquerda */
    
    /* 3 operadores logicos  */
    ,3  /* "&&" */ /* da esquerda para a direita */ 
    ,2  /* "||" */ /* da esquerda para a direita */
    ,8  /* "!"  */ /* da direita para a esquerda */

     /* atribuicao */ 
    ,1  /* "=" */ /* da direita para a esquerda */ 
}; 


/*-------------------------------------------------------------
    itensParaValores(iniFilaItens)
    
    Recebe uma lista ligada com cabeca iniFilaItens representado uma 
    fila de itens lexicos e converte o campo util de cada celula 
    para um valor como descrito a seguir. 

    Nessa conversao, o campo 'util' de cada celula recebe um valor 
    da seguinte maneira.

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um string que representa um float (FLOAT_STR), 
         o campo 'vFloat' deve recebe o valor desse float;

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um operador, o campo 'prec' deve receber a precedencia
         desse operador.
 
         Para isto utilize o vetor 'precedencia'declarado antes 
         desta funcao. 

	 Nesta funcao voce pode utilizar qualquer funcao da biblioteca
         string do C, como, por exemplo, atof().

   Esta funcao _nao_ deve alocar celula alguma, no entanto ela
   deve dar free nas estruturas que deixarem de ser necessarias.

*/

void
itensParaValores(CelUtil *iniFilaItens)
{
	CelUtil *p;
    float aux;

    p = iniFilaItens->prox;

    while(p != NULL)
    {
        if(p->classe==FLOAT_STR)
        {
            aux = atof(p->pStr);
            free(p->pStr);
            p->vFloat = aux;
            p->classe = FLOAT;
        }

        else if (p->classe <= 17)
        {
            p->prec = precedencia[p->classe];
        }

        p = p->prox;
    }

}


/*-------------------------------------------------------------
  eval(iniPosfixa, mostrePilhaExecucao)
  
  Recebe uma lista ligada como cabeca iniPosfixa que representa
  uma expressao em notacao posfixa. 
  
  A funcao percorre a expressao calculando os valores resultantes.
  Para isto e utilizada uma pilha de execucao. 
  
  A pilha de execucao e representada atraves de uma lista ligada
  com cabeca em que cada elemento e do tipo CelUtil.
  
  Ao final a funcao retorna o endereco da celula no p1 da 
  pilha de execucao.
  
  O parametro mostrePilhaExecucao indica se os valores
  na pilha devem ser exibidos depois de qualquer alteracao na
  pilha de execucao.
  
  Esta funcao, ou qualquer funcao chamada por ela,
  pode alocar __no maximo__ uma celula CelUtil para ser a 
  cabeca da pilha. Isto pode ser particularmente util
  para aqueles que desejarem escrever um interface e biblioteca 
  como stack.h e stack.c feitas na aula
  desta semana.  

  Esta funcao deve dar free nas estruturas que deixarem de ser necessarias.
*/

CelUtil *
eval (CelUtil *iniPosfixa, Bool mostrePilhaExecucao)
{
	CelUtil *p, *p2, *p1, *stack;
	char* var;
	float aux;

	stack = mallocSafe( sizeof(CelUtil));
	stack->prox = NULL;

	p = iniPosfixa->prox;

	while(p != NULL)
	{

		if(p->classe == FLOAT || p->classe == ID_STR)
		{
			p1 = p;	
			p = p->prox;	
			stackPush(stack, p1);
		}
		
		/*-------------------------------------------------------------*/
		/* IGUAL (==) */
		/*-------------------------------------------------------------*/
		else if(p->classe == OPER_IGUAL)
		{

			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat == p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_DIFERENTE)
		{
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat != p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_MAIOR_IGUAL)
		{
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat >= p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_MENOR_IGUAL){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat <= p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_MAIOR){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat > p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_MENOR){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat < p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_EXPONENCIACAO){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = pow(p1->vFloat, p2->vFloat);
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_RESTO_DIVISAO){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = fmod(p1->vFloat, p2->vFloat);
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_MULTIPLICACAO){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat * p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_DIVISAO){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat / p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_ADICAO){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat + p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_SUBTRACAO){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat - p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_MENOS_UNARIO)
		{
			p1 = stackTop(stack);

			if(p1->classe == ID_STR)
			{ 
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat*(-1);

			p = p->prox;
		}
		else if(p->classe == OPER_LOGICO_AND){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat && p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_LOGICO_OR){
			p2 = stackPop(stack);
			p1 = stackPop(stack);	
			
			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}	
			
			if(p1->classe == ID_STR)
			{
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat = p1->vFloat || p2->vFloat;
			stackPush(stack, p1);
			freeUtil(p2);
			p = p->prox;
		}
		else if(p->classe == OPER_LOGICO_NOT)
		{
			p1 = stackTop(stack);

			if(p1->classe == ID_STR)
			{ 
				aux = getValorTS(p1->pNomeID);
				free(p1->pNomeID);
				p1->vFloat = aux;
				p1->classe = FLOAT;
			}

			p1->vFloat =  !p1->vFloat;

			p = p->prox;
		}
		else if(p->classe == OPER_ATRIBUICAO)
		{
			p2 = stackPop(stack);

			if(p2->classe == ID_STR)
			{
				aux = getValorTS(p2->pNomeID);
				free(p2->pNomeID);
				p2->vFloat = aux;
				p2->classe = FLOAT;
			}

			p1 = stackTop(stack);
			
			if(p1->classe == ID_STR) 
				setValorTS(p1->pNomeID, p2->vFloat);

			freeUtil(p2);
					
			p = p->prox;
		}

		if(mostrePilhaExecucao) 
			mostreListaUtil(stack, PILHA);
		
	}
   
	 p1 = stackTop(stack);
	 if(p1->classe == ID_STR)
	 {		
			var = mallocSafe((strlen(p1->pNomeID)+1)*sizeof(char));
			strcpy(var, p1->pNomeID );

			free(p1->pNomeID);

			p1->vFloat = getValorTS(var);
			p1->classe = FLOAT;
	}

    return p1; 
}
