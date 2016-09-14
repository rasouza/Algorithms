/*
  Interface para as funcoes do main que sao chamadas 
  pelo modulo graphics quando ocorre um evento do teclado
  ou do mouse, ou seja,

       -  um caractere e teclado ou
       -  ha um clique do mouse 
*/

#ifndef _IMAGEM_H
# define _IMAGEM_H

# include "imagem.h" /* tipos e prototipos de funcoes que manipulam imagens */
#endif /* _IMAGEM_H */

void graveImagemRGB(ImagemRGB *img);

void quit (ImagemRGB *tela, ImagemRGB *img, CelRegiao *listaRegioes);
