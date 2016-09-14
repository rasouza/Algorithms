/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO

  As declaracoes da funcao responsavel pela analise lexica e
  a abreviatura 'item' estao neste arquivo.
  
*/

#ifndef _LEXER_H
#define _LEXER_H

#include "util.h"    /* tipo CelUtil */



/*------------------------------------------------------------*/
/* abreviatura para nos referenciarmos a um item lexico       */
#define item util.ponteiroStr


/*-------------------------------------------------------------*/ 
/*  prototipos de funcoes                                      */

CelUtil *crieFilaItens (char linha[]);

/*-------------------------------------------------------------
  mostreFilaItens(iniFila)

  Recebe uma lista ligada ini como cabeca que representa
  uma fila de itens lexicos e imprime todos os itens da
  lista.

*/ 

#define mostreFilaItens(iniFila) mostreListaUtil(iniFila, ITEM_LEXICO)

#define freeFilaItens(iniFila)   freeListaUtil(iniFila)

#endif /* _LEXER_H */ 
