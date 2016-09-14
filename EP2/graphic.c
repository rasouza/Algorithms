/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/*
  Funcoes responsaveis pela parte grafica.
*/

#include <stdio.h>    /* fprintf, printf */
#include <stdlib.h>   /* exit */
#include <GL/glut.h>  /* funcoes do glut */

#include "cores.h"   /* definicao das cores */
#include "graphic.h" /* imagem.h, myInit */
#include "main.h"    /* graveImagemRGB, quit */

#undef DEBUG

/* 
 * Constantes
 */
/* canto da janela */
#define X0     100
#define Y0      50

/*-------------------------------------------------------------*/
/*
 * VARIAVEIS GLOBAIS: iniciam com o caractere '_' (underscore) 
 * 
 */

static ImagemRGB *_tela         = NULL;
static ImagemRGB *_imgOriginal  = NULL;
static CelRegiao *_listaRegioes = NULL;
static CelRegiao *_pRegiao      = NULL;
static int        _iCor;	  /* indice de uma cor no vetor CORES */  

/*-------------------------------------------------------------*/
/*
 * P R O T O T I P O S   D A    F U N C O E S   D A   P A R T E
 *                  G R A F I C A
 */

static void myReshape(int w, int h);

static void myKeyboard(unsigned char key, int x, int y);

static void myDisplay(void);

static void myMouse(int b, int s, int x, int y);

static void  mostreUso();

/*-------------------------------------------------------------*/
/* 
 *  F U N C O E S   A U X I L I A R E S
 *
 */

void 
myInit(int *argc, char *argv[], 
       ImagemRGB *tela, ImagemRGB *imgOriginal,
       CelRegiao *listaRegioes)
{
  _tela          = tela;
  _imgOriginal   = imgOriginal;
  _listaRegioes  = listaRegioes;
  _pRegiao       = _listaRegioes;
  _iCor           = 2; /* nada especial */

  /* GLUT */
  glutInit(argc, argv);

  /* inicialize o glut */
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

  /* crie uma janela */
  glutInitWindowSize (_tela->width, _tela->height);

 /* canto superior esquerdo da janela tem coordenada (X0,Y0) */ 
  glutInitWindowPosition(X0, Y0);

 /* desenhe a janela de nome EP2 MAC... */ 
  glutCreateWindow ("EP2 MAC0122 2013");

  /* 
   * registre as funções de callback 
   */
  glutKeyboardFunc(myKeyboard);
  glutReshapeFunc (myReshape);
  glutDisplayFunc (myDisplay);
  glutMouseFunc   (myMouse);

  /* mostre no shell as opcoes do programa */
  mostreUso();

  /* turn control over to glut */
  glutMainLoop();
}


/*-------------------------------------------------------------*/
/* 
 * F U N C O E S   P A R A   T R A T A R   O S   E V E N T O S 
 *
 *  CALLBACK == EVENT HANDLER
 */

/* *********************************************
   myReshape: funcao de callback
   Chamada quando a janela muda de tamanho       
*/

/* 
 * Chamada quando alguma tecla e pressionada
 */

void 
myKeyboard (unsigned char key, int mx, int my)
{
  switch (key)
    {
      /* ------------------------------------------------------------ */
    case 'q': /* quit */
    case 'Q':
      printf("\ngraphic: chamando a funcao quit.\n");
      quit(_tela, _imgOriginal, _listaRegioes);
      printf("\ngraphic: Hmmm sua funcao quit nao encerrou a execucao...\n");
      printf("            Eu mesmo vou terminar a execucao!\n");
      exit(EXIT_SUCCESS); 
      break; /* superfluo, nao chega aqui */ 

      /* ------------------------------------------------------------ */      
    case 'g': /* grave imagem corrente */
    case 'G':
      printf("\ngraphic: chamando a funcao graveImagemRGB.\n");
      graveImagemRGB(_tela);
      printf("\ngraphic: voltei da funcao graveImagemRGB.\n");
      break;

      /* ------------------------------------------------------------ */
    case 'l': /* limpa tela */
    case 'L':
      printf("\ngraphic: chamando a funcao pinteImagemRGB.\n");
      pinteImagemRGB(_tela, BACK_GROUND);
      printf("\ngraphic: voltei da funcao pinteImagemRGB.\n");
      myDisplay();
      break;

      /* ------------------------------------------------------------ */
    case 'o': /* pinta tela com imagem original */
    case 'O':
      printf("\ngraphic: chamando a funcao copieImagemRGB.\n");
      copieImagemRGB(_tela, _imgOriginal);
      printf("\ngraphic: voltei  da funcao copieImagemRGB.\n");
      myDisplay();
      break;


      /* ------------------------------------------------------------ */
    case 'r': /* mostra a 'proxima' regiao na tela */
    case 'R':
      if (_pRegiao == NULL)
	{ 
	  printf("\ngraphic: A lista de regioes chegou ao fim.\n");
	  _pRegiao = _listaRegioes;
	  printf("\ngraphic: Voltei ponteiro para inicio da lista.\n");
	}
      else
	{
	  CelPixel *pixel;
	  Byte cor[3];
	  
	  printf("\ngraphic: chamando a funcao pinteImagemRGB.\n");
	  pinteImagemRGB(_tela, BACK_GROUND);
	  printf("\ngraphic: voltei  da funcao pinteImagemRGB.\n");
	  
	  pixel = _pRegiao->ini;
	  if (pixel == NULL) 
	    {
	      printf("\ngraphic: encontrei um regiao vazia....\n");
	      break;
	    }
	  cor[RED]   = _imgOriginal->pixel[pixel->h][pixel->w].red;
	  cor[GREEN] = _imgOriginal->pixel[pixel->h][pixel->w].green;  
	  cor[BLUE]  = _imgOriginal->pixel[pixel->h][pixel->w].blue;
	  
	  printf("\ngraphic: chamando a funcao pinteRegiaoRGB.\n");
	  /* a cor da regiao for igual a do BACK_GROUND mudados de cor */
	  if (cor[RED]   == BACK_GROUND[RED] && 
	      cor[GREEN] == BACK_GROUND[GREEN] &&
	      cor[BLUE]  == BACK_GROUND[BLUE])
	    pinteRegiaoRGB(_tela, pixel, CORES[RED]);
	  else  
	    pinteRegiaoRGB(_tela, pixel, cor);
	  printf("\ngraphic: voltei da funcao pinteRegiaoRGB.\n");

	  myDisplay();

	  _pRegiao = _pRegiao->prox;
	}
      break;
 
    default:
      break;
    }

  
  if (key != '\n') /* este if evita que a mensagem fique "soluçando"... */
    { 
      mostreUso();
    }
}

