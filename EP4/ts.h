/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO

  Aqui estao declarados o tipo CelTS e o prototipo da funcao 
     
          crieTS()
          enderecoVariavel(nomeID)

  que manipulam a tabela de simbolos.
  
*/

#ifndef _TS_H
#define _TS_H

#include "util.h" /* tipo Bool, tipo CelUtil */

/*----------------------------------------------------------*/
/* estrutura basica da tabela de simbolos */
typedef struct celTS CelTS;
struct celTS 
{
    /* ponteiro para o nome da variavel */
    char *nomeVar; 

    /* indica se a variavel ja foi inicializada */
    Bool inic;

    /* valor da variavavel */
    float valor;

    /* proxima celula da tabela */
    CelTS *prox; 
};


/*----------------------------------------------------------*/
/* prototipos das funcoes que manipula a tabel de simbolos  */

void  initTS();

float getValorTS(char *nomeVar);

void  setValorTS(char *nomeVar, float valor);

void  showTS(); 

void  freeTS();

#endif /* ts.h */
