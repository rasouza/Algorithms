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

  Nome: Rodrigo Alves Souza
  NUSP: 6800149

  imagem.c

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:

  - função mallocSafe copiada de: 

       http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/


/*
   Funcoes que manipulam uma imagem:
*/

#include <stdio.h>  /* fprintf, printf */
#include <stdlib.h> /* malloc, free,  */
#include "imagem.h" /* Byte, ImagemRGB, CelPixel, CelRegiao ... */

/*-------------------------------------------------------------
  contantes 
*/
#define EXIT_FAILURE_MALLOC -1

/*-------------------------------------------------------------
  Funcoes auxiliares 
*/
static void *mallocSafe (size_t nbytes);

static Boolean coresIguaisByte(Byte cor1[], Byte cor2[]);

static Boolean coresIguaisPixel(PixelRGB pix1, PixelRGB pix2);

/*-------------------------------------------------------------
  mallocImagemRGB
  
  Recebe inteiros width e height e retorna a estrutura que representa
  uma imagem RGB com height linhas e width colunas (height x width pixels). 
  Cada pixel da imagem e do tipo PixelRGB.
   
  Esta funcao utiliza a funcao mallocSafe.
 */

ImagemRGB *
mallocImagemRGB(int width, int height)
{
  int i;
  ImagemRGB *imagem = (ImagemRGB*)mallocSafe(sizeof(ImagemRGB));

  /* Alocacao de HEIGHT linhas */
  imagem->pixel = (PixelRGB**)mallocSafe(height * sizeof(PixelRGB*));

  /* Alocacao de WIDTH colunas */
  for(i = 0; i < height; i++)
      imagem->pixel[i] = (PixelRGB*)mallocSafe(width * sizeof(PixelRGB));

  return imagem;

}


/*-------------------------------------------------------------
  freeImagemRGB
  
  Recebe um ponteiro img para um estrutura que representa uma 
  imagem RGB e libera a memoria utilizada.
  
  Esta funcao utiliza a funcao free.
 */

void
freeImagemRGB(ImagemRGB *img)
{
  int i;

  /* Processo inverso do malloc para matrizes dinamicas */
  for (i = 0; i < img->height; i++)
  {
    free(img->pixel[i]);
    img->pixel[i] = NULL;
  }

  free(img->pixel);
  img->pixel = NULL;
}


/*-------------------------------------------------------------
  freeImagemRGB
  
  Recebe um ponteiro listaRegioes para um lista de regioes
  e libera a memoria aloca para cada celula dessa lista.
  Tambem libera a memoria alocada para cada celula da lista 
  de pixels da regiao.

 */

void 
freeRegioes(CelRegiao *listaRegioes)
{
  CelRegiao* regiao;
  CelPixel* p;

  /* Libera cada celula de pixel antes de liberar cada regiao */
  for(regiao = listaRegioes; regiao != NULL; regiao = regiao->prox)
  {
    for(p = regiao->ini; p != NULL; p = p->prox)
      free(p);

    /* Libera a regiao depois de ter liberado todos os pixels dela */
    free(regiao);
  }
}

/*-------------------------------------------------------------
  getPixel

  Recebe um ponteiro img para uma estrutura que representa 
  uma imagem RGB e a posicao (x,y) de um pixel e retorna
  o valor do pixel (valor = representacao da cor do pixel).

 */

PixelRGB
getPixelRGB(ImagemRGB *img, int w, int h)
{
  return img->pixel[h][w];
}

/*-------------------------------------------------------------
  setPixel

  Recebe uma imagem img, uma posicao (h,w) de um pixel e uma cor.
  A funcao pinta o pixel da posicao (h,w) com a cor dada.

*/

void
setPixelRGB(ImagemRGB *img, int w, int h, Byte cor[])
{
  img->pixel[h][w].red = cor[RED];
  img->pixel[h][w].green = cor[GREEN];
  img->pixel[h][w].blue = cor[BLUE];
}

/*-------------------------------------------------------------
  pinteImagem

  Recebe uma imagem img e uma cor e pinta todos os pixels
  da imagem com a cor dada.

  Esta funcao deve utilizar a funcao setPixelRGB.
 */ 

void 
pinteImagemRGB(ImagemRGB *img, Byte cor[])
{
  int i, j;
  for(i = 0; i < img->height; i++)
    for(j = 0; j < img->width; j++)
      setPixelRGB(img, j, i, cor);
}


/*-------------------------------------------------------------
  pinteImagem

  Recebe uma imagem, um ponteiro para uma lista de pixels 
  (de uma regiao) e uma cor. A funcao pinta todos os pixels da 
  imagem com a cor dada.

  Esta funcao deve utilizar a funcao setPixelRGB.
 */ 

