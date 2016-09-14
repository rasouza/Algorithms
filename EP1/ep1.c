/***************************************************************/
/**                                                           **/
/**   Rodrigo Alves Souza                           6800149   **/
/**   Exercício-Programa 1                                    **/
/**                                                           **/
/***************************************************************/

#include <stdio.h>  /* scanf, printf,  ... */
#include <stdlib.h> /* srand, rand,    ... */
#include <string.h> /* strlen, strcmp, ... */  

/*---------------------------------------------------------------*/
/* 
 * 0. C O N S T A N T E S 
 */

/* tamanho máximo de um tdorm */
#define MAX      128

#define ACORDADO  '#'
#define DORMINDO  ' '
#define TAPINHA   'T'

#define TRUE  1
#define FALSE 0

#define ENTER  '\n'
#define FIM    '\0'
#define ESPACO ' '


/*---------------------------------------------------------------*/
/*
 * 1. P R O T Ó T I P O S
 */

/* PARTE I */

void
leiaTurtledorm(int *n, int tdorm[MAX][MAX]);

void 
mostreTurtledorm(int n, int tdorm[][MAX], char c);

void
atualizeTurtledorm(int n, int tdorm[][MAX], int lin, int col);

int 
todosDormindo(int n, int tdorm[][MAX]);

int
graveTurtledorm(int n, int tdorm[][MAX]);

/* PARTE II */

void
sorteieTurtledorm(int *n, int tdorm[][MAX]);

int
graveTurtledorm(int n, int tdorm[][MAX]);

/* PARTE III */

void
resolvaTurtledorm(int n, int tdorm[][MAX]);

/* FUNÇõES AUXILIARES */
int 
randomInteger(int low, int high);

void
incremente(int bin[]);

/*---------------------------------------------------------------*/
/* 
 *  M A I N 
 */
int 
main(int argc, char *argv[])
{
	char action, strAction[MAX];
	int n, tdorm[MAX][MAX], lin, col, jogadas = 0;

	/* Questionario inicial do jogo */

	printf("(s)ortear ou (l)er um turtledorm de arquivo: ");
	fgets(strAction, sizeof(strAction), stdin);
	sscanf(strAction,"%c", &action);
	

	/* Verifica a acao a ser feita */
	if (action == 'l')
		leiaTurtledorm(&n, tdorm);	
	else if (action == 's')
		sorteieTurtledorm(&n, tdorm);

	printf("\nTurtledorm inicial\n");
	mostreTurtledorm(n, tdorm, '#');
	printf("\nUma jogada e definida por 2 numeros inteiros entre 1 e %d\n", n);

	/* INICIO DO JOGO */
	while(!todosDormindo(n, tdorm))
	{
		printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
		printf("\nDigite 'd' para desistir");
		printf("\nDigite 'a' para receber (a)juda para encontrar uma solução");
		printf("\nDigite 'g' para (g)ravar o estado atual do Turtledorm");
		printf("\nOu digite a posição lin, col para dar um tapinha: ");
		fgets(strAction, sizeof(strAction), stdin);

		/* Joga a coordenada */
		if (sscanf(strAction, "%d %d", &lin, &col) == 2)
		{
			printf("Sua jogada foi na posicao (%d, %d)\n", lin, col);
			atualizeTurtledorm(n, tdorm, lin-1, col-1);
			jogadas++;
			printf("\nTurtledorm apos jogada %d:\n", jogadas);
			mostreTurtledorm(n, tdorm, '#');
			
		}
		/* Executa o comando */
		else if (sscanf(strAction, "%c", &action) == 1)
		{
			switch(action)
			{
				case 'g':
					graveTurtledorm(n, tdorm);
					printf("\nTurtledorm gravado com sucesso!\n");
				break;

				case 'a':
					resolvaTurtledorm(n, tdorm);
				break;

				case 'd':
					printf("\nDessa vez nao deu.\nVoce fez %d jogadas.\nMais sorte na proxima!\n\n", jogadas);
					return EXIT_SUCCESS;
				break;

				default:
					printf("\nComando nao reconhecido. Tente novamente\n");
				break;
			}
		}
	}

	printf("\nParabens! Voce conseguiu resolver apos %d jogadas.\n\n", jogadas);

	return EXIT_SUCCESS;
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                       P A R T E   I 
 */
void leiaTurtledorm(int *n, int tdorm[][MAX])
{
	int i, j;
	char fileName[MAX]; /* Uso da constante MAX apenas por convencao */
	FILE *file;

	printf("Digite o nome do arquivo: ");
	fgets(fileName, sizeof(fileName), stdin);
	sscanf(fileName, "%s\n", fileName);

	/* Le a matriz que esta no arquivo indicado pelo usuario */
	file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("Arquivo nao existe!\n");
		exit(EXIT_FAILURE);
	}
	fscanf(file, "%d", n);
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *n; j++)
		{
			fscanf(file, "%d", &tdorm[i][j]);
		}
	}
	fclose(file);
}

