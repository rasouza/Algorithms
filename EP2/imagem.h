/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/**************************************************************** 

  Declaracoes das representacoes referentes a uma imagem:
     pixelGS, pixelRGB, ImageGS, ImagemRGB, CelPixel, CelRegiao,
 
  O prefixo 'Cel' indica a definicao de um elemento de um lista 
    ligada/encadeada.
 
  Aqui tambem estao os prototipos das funcoes que manipulam
  imagens:
    
****************************************************************/

#define _IMAGEM_H 

/*-------------------------------------------------------------*/
/* indices de uma cor */
#define RED   0
#define GREEN 1
#define BLUE  2

#define TRUE  1
#define FALSE 0

/* Byte assume valores entre 0 e 255 (8 bits) */
typedef unsigned char Byte;

typedef Byte Boolean;

/* Cor indica o nivel/intensidade da cor */
typedef Byte Cor;

/*-------------------------------------------------------------*/
/* pixel True Color */
/* http://en.wikipedia.org/wiki/True_Color#True_color_.2824-bit.29 */
typedef struct pixelRGB PixelRGB;
struct pixelRGB {
  Byte    red;         /* valor entre 0 e 255 */
  Byte    green;       /* valor entre 0 e 255 */
  Byte    blue;        /* valor entre 0 e 255*/
  Boolean visitado;    /* TRUE ou FALSE */ 
}; 

/*------------------------------------------------------------*/
/* representacao para uma imagem colorida */
typedef struct imagemRGB ImagemRGB;
struct imagemRGB {
  int  width;        /* numero de colunas (width/largura) da imagem em pixels */
  int height;        /* numero de linhas  (height/altura) da imagem em pixels */
  PixelRGB **pixel;  /* matriz height x width de pixels com os níveis RGB     */
}; 


/*-------------------------------------------------------------*/
/* celula de um lista de pixels */
typedef struct celPixel CelPixel;
struct celPixel { 
  int  w, h;         /* (h,w) eh a posicao do pixel */
  CelPixel *prox;    /* ponteiro para o proximo pixel */
};


/*-------------------------------------------------------------*/
/* celula de uma lista de regioes */
typedef struct celRegiao CelRegiao;
struct celRegiao {        
  int     nPixels; /* numero de pixels na regiao */
  CelPixel   *ini; /* ponteiro para a lista de pixels da regiao */
  Byte      cor[3]; /* cor dos pixels na regiao */
  CelRegiao *prox; /* ponteiro para a proxima regiao */   
};


/*-------------------------------------------------------------*/ 
/*  prototipos de funcoes */
 
ImagemRGB *
mallocImagemRGB(int width, int height);

void 
freeImagemRGB(ImagemRGB *img);

void 
freeRegioes(CelRegiao *listaRegioes);

PixelRGB
getPixelRGB(ImagemRGB *img, int w, int h);

void 
setPixelRGB(ImagemRGB *img, int w, int h, Byte cor[]);

void 
copieImagemRGB (ImagemRGB *destino, ImagemRGB *origem);

void 
pinteImagemRGB(ImagemRGB *img, Byte cor[]);

void 
pinteRegiaoRGB(ImagemRGB *img, CelPixel *pixel, Byte cor[]);

int 
pixelsRegiao(ImagemRGB *img, int w, int h, PixelRGB semente, CelPixel **ini);

CelRegiao * 
regioesImagem(ImagemRGB *img);

void
trocaCorRGB (ImagemRGB *img, CelRegiao *listaRegioes, Byte cor[3], Byte corNova[3]);