void 
pinteRegiaoRGB(ImagemRGB *img, CelPixel *pixel, Byte cor[])
{
  CelPixel *p;
  for(p = pixel; p != NULL; p = p->prox)
    setPixelRGB(img, p->w, p->h, cor);
}



/*-------------------------------------------------------------*/ 
/* copieImagemRGB 

   Copia a imagem *origem para a imagem *destino. 
   
   Suponha que a imagem *destino já foi criada, ou seja, a
   memória utilizada pela matriz já foi alocada.

*/

void 
copieImagemRGB (ImagemRGB *destino, ImagemRGB *origem)
{
  int i, j;
  /*destino->pixel = (PixelRGB**)mallocSafe(sizeof(PixelRGB) * origem->height * origem->width);*/

  /* Copia as dimensoes da imagem */
  destino->width = origem->width;
  destino->height = origem->height;

  /* Copia  cada pixel da imagem */
  for(i = 0; i < origem->height; i++)
    for(j = 0; j < origem->width; j++)
    {
      destino->pixel[i][j].red = origem->pixel[i][j].red;
      destino->pixel[i][j].green = origem->pixel[i][j].green;
      destino->pixel[i][j].blue = origem->pixel[i][j].blue;
    }
}

/*-------------------------------------------------------------*/ 
/*
  regioesImagem

  Recebe uma imagem img e cria e retorna um ponteiro para 
  o inicio de uma lista de regioes conexas da imagem.

  Cada uma dessas regioes conexas deve ser formada por pixels
  de uma mesma cor. 

  Cada celula da lista de regioes e do tipo CelRegiao e 
  contem um campo ini sera o ponteiro para o inicio da 
  lista de pixels que formam a regiao.
 
  Cada celula dessa lista de pixels e do tipo CelPixel.

  Esta funcao utiliza a funcao mallocSafe.
  Esta funcao deve utilizar a funcao pixelsRegiao que 
  cria e devolve a lista de pixels de cada regiao.

 */

CelRegiao *
regioesImagem(ImagemRGB *img)
{
  int i, j;
  /* Inicializa a lista ligada */
  CelRegiao *iniRegiao, *novaRegiao;
  iniRegiao = NULL;
  
  /* Varre por todos os pixels da imagem procurando regioes conexas */
  
  for(i = 0; i < img->height; i++)
    for(j = 0; j < img->width; j++)
    {
      /* Se o pixel ainda nao tiver sido visitado,
       entao temos uma nova regiao conexa */
      if (img->pixel[i][j].visitado != TRUE)
      {
        /* Cria a nova celula da Regiao*/
        novaRegiao = (CelRegiao*)mallocSafe(sizeof(CelRegiao));
        novaRegiao->cor[RED] = img->pixel[i][j].red;
        novaRegiao->cor[GREEN] = img->pixel[i][j].green;
        novaRegiao->cor[BLUE] = img->pixel[i][j].blue;
 
        /* Inicializa a lista de pixels */
        novaRegiao->ini = (CelPixel*)mallocSafe(sizeof(CelPixel));
        novaRegiao->ini = NULL;
        novaRegiao->nPixels = pixelsRegiao(img, j, i, img->pixel[i][j], &novaRegiao->ini);

        /* Liga a nova celula na lista encadeada */
        novaRegiao->prox = iniRegiao;
        iniRegiao = novaRegiao;
      }
    }

  return iniRegiao; 
}

/*-------------------------------------------------------------*/ 
/* pixelsRegiao

   Atencao: Esta funcao deve ser recursiva.

   Recebe 
    
       * uma imagem img, 
       * uma posicao (h,w) de um pixel, 
       * um  pixel semente e
       * um  ponteiro *pIni para de uma lista de pixels. 

   A funcao cria uma lista de pixels e devolve essa lista 
   atraves do parametros *pIni.

   Essa lista devolvida deve ser criada recursivamente 
   visitando-se 

        - os vizinhos do pixel da posicao (h,w) 
          que tem a mesma cor que o pixel semente 
          e ainda nao foram visitados 
	- os vizinhos dos vizinhos .... que tem 
          a mesma cor que a semente e ainda nao 
          foram visitados 
	- os vizinhos, dos vizinhos, dos vizinhos ...
        - ...

    Um pixel tem de 3 (os quatro pixels do canto) a 8 
    vizinhos (pixels do meio da imagem).

    A funcao ainda retorna o numero de pixels na lista 
    devolvida.

    Cada celula da lista de pixels e do tipo CelPixel.
 */