void mostreTurtledorm(int n, int tdorm[][MAX], char c)
{
	int j, i;

	printf("\n");

	/* Imprime a primeira linha de coordenadas horizontais */
	for (j = 0; j <= n; j++)
	{
		if (j == 0)
			printf("     |");
		else
			printf("   %d   |", j);
	}
	printf("\n");
	/* Imprime as entrelinhas */
	for(j = 0; j <= n; j++)
	{
		if (j == 0)
			printf("-----+");
		else
			printf("-------+");
	}

	for (i = 0; i < n; i++)
	{

		printf("\n");	
		
		/* Printa o estado de cada Turtle */
		for (j = 0; j < n; j++)
		{
			if (j == 0)
				printf("  %d  |", i+1); /* Número da linha */

			printf("   %c   |", tdorm[i][j]?c:' '); /* Estado de cada Turtle */
		}
		
		printf("\n");

		/* Imprime as entrelinhas */
		for(j = 0; j <= n; j++)
		{
			if (j == 0)
				printf("-----+");
			else
				printf("-------+");
		}		
	}

	printf("\n");
}

void atualizeTurtledorm(int n, int tdorm[][MAX], int lin, int col)
{
	/* Tapa no Turtle */
	if (tdorm[lin][col] == 1)
		tdorm[lin][col] = 0;
	else
		tdorm[lin][col] = 1;

	/* Altera o estado do Turtle acima se possivel */
	if (lin > 0)
	{
		if (tdorm[lin-1][col] == 1)
			tdorm[lin-1][col] = 0;
		else
			tdorm[lin-1][col] = 1;
	}

	/* Altera o estado do Turtle da direita se possivel */
	if (col < n)
	{
		if (tdorm[lin][col+1] == 1)
			tdorm[lin][col+1] = 0;
		else
			tdorm[lin][col+1] = 1;
	}

	/* Altera o estado do Turtle abaixo se possivel */
	if (lin < n)
	{
		if (tdorm[lin+1][col] == 1)
			tdorm[lin+1][col] = 0;
		else
			tdorm[lin+1][col] = 1;
	}

	/* Altera o estado do Turtle da esquerda se possivel */
	if (col > 0)
	{
		if (tdorm[lin][col-1] == 1)
			tdorm[lin][col-1] = 0;
		else
			tdorm[lin][col-1] = 1;
	}
}

int todosDormindo(int n, int tdorm[][MAX])
{
	int i, j;

	/* Percorre a matriz inteira a procura de 1's */
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (tdorm[i][j] == 1)
				return FALSE;
		}
	}

	return TRUE;
}

int graveTurtledorm(int n, int tdorm[][MAX])
{
	int i, j;
	char fileName[MAX]; /* Uso da constante MAX apenas por convencao */
	FILE *file;

	printf("Digite o nome do arquivo: ");
	scanf("%s", fileName);
	while (getchar() != '\n');

	/* Grava a matriz indicada pelo usuario */
	file = fopen(fileName, "w");
	if (file == NULL)
	{
		printf("Houve algum erro ao tentar gravar o jogo\n");
		return EXIT_FAILURE;
	}
	fprintf(file, "%d\n", n);
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			fprintf(file, "%d ", tdorm[i][j]);
		}
		fprintf(file, "\n");
	}
	fclose(file);

	return EXIT_SUCCESS;
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                       P A R T E   II 
 */
void sorteieTurtledorm(int *n, int tdorm[][MAX])
{
	int seed, i, j, nTapinhas = 0, lin, col, turtleDespertos = 0;
	char dificuldade, strAction[MAX];

	printf("Qual o tamanho do turtledorm? ");
	fgets(strAction, sizeof(strAction), stdin);
	sscanf(strAction, "%d", n);

	printf("Qual a semente para sorteio? ");
	fgets(strAction, sizeof(strAction), stdin);
	sscanf(strAction, "%d", &seed);

	printf("Qual o nivel de dificuldate [f/m/d]? ");
	fgets(strAction, sizeof(strAction), stdin);
	sscanf(strAction, "%c", &dificuldade);

	/* SEMENTE */
	srand(seed);

	/* Inicializa TDORM com zeros */
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *n; j++)
			tdorm[i][j] = 0;
	}

	/* Sorteia o numero de tapinhas de acordo com a dificuldade */
	switch(dificuldade)
	{
		case 'f':
			nTapinhas = randomInteger((int)(0.05*(*n)*(*n)), (int)(0.2*(*n)*(*n)));
			break;

		case 'm':
			nTapinhas = randomInteger((int)(0.25*(*n)*(*n)), (int)(0.5*(*n)*(*n)));
			break;

		case 'd':
			nTapinhas = randomInteger((int)(0.55*(*n)*(*n)), (int)(0.85*(*n)*(*n)));
	}

	/* Sorteio de Tapinhas */
	for (i = 0; i < nTapinhas; i++)
	{
		lin = randomInteger(1, *n);
		col = randomInteger(1, *n);
		atualizeTurtledorm(*n, tdorm, lin-1, col-1);
	}

	/* Verifica quantos TURTLES estao despertos */
	for (i = 0; i < *n; i++)
	{
		for (j = 0; j < *n; j++)
		{
			if (tdorm[i][j] == 1)
				turtleDespertos++;
		}
	}

	printf("\nNumero de tapinhas sorteados foi: %d", nTapinhas);
	printf("\nNumero de turtles despertos e: %d\n", turtleDespertos);
}


