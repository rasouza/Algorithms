/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO

  Aqui esta o prototipo da funcao 
     
          infixaParaPosfixa(inFilaInf)

  utilizada para converter um expressao da notacao infixa 
  para a notacao posfixa.
  
*/

#ifndef _POSFIXA_H
#define _POSFIXA_H

#include "util.h"

CelUtil *infixaParaPosfixa (CelUtil *iniFilaInf);
void queuePut(CelUtil *iniFila, CelUtil *nova);

#endif