int
pixelsRegiao(ImagemRGB *img, int w, int h, 
	     PixelRGB semente, CelPixel **pIni)
{
  int n = 1;
  CelPixel *cpixel;

  /* Se o pixel estiver fora dos limites da imagem, não conta */
  if (w < 0 || w >= img->width || h < 0 || h >= img->height)
    return 0;

  /* Nao conta se o pixel ja tiver sido visitado */
  if (img->pixel[h][w].visitado == TRUE)
    return 0;

  /* Nao contar pixels que nao sao da mesma cor */
  if (coresIguaisPixel(img->pixel[h][w], semente) == FALSE)
    return 0;

  /* CASO AS CONDICOES ESTEJAM CORRETAS: */
  /* 1 - Visita o pixel */
  img->pixel[h][w].visitado = TRUE;

  /* 2 - Adiciona na lista */
  cpixel = (CelPixel*)mallocSafe(sizeof(CelPixel));
  cpixel->w = w;
  cpixel->h = h;
  cpixel->prox = *pIni;
  *pIni = cpixel;

  /* 3 - Verifica os vizinhos */
  n += pixelsRegiao(img, w, h-1, semente, pIni);
  n += pixelsRegiao(img, w, h+1, semente, pIni);
  n += pixelsRegiao(img, w+1, h-1, semente, pIni);
  n += pixelsRegiao(img, w+1, h, semente, pIni);
  n += pixelsRegiao(img, w+1, h+1, semente, pIni);
  n += pixelsRegiao(img, w-1, h-1, semente, pIni);
  n += pixelsRegiao(img, w-1, h, semente, pIni);    
  n += pixelsRegiao(img, w-1, h+1, semente, pIni);

  return n;
}
 
 
/*-------------------------------------------------------------*/ 
/* trocaCor

   Recebe uma imagem, a lista de regioes conexas e de mesma cor,
   uma cor antiga e uma cor nova. 

   A funcao pinta todos os pixels da imagem que tem a cor antiga 
   com a cor nova. 

   Para isto a funcao percorre a lista de regioes e para cada 
   regiao de pixels com a cor antiga percorre a lista de 
   pixels pintando-os com a cor nova.

   Esta funcao deve itilizar a funcao coresIguaisByte.
   Esta funcao deve utilizar a funcao pintaRegiaoRGB.
*/

void
trocaCorRGB (ImagemRGB *img, CelRegiao *listaRegioes, Byte cor[3], Byte corNova[3])
{
  CelRegiao *regiao;
  CelPixel *pixel;

  for(regiao = listaRegioes; regiao != NULL; regiao = regiao->prox)
    if(coresIguaisByte(regiao->cor, cor))
      for(pixel = regiao->ini; pixel != NULL; pixel = pixel->prox)
        pinteRegiaoRGB(img, pixel, corNova);

}


/* 
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    IMPLEMENTACAO DAS FUNCOES DADAS

////////////////////////////////////////////////////////////////////// 
*/

/*-------------------------------------------------------------*/ 
/* coresIguaisPixel

   Recebe dois pixels e retorna TRUE se eles tem a mesma cor 
   e FALSE em caso contrario.
*/
 
static Boolean
coresIguaisPixel(PixelRGB pix1, PixelRGB pix2)
{
  return pix1.red   == pix2.red
     &&  pix1.green == pix2.green
     &&  pix1.blue  == pix2.blue;   
} 


/*-------------------------------------------------------------*/ 
/* coresIguaisByte

   Recebe duas cores no formato de vetor de bytes retorna TRUE se 
   sao iguais e FALSE em caso contrario.
*/
 
static Boolean
coresIguaisByte(Byte cor1[], Byte cor2[])
{
  return cor1[RED]   == cor2[RED]
     &&  cor1[GREEN] == cor2[GREEN]
     &&  cor1[BLUE]  == cor2[BLUE];   
} 

/*-------------------------------------------------------------*/ 
/*  mallocSafe 

   O parâmetro de mallocSafe é do tipo size_t.  
   Em muitos computadores, size_t é equivalente a unsigned int.  
   A função mallocSafe não está em nenhuma biblioteca e é desconhecida 
   fora destas notas de aula. 
   Ela é apenas uma abreviatura conveniente.

   Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html
 */

static void 
*mallocSafe (size_t nbytes)
{
   void *ptr;

   ptr = malloc (nbytes);
   if (ptr == NULL) {
     fprintf (stderr, "Socorro! malloc devolveu NULL!\n");
     exit (EXIT_FAILURE_MALLOC);
   }

   return ptr;
}

