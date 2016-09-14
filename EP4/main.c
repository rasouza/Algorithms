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

  main.c
  Pitao II

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

#include <stdio.h>   /* fprintf(), fgets(), printf() */
#include <stdlib.h>  /* exit(), EXIT_FAILURE */
#include <string.h>  /* strncmp */

#include "lexer.h"   /* lexer(), freeFilaItens */
#include "eval.h"    /* itensParaValores(), eval() */
#include "util.h"    /* tipo Bool, tipo CelUtil */
#include "posfixa.h" /* infixaParaPosfixa() */
#include "ts.h"      /* initTS(), showTS() e freeTS() */

#ifdef __linux__
#    define  SYSTEM "linux"
#elif  __FreeBSD__
#    define  SYSTEM "FreeBSD"
#elif __MACH__
#    define  SYSTEM "Mac OS X"
#elif __MSDOS__
#    define  SYSTEM "Windows"
#else
#    define  SYSTEM "nao sei o nome do SO..."
#endif

/*---------------------------------------------------------------*/
/* 
 *  C O N S T A N T E S 
 */

/* numero maximo de caracteres em um linha */
#define MAX_TAMANHO 128 

/*---------------------------------------------------------------*/
/*
 *  P R O T Ó T I P O S
 */

static void mostreUso (char *nomePrograma);

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */

