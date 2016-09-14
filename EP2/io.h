/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ARQUIVO
*/

/*
 * Interface para uso do modulo io.c 
 *
 */

#ifndef _IMAGEM_H
# define _IMAGEM_H

# include "imagem.h" /* tipos e prototipos de funcoes que manipulam imagens */
#endif /* _IMAGEM_H */

void 
graveImagemPPM(char *nomeArquivo, ImagemRGB *img);

ImagemRGB *
carregueImagemPPM(char *nomeArquivo);