/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                       P A R T E   III 
 */

/* 
 * Essa funccao utiliza o auxilio do programa tapinhas.c na pagina:
 * http://www.ime.usp.br/~coelho/mac0122-2013/ep1/esqueleto/tapinhas.c
 */  
void resolvaTurtledorm(int n, int tdorm[][MAX])
{
	int bin[MAX*MAX+1];     /* numeros binarios com n*n+1 bits */
	int nBits;              /* durante o programa nBits == n*n */
	int tapinhas[MAX][MAX]; /* representacao da lista de tapinhas e contador de tapinhas*/
	int contTapinhas = 0; /* Contador de tapinhas da iteracao atual */
	int nTapinhasMenor = MAX; /* Numero da solucao de menor tapinhas durante a iteracao */
	int tapinhasMenor[MAX][MAX]; /* Matriz com a solucao otima de taminhas */
	int temSolucao = 0; /* Flag que verifica se o jogo tem ou nao solucao */
	int i, j;
	int tdormOriginal[MAX][MAX]; /* Preserva o tdorm original */


	/* Inicializa o vetor bin com zeros */
	nBits = n*n;
	for(i = 0; i < nBits+1; i++)
		bin[i] = 0;

	/* Grava o tdorm original para ser usado em outras tentativas */
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) 
			tdormOriginal[i][j] = tdorm[i][j];

	while (bin[nBits] == 0)
	{
		/* transforme os n*n (== nBits-1) bits menos significativos de bin 
		 * em uma matriz n x n
		 */
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++) 
				tapinhas[i][j] = bin[i*n + j];

		/* Realiza tapinhas de acordo com a matriz tapinhas */
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{
				if (tapinhas[i][j] == 1)
				{
					atualizeTurtledorm(n, tdorm, i, j);
					contTapinhas++;
				}
			}
		}
			
		/* Verifica se a matriz tapinhas dada e uma solucao */
		if (todosDormindo(n, tdorm) == TRUE)
		{
			temSolucao = 1;

			/* Grava a solucao otima atual */
			if (contTapinhas < nTapinhasMenor)
			{
				nTapinhasMenor = contTapinhas;

				for (i = 0; i < n; i++)
					for (j = 0; j < n; j++)
						tapinhasMenor[i][j] = tapinhas[i][j];
			}
		}

		/* Proxima tentativa de tapinhas */
		incremente(bin);

		/* Reseta o tdorm e o contador de tapinhas*/
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++) 
				tdorm[i][j] = tdormOriginal[i][j];
		contTapinhas = 0;
	}

	if (temSolucao == 1)
	{
		printf("\nA solucao otima e de %d tapinhas:\n", nTapinhasMenor);
		mostreTurtledorm(n, tapinhasMenor, 'T');
	}
	else
		printf("Nao tem solucao\n");
}

/*---------------------------------------------------------------*/
/* 
 *  I M P L E M E N T A Ç Ã O   D A S   F U N Ç Õ E S   DA  
 *                     A U X I L I A R E S 
 */
int randomInteger( int low, int high)
{
    int k;
    double d;
    d = (double) rand( ) / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);
    return low + k;
}

/* 
 * incremente(bin)
 * 
 * Recebe atraves do vetor bin a representacao de um 
 * numero binario k e devolve em bin a representacao 
 * binaria de k+1.
 * 
 * Pre-condicao: a funcao nao se preocupa com overflow,
 *   ou seja, supoe que k+1 pode ser reprensentado em 
 *   bin.
 *
 * Essa funcao foi retirada do tapinhas.c na pagina:
 * http://www.ime.usp.br/~coelho/mac0122-2013/ep1/esqueleto/tapinhas.c
 */ 
void incremente(int bin[])
{
  int i;

  for (i = 0; bin[i] != 0; i++)
    bin[i] = 0;

  bin[i] = 1;
}