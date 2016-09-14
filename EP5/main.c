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

  IMDB: main.c 


  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

  \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


#include <stdio.h>  /* printf(), scanf() */ 
#include <stdlib.h> /*exit(), EXIT_SUCCESS, EXIT_FAILURE*/
#include <time.h>   /* CLOCKS_PER_SECOND */
#include <string.h> /*strlen()*/

#include "main.h"

/* crieListaFilmes(), crieFilme(), inseraFilme(),  mergeSortFilmes() */
#include "filmes.h" 

/* carregueListaFilmes(), graveListaFilmes(), mostreFilme(), mostreListaFilmes() */
#include "iofilmes.h" 

#include "utils.h"    /* mallocSafe(), leiaString() */



/*------------------------------------------------------------------- 
  P R O T O T I P O S 
*/

/* A funcao leiaOpcao so e usada neste arquivo. */
static char  leiaOpcao(); 


/*------------------------------------------------------------------- 
    M A I N 
*/
int 
main(int argc, char *argv[])
{
    ListaFilmes *lst = crieListaFilmes(); 
    char         opcao;
    clock_t start, end; /* usadas para medir tempo de processamento */
    double elapsed;
    /* declaracao das demais variaveis do main */

    /*-----------------------------------------------------*/
    /* iterara ate o usuario digitar 'x' para sair         */
    do 
    { 

   opcao = leiaOpcao();

   /* comeca a cronometrar */
   start = clock(); 

   switch (opcao) 
   {
       /*---------------------------------------------*/
   case CARREGAR:
   {
       carregueListaFilmes(lst);
       break;
   }  
       /*---------------------------------------------*/
   case GRAVAR:
   {
       graveListaFilmes(lst);
       break;
   }

       /*---------------------------------------------*/
   case PROCURAR:
   {
       /* @TO-DO */ 
       break;
   }
       /*---------------------------------------------*/
   case INSERIR:
   {
       Filme       *flm = NULL;      

       char  dist[TAM_DIST+1];  
       int   votos;             
       float nota;              
       char  nome[TAM_STR+1];   
       int   ano;               

       printf("Digite o nome do filme: ");
       leiaString(nome, TAM_STR);

       printf("Digite o ano: ");
       scanf("%d", &ano);

       printf("Digite a nota: ");
       scanf("%f", &nota);

       printf("Digite o numero de votos: "); 
       scanf("%d", &votos);

       printf("Digite a distribuicao: ");
       leiaString(dist, TAM_DIST+1);
   
       flm = crieFilme(dist, votos, nota, nome, ano);
       mostreFilme(flm);

       insiraFilme(lst, flm); 
       /* completar essa opcao */
       break;
   }

       /*---------------------------------------------*/
   case REMOVER:
   {
	   /* TO-DO */
       break;
   }

             /*---------------------------------------------*/
   case ORDENAR_NOTA_M:
   {
       mergeSortFilmes(lst, NOTA);
       break;
   }

             /*---------------------------------------------*/
   case ORDENAR_NOME_M:
   {
       mergeSortFilmes(lst, NOME);
       break;
   }

             /*---------------------------------------------*/
   case ORDENAR_NOTA_Q:
   {
      quickSortFilmes(lst, NOTA); 
      break;
   }

             /*---------------------------------------------*/
   case ORDENAR_NOME_Q:
   {
       quickSortFilmes(lst, NOME);
       break;
   }

       /*---------------------------------------------*/
   case MOSTRAR:
   {
       mostreListaFilmes(lst); 
       break;
   }

       /*---------------------------------------------*/
   case MOSTRAR_MENOR:
   {
       mergeSortFilmes(lst, NOTA);
       mostreMelhoresFilmes(lst);
       break;
   }

       /*---------------------------------------------*/
   case MOSTRAR_MAIOR:
   {
       mergeSortFilmes(lst, NOTA);
       mostrePioresFilmes(lst);
       break;
   }
      
       /*---------------------------------------------*/
   case LIMPAR:
   {
       libereListaFilmes(lst);
       break;
   }

             /*---------------------------------------------*/
   case SAIR:
   {
       break;
   }

   default :
   {
       printf("main: opcao '%c' nao reconhecida\n", opcao);
       break;
   }
   
   } /* switch */
   
   /* trava o cronometro */  
   end = clock();
   
   /* calcula o tempo */
   elapsed = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("\n(%g segundos)\n", elapsed);
    } 
    while (opcao != SAIR);
    libereListaFilmes(lst);
    free(lst->cab);
    free(lst);

    return 0;
}


/*---------------------------------------------------------------------
  leiaOpcao()
   
  Le e retorna o caractere correspondente a opcao do usuario.
*/

char 
leiaOpcao()
{
    char opcao;

    printf(
   "\n================================================"
   "======================\n"
   "  (c) carregar um arquivo de dados\n"
   "  (g) gravar a lista atual em um arquivo\n"
   "  (p) procurar a nota de um filme\n"
   "  (i) inserir um filme\n"
   "  (r) remover um filme\n"
   "  (o) ordenar a lista de filmes por nota (mergeSort)\n"
   "  (O) ordenar a lista de filmes por nome (mergeSort)\n"
   "  (q) ordenar a lista de filmes por nota (quickSort, opcional)\n"
   "  (Q) ordenar a lista de filmes por nome (quickSort, opcional)\n"
   "  (m) mostrar todos os filmes\n"
   );

    printf(
   "  (<) mostrar N filmes com nota _menor_ que X e pelo menos V votos\n"
   "  (>) mostrar N filmes com nota _maior_ que X e pelo menos V votos\n"
   "  (l) limpar a lista de filmes\n"
   "  (x) sair do programa\n\n"
   );
    printf("Digite uma opcao: ");
    scanf(" %c", &opcao);

  /* main.c: warning: string length ‘679’ is greater than the length 
     ‘509’ ISO C90 compilers are required to support 
     [-Woverlength-strings] */

    return opcao;
}
