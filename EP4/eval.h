/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/**************************************************************** 

  Declaracoes das representacoes para referencias:

  Aqui tambem estao os prototipos das funcoes que manipulam
  a pilha de execucao. 
  
****************************************************************/

#ifndef _EVAL_H
#define _EVAL_H

#include "util.h"  /* tipo CelUtil */



/*-------------------------------------------------------------*/ 
/*  prototipos de funcoes e macros para funcoes                */

CelUtil *infixaParaPosfixa (CelUtil *iniFilaInf);

void itensParaValores (CelUtil *iniFila);

CelUtil *eval (CelUtil *iniPosfixa, Bool mostrePilhaExecucao);

void stackPush(CelUtil *iniPilha, CelUtil *nova);

CelUtil* stackPop(CelUtil *iniPilha);

CelUtil* stackTop(CelUtil *iniPilha);

void stackFree(CelUtil *iniPilha);
#define mostreValor(pValor)        mostreUtil(pValor, VALOR)

#define mostreFilaValores(iniFila) mostreListaUtil(iniFila, VALOR) 

#define freeValor(pValor)          freeUtil(pValor)

#define freeFilaValores(iniFila)   freeListaUtil(iniFila)

#endif /* _EVAL_H */
