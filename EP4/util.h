/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO

  Aqui estao declarodos os tipos 

       Util e CelUtil 

  que sao usados em todos os modulo.
  Alem disso, aqui estao o prototipo da funcao mallocSafe e os
  prototipos de funcoes basicas para mostrar e leiberar a área 
  de objetos do tipo CelUtil. 
  
*/

#ifndef _UTIL_H
#define _UTIL_H

/*-------------------------------------------------------------*/
#include <stdio.h> /* size_t, fprintf() */

/*-------------------------------------------------------------*/
#include "classes.h" /* tipo Classe */

/*-------------------------------------------------------------*/
#define ITEM_LEXICO   0
#define VALOR         1
#define PILHA         2
#define SIMBOLO       3

/*EP4*/
#define POSFIXA       4

/*-------------------------------------------------------------*/ 
#define ERRO(msg)  fprintf(stderr,"ERRO: %s\n", #msg)
#define AVISO(msg) fprintf(stdout,"AVISO: %s\n", #msg)

/*---------------------------------------------------------------*/
enum bool 
{
    FALSE,
    TRUE
};
typedef enum bool Bool;

typedef struct celUtil CelUtil;

/*---------------------------------------------------------------*/
/* Uma variavel do tipo Util e de uso geral.
   Podem conter 
      - um inteiro ('valorInt' = valor int) ou
      - um float   ('valorFloat' = valor float) ou
      - um ponteiro para um string (ponteiroStr = ponteiro para string)
*/
union util 
{
    /* para classes OPER_*, valor int   */
    int    valorInt;    
    
    /* para classe FLOAT, valor float */ 
    float  valorFloat;  
    
    /* para classes  FLOAT_STR,... ponteiro para a string */
    char   *ponteiroStr;    
};
typedef union util Util;

/*--------------------------------------------------------------*/
/* CelUtil e o tipo da celula utilizada para representar
   todas as listas neste EP (filas ou pilha) de objetos do 
   tipo Util.

   O campo 'classe' indica o tipo (int, float, ponteiro para string) 
   e depende do objeto armazenado (constante, operador, ...)
*/

struct celUtil 
{
    Classe    classe; /* classe a qual o objeto pertence */
    Util      util;   /* representacao de um valor: int, float, ...*/
    CelUtil  *prox;   /* proxima celula */	
};



/*--------------------------------------------------------------*/
/* as macros a seguir torna mais conveniente e mais claro 
   (esperasse...) o acesso aos campos do tipo Util.
*/

#define vFloat       util.valorFloat
#define pStr         util.ponteiroStr

/* nome identificador */   
#define pNomeID      util.ponteiroStr   

/* precedencia */
#define prec         util.valorInt  

/* item lexico */    
#define item         util.ponteiroStr
 
/*---------------------------------------------------------------*/
/* prototipo de funcoes */

void *mallocSafe (size_t nbytes);

void  mostreUtil (CelUtil *pUtil, int tipo);

void  mostreListaUtil (CelUtil *iniLista, int tipoLista);

void  freeListaUtil (CelUtil *iniFila);

void  freeUtil(CelUtil *pUtil);
#endif /* util.h */

