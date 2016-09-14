/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO

  Neste arquivo esta a declaracao do tipo Classe alem de
  uma tabela com as constantes que representam as possiveis 
  classes dos itens lexicos.
*/


#ifndef _CLASSES_H
#define _CLASSES_H

/*-------------------------------------------------------------*/
/* 
   C O N S T A N T E S 
*/

#define MAX_OPERADORES 17 

/*---------------------------------------------------------------*/
/* temos 30 classes... deve dar e sobrar ... */

#define MAX_CLASSES    21

/* classe indefinida */
#define INDEFINIDA -1

enum classe 
{
    /* 4 operadores relacionais com 2 simbolos  */
     OPER_IGUAL          /* "==" */
    ,OPER_DIFERENTE      /* "!=" */
    ,OPER_MAIOR_IGUAL    /* ">=" */
    ,OPER_MENOR_IGUAL    /* "<=" */
    
    /* 2 operadores relacionais com 1 simbolo */
    ,OPER_MAIOR          /* ">"  */
    ,OPER_MENOR          /* "<"  */  
    
    /* 7 operadores aritmeticos  */
    ,OPER_EXPONENCIACAO  /* "^" */
    ,OPER_RESTO_DIVISAO  /* "%" */
    ,OPER_MULTIPLICACAO  /* "*" */
    ,OPER_DIVISAO        /* "/" */
    ,OPER_ADICAO         /* "+" */
    ,OPER_SUBTRACAO      /* "-" */ 
    ,OPER_MENOS_UNARIO   /* "_" */  
    
    /* 3 operadores logicos  */
    ,OPER_LOGICO_AND     /* "&&" */ 
    ,OPER_LOGICO_OR      /* "||" */
    ,OPER_LOGICO_NOT     /* "!" */
    
    /* atribuicao */ 
    ,OPER_ATRIBUICAO     /* "=" */ 
    
    /* constante */
    ,FLOAT_STR   /* um string representando um float */
    ,FLOAT       /* um float */
    
    /* identificador */ 
    ,ID_STR      /* nome do identificador */ 
    ,ID_PTR      /* ponteiro para o identificador */
};
/* warning: ISO C forbids forward references to ‘enum’ types [-pedantic] */
typedef enum classe Classe; 

#endif /* classes.h */
