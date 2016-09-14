/*
  NAO E' NECESSARIO EDITAR ESSE MODULO.
  ENTRETANTO VOCE PODE ALTERA-LO SE ACHAR CONVENIENTE.
*/

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

  Nome:

  main.c
  Pitao I

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

#include "lexer.h"  /* lexer(), freeFilaItens */
#include "eval.h"   /* itensParaValores(), eval() */
#include "util.h"   /* tipo Bool, tipo CelUtil */


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

    FILE *fEntrada   = stdin; 
    char *nomeScript = NULL; /* nome do modo com instrucoes a serem executadas
				 (default = ler do shell) *
			       */
    int nLinha   = -1;  

    /*-------------------------------------------------------------*/
    /* 1 pegue as opcoes da linha de comando */
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
    printf("MAC0122 2013 - EP3\n");
    printf("Pitao (%s, %s)\n", __DATE__, __TIME__);
    printf("[GCC %s] on %s\n", __VERSION__, SYSTEM);

    /* mostre o prompt se o modo e iterativo */
    if (modoInterativo)
    {
	printf(">>> "); /* prompt */
    }	   

    /*------------------------------------------------------------*/
    /* 4 interprete cada uma das linhas dadas */
    while (fgets(linha, MAX_TAMANHO, fEntrada) != NULL) 
    {
	/* 4.1 fila com a representacao de uma expressao posfixa */
	CelUtil *iniFila   = NULL; 
	CelUtil *resultado = NULL; 

	/* 4.2 contador de linhas, utilizado no modo script */
	int lenLinha  =  -1; /* valor absurdo */
    
	/* 4.3 pegue o comprimento da linha */
	lenLinha = strlen(linha) - 1; /* nao conta o '\n' */

	/* 4.4 substitua '\n' por '\0' */
	linha[lenLinha] = '\0'; 

	/* 4.5 imprima a linha */
	if (!modoInterativo)
	{
	    printf("Linha %d: %s\n", ++nLinha, linha);
	}

	/* 4.6 construa fila de itens lexicos e mostre os itens se
               o programa tiver sido chamado com a opcao "-l" */
	iniFila = crieFilaItens(linha);
	if (mostreItensLexicos)
	{
	    /* TAREFA: a funcao a seguir deve ser escrita
	       veja o modulo util.c */
	    mostreListaUtil(iniFila, ITEM_LEXICO);
	}
	
	/* 4.7 substitua os itens por valores */
	/* TAREFA: a funcao a seguir deve ser escrita
	   veja o modulo eval.c */
	itensParaValores(iniFila); 
	if (iniFila && mostreValores)
	{
	    /* TAREFA: a funcao a seguir deve ser escrita
	       veja o modulo util.c */
	    mostreListaUtil(iniFila, VALOR);
	}
	
	/* 4.8 calcule o valora da expressao posfixa */
	/* TAREFA: a funcao a seguir deve ser escrita
	   veja o modulo eval.c */
	resultado = eval(iniFila, mostrePilhaExecucao); 
	
	/* 4.9 mostre o resultado/valor da expressao */
	if (resultado)
	{ 
	    printf("Resultado: %f\n", resultado->vFloat);
	    freeUtil(resultado);
	}
	
	/* acho que essa pulada de linha e para algo ficar bonito */
	if (!modoInterativo)
	{
	    printf("\n");
	}
	
	/* 4.10 libere os itens da Fila */
	/* TAREFA: a funcao a seguir deve ser escrita
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
  fprintf(stderr,"%s: Uso \n"
	  "prompt> %s [-h] [-i | -s<nome-script> ] [-l] [-v]\n"
	  "    -h = mostra como usar o programa e abandona o programa\n"
	  "    -i = executa em modo interativo\n"

	  "    -s<nome-script> = calcula as expressões no arquivo <nome-script>\n"
	  "    -l = mostra fila de itens lexicos\n"
	  "    -v = mostra fila de valores\n"
	  "    -p = mostra a pilha de execucao apos cada operacao\n",
	  nomePrograma, nomePrograma);
  exit(EXIT_FAILURE);
}


