/*
 * Definicao de cores das cores usadas no EP2 
 *
 * AUTOR: Carlos Hitoshi Morimoto
 *
 * http://en.wikipedia.org/wiki/List_of_colors_(compact)
 */ 

#ifndef _IMAGEM_H
# define _IMAGEM_H
/* tipos e prototipos de funcoes que manipulam imagens */
# include "imagem.h" /* declaracao de Byte */
#endif  /* _IMAGEM_H */

/* numero de cores na tabela menos 1 (tiramos a cor de fundo da jogada)*/
#define NUM_CORES 32 

/* a cor de fundo e branco */
#define BACK_GROUND    CORES[NUM_CORES] 


/* C O R E S */
Byte CORES[NUM_CORES+1][3]=
{
  { 255,    0,    0}, /*  0 red     i*/
  {   0,  255,    0}, /*  1 green   */
  {   0,    0,  255}, /*  2 blue    */
  { 255,  255,    0}, /*  3 yellow  */
  { 255,    0,  255}, /*  4 magenta */
  { 102,   51,  178}, /*  5 purple */
  {  51,  178,  102}, /*  6 green 2 */
  { 178,  102,   51}, /*  7 marrom  */
  {   0,  255,  255}, /*  8 cyan    */
  { 128,  128,  128}, /*  9 cinza   */
  {   0,    0,    0}, /* 10 black   */
  { 140,  190,  214}, /* 11 dark sky blue */
  { 255,  127,    0}, /* 12 orange  */
  { 255,  219,   88}, /* 13 mustard   */
  { 232,   97,    0}, /* 14 orange (g&s) */
  { 255,  168,   18}, /* 15 dark tangerine */
  { 155,   20,  147}, /* 16 deep pink */
  { 255,   40,    0}, /* 17 ferrari red */
  { 102,    2,   60}, /* 18 imperial purple */
  {   0,  168,  107}, /* 19 jade */
  { 191,  255,    0}, /* 20 lime */
  {  28,   53,   45}, /* 21 medium jungle */
  {  62,  180,  137}, /* 22 mint */
  { 155,  196,   12}, /* 23 mikado yellow */
  {   0,    0,  128}, /* 24 navy */
  {   0,   33,   71}, /* 25 oxford blue */ 
  {  50,   18,  122}, /* 26 persian indigo */
  { 204,   51,   51}, /* 27 persian red */
  { 233,    0,  255}, /* 28 phlox */
  {   0,   15,  137}, /* 29 phthalo blue */
  {  18,   53,   36}, /* 30 phthalo green */
  { 195,   11,   78}, /* 31 pictorial carmine */ 
  { 255,  255,  255}, /* 32 branco  */
};