int main(int argc, char *argv[])
{
    char *nomePrograma = argv[0];
    char linha[MAX_TAMANHO]; /* recebe linha do arquivo de entrada */
    
    /* opcoes de execucao e seus valores default */
    Bool modoInterativo      = TRUE;
    Bool mostreItensLexicos  = FALSE;
    Bool mostreValores       = FALSE;
    Bool mostrePilhaExecucao = FALSE;
    Bool mostreExpressao     = FALSE;
	 Bool mostreTabelaSimbolo = FALSE;

    FILE *fEntrada   = stdin; 
    char *nomeScript = NULL; /* nome do modo com instrucoes a serem executadas
				 (default = ler do shell) *
			       */
    int nLinha   = -1;  

    /*-------------------------------------------------------------*/
    /* 1 pegue as opcoes da linha de comando */
   /* TAREFA EP4: incluir as opcoes "-e" e "-t" */
    while (--argc) 
    {
	if      (!strncmp(argv[argc], "-h", 2)) mostreUso(argv[0]);
	else if (!strncmp(argv[argc], "-i", 2)) modoInterativo      = TRUE;
	else if (!strncmp(argv[argc], "-l", 2)) mostreItensLexicos  = TRUE;
	else if (!strncmp(argv[argc], "-v", 2)) mostreValores       = TRUE;
	else if (!strncmp(argv[argc], "-p", 2)) mostrePilhaExecucao = TRUE;
	else if (!strncmp(argv[argc], "-s", 2))
	
	{  /* teremos um arquivo com as instrucoes */
	    modoInterativo = FALSE;
	    nomeScript     = argv[argc]+2; 
	}
	else if(!strncmp(argv[argc],"-e",2)) mostreExpressao = TRUE;
	else if(!strncmp(argv[argc],"-t",2)) mostreTabelaSimbolo = TRUE;
	else 
	{ /* opcao invalida */
	    fprintf(stderr, "%s: opcao invalida '%s'\n", nomePrograma, argv[argc]); 
	    mostreUso(nomePrograma); 
	}	
    }

    /*-------------------------------------------------------------*/
    /* 2 verifique se ha um scritp a ser interpretado */
    if (!modoInterativo)
    {  
	fEntrada = fopen(nomeScript, "r");
	if (fEntrada == NULL) 
	{
	    printf("Nao consegui abrir o arquivo '%s'\n", nomeScript);
	    exit(EXIT_FAILURE);
	}
    }

    /*------------------------------------------------------------*/
    /* 3 imprima o cabecalho */
    printf("MAC0122 2013 - EP4\n");
    printf("Pitao (%s, %s)\n", __DATE__, __TIME__);
    printf("[GCC %s] on %s\n", __VERSION__, SYSTEM);

    /* mostre o prompt se o modo e iterativo */
    if (modoInterativo)
    {
	printf(">>> "); /* prompt */
    }	   

    /*------------------------------------------------------------*/
    /* 4 crie a tabela de simbolos                                */
    /* TAREFA EP4 */
		initTS();
    /*------------------------------------------------------------*/
    /* 5 interprete cada uma das linhas dadas */
    while (fgets(linha, MAX_TAMANHO, fEntrada) != NULL) 
    {
	/* 5.1 fila com a representacao de uma expressao posfixa */
	CelUtil *iniFila   = NULL; 
	CelUtil *resultado = NULL; 

	/* 5.2 contador de linhas, utilizado no modo script */
	int lenLinha  =  -1; /* valor absurdo */
    
	/* 5.3 pegue o comprimento da linha */
	lenLinha = strlen(linha) - 1; /* nao conta o '\n' */

	/* 5.4 substitua '\n' por '\0' */
	linha[lenLinha] = '\0'; 

	/* 5.5 imprima a linha */
	if (!modoInterativo)
	{
	    printf("Linha %d: %s\n", ++nLinha, linha);
	}

	/* 5.6 construa fila de itens lexicos e mostre os itens se
               o programa tiver sido chamado com a opcao "-l" */
	iniFila = crieFilaItens(linha);
	if (mostreItensLexicos)
	{
	    /* TAREFA EP3: a funcao a seguir deve ser escrita
	       veja o modulo util.c */
	    mostreListaUtil(iniFila, ITEM_LEXICO);
	}
	
	/* 5.7 substitua os itens por valores */
	/* TAREFA EP3: a funcao a seguir deve ser escrita
	   veja o modulo eval.c */
	itensParaValores(iniFila); 
	if (iniFila && mostreValores)
	{
	    /* TAREFA EP3: a funcao a seguir deve ser escrita
	       veja o modulo util.c */
	    mostreListaUtil(iniFila, VALOR);
	}

        /* 5.8 transforme a expressao para a notacao posfixa */ /*EP4*/
        /* TAREFA EP4 */
	iniFila = infixaParaPosfixa(iniFila);

	if(mostreExpressao){
		mostreListaUtil(iniFila, POSFIXA);
		printf("\n");
	}
		/* 5.9 calcule o valor da expressao posfixa */
	/* TAREFA EP3: a funcao a seguir deve ser escrita
	   veja o modulo eval.c */
        /* TAREFA EP4: a funcao a seguir deve ser adaptada para tratar
           atribuicao e variaveis */
	resultado = eval(iniFila, mostrePilhaExecucao); 
	/* 5.10 mostre o resultado/valor da expressao */
	if (resultado)
	{ 
	    /* printf("Resultado: %g\n", resultado->vFloat); */
       printf("%g\n", resultado->vFloat); 
		 /*o free abaixo nao e necessario no meu algoritmo, portanto, o comentei*/
	   /* freeUtil(resultado);*/
	}
	   
	/* acho que essa pulada de linha e para algo ficar bonito */
	if (!modoInterativo)
	{
	    printf("\n");
	}

	/* 5.11 mostre a tabela de simbolos, opcao "-t" */
        /* TAREFA EP4 */	
   if(mostreTabelaSimbolo) showTS();	
	/* 5.12 libere os itens da Fila */
	/* TAREFA EP3: a funcao a seguir deve ser escrita
	   veja o modulo util.c */
	freeListaUtil(iniFila); /* idealmente so vai liberar a cabeca */
	if (modoInterativo)
	{
	    printf(">>> "); /* prompt */
	}	   
    }

    if (modoInterativo)
    {
	printf("\n"); 
    }

    /*------------------------------------------------------------*/
    /* 6 libere a tabela de simbolos                              */
    /* TAREFA EP4 */
	 freeTS();
    fclose(fEntrada);

    return EXIT_SUCCESS;
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                     A U X I L I A R E S 
 */

static void 
mostreUso (char *nomePrograma)
{
    /* TAREFA EP4: incluir as opcoes "-e" e "-t" na mensagem */
    fprintf(stderr,"%s: Uso \n"
	    "prompt> %s [-h] [-i | -s<nome-script> ] [-l] [-v] [-p] [-e] [-t]\n"
	    "    -h = mostra como usar o programa e abandona o programa\n"
	    "    -i = executa em modo (i)nterativo\n"
	    "    -s<nome-script> = calcula as expressões no arquivo <nome-script>\n"
	    "    -l = mostra fila de itens (l)exicos\n"
	    "    -v = mostra fila de (v)alores\n"
	    "    -p = mostra a (p)ilha de execucao apos cada operacao\n"
		"    -e = mostra a (e)xpressao na notacao posfixa\n"
		"    -t = mostra a (t)abela de simbolos\n"

	    ,nomePrograma, nomePrograma);
    exit(EXIT_FAILURE);
}


