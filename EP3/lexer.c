/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO

  Este arquivo contem a funcao 

       crieFilaItens(linha)

  que e' responsavel pela analise lexica de cada linha 
  a ser interpretada.
*/

/*------------------------------------------------------------*/
/* interface para este modulo */
#include "lexer.h"  

/*------------------------------------------------------------*/
#include <stdlib.h> /* malloc(), free() */
#include <stdio.h>  /* printf(), fprintf() */
#include <string.h> /* strlen(), strchr(), strncmp() */
#include <ctype.h>  /* isdigit(), isalpha(), isalnum() */

/*------------------------------------------------------------*/
#include "util.h"     /* celUtil, mallocSafe(), ERRO(), AVISO() */
#include "classes.h"  /* tipo Classe */
/*-------------------------------------------------------------*/
/*
  http://en.wikipedia.org/wiki/ASCII

  \t  Horizontal Tab
  \n  Line feed
  \v  Vertical Tab
  \f  Form feed
  \r  Carriage return[g]

Whitespace characters: space, horizontal tab, vertical tab, form feed, newline
http://en.wikipedia.org/wiki/C_language
*/

static const char *whiteSpace = " \t\v\f\n";

/*-------------------------------------------------------------*/
/* Tabelas com operadores aritmeticos, relacionais, logicos 
   e constantes logicas
*/

/*-----------------------------------------------------------*/
/* tabela de operadores */

static char *operador[MAX_OPERADORES] =
{
    /* 4 operadores relacionais com 2 simbolos */
    "=="  /* "operador relacional igual" */ 
    ,"!="  /* "operador relacional diferente" */ 
    ,">="  /* "operador relacional maior ou igual" */ 
    ,"<="  /* "operador relacional menor ou igual" */ 
    
    /* 2 operadores relacionais com 1 simbolo */
    ,">"   /* "operador relacional maior" */ 
    ,"<"   /* "operador relacional menor" */ 
    
    /* 7 operadores aritmeticos */
    ,"^"  /* "operador exponenciacao" */  
    ,"%"  /* "operador resto de divisao" */ 
    ,"*"  /* "operador aritmetico multiplicacao" */ 
    ,"/"  /* "operador aritmetico divisao" */ 
    ,"+"  /* "operador aritmetico adicao" */ 
    ,"-"  /* "operador aritmetico subtracao" */ 
    ,"_"  /* "operador aritmetico \"menos unario\"" */
    
    /* 3 operadores logicos */
    ,"&&" /* "operador logico e "*/  
    ,"||" /* "operador logico ou"*/ 
    ,"!"  /* "operador logico negacao"*/ 
    
    /* atribuicao... */ 
    ,"="  /* "operador de atribuicao"*/ 
};


/*-------------------------------------------------------------
  crieFilaItens(linha)
  
  Recebe uma string linha e retorna uma fila com os itens lexicos 
  que formam a linha.

  A fila e implementada atraves de uma lista ligada COM CABECA 
  que contem os itens lexicos encontrados a medida que a linha 
  e examinada do inicio ao fim.

  Brancos (whitespaces) sao pulados a medida que varemos a linha 
  e nao fazem parte da lista de itens lexicos.

  Tudo encontrado a partir de um # e considerado um comentario 
  e sera ignorado.

  Apesar de supormos que as expressoes estao corretas o 
  a funcao retorna NULL se alguma problema for encontrado na linha.

*/

CelUtil *
crieFilaItens (char linha[])
{
    CelUtil *ini = NULL;
    CelUtil *fim = NULL;

    int i; /* indice para percorrer a linha */
    int n = strlen(linha); /* comprimento da linha */

    /* inicialmente a lista de item como vazia */
    /* ini e um ponteiro para a cabeca da fila */
    ini = mallocSafe(sizeof *ini); /* celula cabeca */
    ini->classe = INDEFINIDA; /* indefinida, pois e a celula cabeca */
    ini->item   = NULL;
    ini->prox   = NULL;
    fim = ini;

    i = 0;
    while (i < n) /* equivalente a (*linha != '\0') */
    {
        /* 1 verifique se *pLinha e o caractere de comentario */
	if (linha[i] == '#') 
	{  /* encontramos um comentario */
	    i = n; /* acabou o servico do analisador lexico */
	}

	/* 2 verifique se Linha[i] e um branco */
	else if (strchr(whiteSpace, linha[i])) 
	{   
	    i++; /* pule o branco */
	}

	/* encontramos um item lexico, so falta saber qual e'... */
	else
	{   
	    CelUtil *nova = mallocSafe(sizeof *nova);
	    int j;
	    
	    /* prencha a nova celula */
	    nova->classe = INDEFINIDA; /* indefinida por enquanto */
	    nova->item   = NULL;
	    nova->prox   = NULL;
	    
	    /* insira a nova celula no final da lista/fila */
	    fim->prox = nova;
	    fim       = nova;
	    
            /* 3 verifique se encontramos um numero */
	    if (isdigit(linha[i]) || linha[i] == '.') 
	    {
		/* encontramos um numero que, para simplificar, 
                   consideraremos como sendo float */
		nova->classe = FLOAT_STR;
		
                /* anda enquanto e digito */
		for (j = 0; linha[i+j] && isdigit(linha[i+j]); j++) ;
		
		if (linha[i+j] == '.') 
		{
		    /* anda sobre o resto do float */
		    for (j++; linha[i+j] && isdigit(linha[i+j]); j++) ;
		}
		
                if (isalpha(linha[i+j])) 
		{ 
		    /* Hmmm... esta estranho ... */
		    printf("    %s\n", linha);
		    for (j = 0; j < i-1; j++) printf(" ");
		    printf("    ^\n");
		    ERRO(SyntaxError: invalid syntax);
		    freeFilaItens(ini);
		    return NULL; /* abandonamos a linha */
		}
		
		nova->item = malloc((j+1) * sizeof(char));
		strncpy(nova->item, &linha[i], j);
		nova->item[j] = '\0';

		i += j;
	    }

	    /*beginfora*/
	    /* 4 verifique se encontramos um identificador */
	    else if (isalpha(linha[i])) 
	    {
		nova->classe = ID_STR;

		/* anda enquanto for uma letra ou digito */
		for (j = 0; linha[i+j] && isalnum(linha[i+j]); j++) ;

		nova->item = malloc((j+1) * sizeof(char));
		strncpy(nova->item, &linha[i], j);
		nova->item[j] = '\0';
		
		i += j;
	    }
	    /*endfora*/
	    /* 5 verifique se encontramos um operador aritmetico 
	       relacional ou logico
	    */
	    else
	    {
		/* 5.1 procure por linha[i..] na tabela de operadores */
		j = 0;
		while (j < MAX_OPERADORES 
		       && strncmp(&linha[i], operador[j], strlen(operador[j])))
		{
		    j++;
		}
	    
		/* 5.2 encontrou linha[i..] na tabela de operadores? */
		if (j < MAX_OPERADORES) 
		{   /* sim  encontramos um operador */
		    nova->classe = j;
		    nova->item   = operador[j];
		    
		    /* atualize o ponteiro para a linha */
		    i += strlen(operador[j]);
		}
		else
		{
		    /* Xiii, se chegou aqui teve algum problema */
		    printf("    %s\n", linha);
		    for (j = 0; j < i; j++) printf(" ");
		    printf("    ^\n");
		    ERRO(SyntaxError: invalid syntax);
		    freeFilaItens(ini);
		    return NULL; /* abandonamos a linha */
		}
	    }
	}
    }
    
    return ini;
}
    