/*-------------------------------------------------------------*/
/* 
 * chamada quando a janela precisa ser desenhada 
 */

void 
myDisplay(void)
{
  int w, h;
  GLubyte cor[3];

#ifdef DEBUG
  printf("Entrei myDisplay (%d,%d)\n",_tela->width, _tela->height);
#endif
  
  glBegin(GL_POINTS);
  for (h = 0; h < _tela->height; h++) 
    for (w = 0; w < _tela->width; w++) 
      {
	PixelRGB pixel = getPixelRGB(_tela, w, h);
	
	cor[RED]   = pixel.red;
	cor[GREEN] = pixel.green;
	cor[BLUE]  = pixel.blue;
	glColor3ubv(cor);

	glVertex2f(w, _tela->height-h-1);
    }
  glEnd();

  /* mostra o buffer */
  glutSwapBuffers(); 
}

/*-------------------------------------------------------------*/
/* 
 * Chamada quando ocorre um clique na janela
 */

static void 
myMouse(int b, int s, int w, int h)
{
  
  if (b == GLUT_LEFT_BUTTON /*  b indicates the button */
      && s == GLUT_DOWN) /* button pressed */
    {
      /* (w,h) sao as cordenadas na janela */
      PixelRGB  pixel;
      Byte     cor[3];

      printf("\ngraphic: chamando a funcao getPixelRGB.\n");
      pixel = getPixelRGB(_imgOriginal, w, h);
      printf("\ngraphic: voltei da funcao getPixelRGB.\n");

      cor[RED]   = pixel.red;
      cor[GREEN] = pixel.green;
      cor[BLUE]  = pixel.blue;
      _iCor = (_iCor+1) % NUM_CORES;

      printf("\ngraphic: chamando a funcao trocaCorRGB.\n");
      trocaCorRGB(_tela, _listaRegioes, cor, CORES[_iCor]); 
      printf("\ngraphic: voltei da funcao trocaCorRGB.\n");

      myDisplay();

      mostreUso();
    }
  
}


/*-------------------------------------------------------------*/
/* 
 * Chamada quando a janela muda de tamanho       
 */
static void 
myReshape(int w, int h)
{
#ifdef DEBUG
  printf("Entrei myReshape\n");
#endif

  glViewport (0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  /* map drawing area to viewport */
  gluOrtho2D(0, w, 0, h); 
  glMatrixMode(GL_MODELVIEW);

  /* request redisplay */
  glutPostRedisplay(); 
}



/*-------------------------------------------------------------*/
static void
mostreUso()
{
  fprintf(stdout, "\nTecle:  'r' para mostrar uma (r)egiao na tela\n");
  fprintf(stdout, "        'o' para mostrar a imagem (o)riginal na tela\n");
  fprintf(stdout, "        'l' para (l)impar a tela\n");
  fprintf(stdout, "        'g' para (g)ravar a imagem atual em um arquivo\n");
  fprintf(stdout, "        'q' para (q)uit, encerrar o programa.\n");
  fprintf(stdout, "Clique: em um pixel para alterar a cor\n"); 
}
