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

  posfixa.c
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
#include "posfixa.h"

#include "util.h"  /* tipo CelUtil, UtilUtil() */



/*-------------------------------------------------------------
    itensParaPosfixa(iniFilaInf)
    
    Recebe uma lista ligada com cabeca iniFilaInf representando uma 
    fila de itens de uma expressao infixa e retorna uma lista ligada 
    com cabeca contendo a fila que representacao a correspondente 
    expressao em notacao posfixa. 

    Nessa conversao, nenhuma celula nova deve ser criada a nao ser,
    possivelmente, a celula cabeca da notacao posfixa.  As demais 
    celulas devem simplesmente migrar da fila da notacao infixa 
    para a fila da notacao posfixa. 

    As celulas da notacao infixa que nao forem utilizadas na notacao 
    posfixa (abre e fecha parentese) devem ser liberadas (freeUtil).
*/

CelUtil *
infixaParaPosfixa (CelUtil *iniFilaInf)
{
	CelUtil *posfixa, *stack, *p, *aux, *morta, *topo;

	posfixa = mallocSafe(sizeof (CelUtil));
	posfixa->prox = NULL;
	stack = mallocSafe(sizeof (CelUtil));
	stack->prox = NULL;

	p = iniFilaInf->prox;

	while(p != NULL)
	{
		if (p->classe == FLOAT || p->classe == ID_STR)
		{
			aux = p;
			p = p->prox;
			queuePut(posfixa, aux);
		}
		else if (p->classe == ABRE_PARENTESES)
		{
				aux = p;
				p = p->prox;
				aux->prox = stack->prox;
				stack->prox = aux;
			
		}
		else if(p->classe == OPER_MENOS_UNARIO || p->classe == OPER_LOGICO_NOT || p->classe == OPER_EXPONENCIACAO || p->classe == OPER_ATRIBUICAO)
		{
				topo = stack->prox;
				while (topo != NULL && topo->classe != ABRE_PARENTESES && topo->prec > p->prec)
				{	
					aux = topo;
					topo = topo->prox;
					queuePut(posfixa, aux);
				}

				stack->prox = topo;
				aux = p;
				p = p->prox;
				aux->prox = stack->prox;
				stack->prox = aux;
		}
		else if(p->classe == FECHA_PARENTESES)
		{
			topo = stack->prox;
			while(topo != NULL && topo->classe != ABRE_PARENTESES)
			{
				aux = topo;
				topo = topo->prox;
				queuePut(posfixa, aux);
			}

			stack->prox = topo;

			morta = stack->prox;
			stack->prox = stack->prox->prox;

			freeUtil(morta);

			morta = p;
			p = p->prox;
			freeUtil(morta);

		}
		else
		{
				topo = stack->prox;
				while(topo != NULL && topo->classe != ABRE_PARENTESES && topo->prec >= p->prec)
				{
						aux = topo;
						topo = topo->prox;
						queuePut(posfixa, aux);	
				}

				stack->prox = topo;				
				aux = p;
				p = p->prox;
				aux->prox = stack->prox;
				stack->prox = aux;
		}
	}

	topo = stack->prox;
	while(topo != NULL)
	{
		aux = topo;
		topo = topo->prox;
		queuePut(posfixa, aux);
	}

	freeUtil(iniFilaInf);
	 
    return posfixa; 
}

void queuePut(CelUtil *queue, CelUtil *nova)
{
		CelUtil *p;

		if(queue->prox == NULL)
		{
			nova->prox = queue->prox;
			queue->prox = nova;
		}
		else
		{
			p = queue->prox;

			while(p->prox != NULL)		
				p = p->prox;

			nova->prox = p->prox;
			p->prox = nova;
		}
}
