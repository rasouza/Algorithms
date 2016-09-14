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

  eval.c
  Pitao I

  Referências: Com exceção das rotinas fornecidas no esqueleto e em sala
  de aula, caso você tenha utilizado alguma refência, liste-as abaixo
  para que o seu programa não seja considerada plágio.
  Exemplo:
  - função mallocc retirada de: http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html

 \__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__\__
*/

/*
  NAO EDITE OU MODIFIQUE NADA QUE ESTA ESCRITO NESTE ESQUELETO
*/

/*------------------------------------------------------------*/
/* interface para as funcoes deste modulo */
#include "eval.h" 

/*------------------------------------------------------------*/
#include <stdlib.h>  /* atoi(), atof() */
#include <string.h>  /* strncmp(), strlen(), strncpy(), strcpy() */
#include <math.h>    /* pow() */

/*------------------------------------------------------------*/
#include "classes.h" /* tipo Classe */


/*------------------------------------------------------------
  Tabela com a preceedencia do operadores

  http://www.ime.usp.br/~pf/algoritmos/apend/precedence.html
*/
static const int precedencia[MAX_OPERADORES] =
{
    /* 4 operadores relacionais com 2 simbolos  */
     4   /* "==" */ /* da esquerda para a direita */
    ,4   /* "!=" */ /* da esquerda para a direita */
    ,5   /* ">=" */ /* da esquerda para a direita */
    ,5   /* "<=" */ /* da esquerda para a direita */
    
    /* 2 operadores relacionais com 1 simbolo */
    ,5  /* ">"  */ /* da esquerda para a direita */
    ,5  /* "<"  */ /* da esquerda para a direita */ 
    
    /* 7 operadores aritmeticos */
    ,8  /* "^" */ /* da direita para a esquerda */
    ,7  /* "%" */ /* da esquerda para a direita */
    ,7  /* "*" */ /* da esquerda para a direita */
    ,7  /* "/" */ /* da esquerda para a direita */
    ,6  /* "+" */ /* da esquerda para a direita */
    ,6  /* "-" */ /* da esquerda para a direita */
    ,8  /* "_" */ /* da direita para a esquerda */
    
    /* 3 operadores logicos  */
    ,3  /* "&&" */ /* da esquerda para a direita */ 
    ,2  /* "||" */ /* da esquerda para a direita */
    ,8  /* "!"  */ /* da direita para a esquerda */

     /* atribuicao */ 
    ,1  /* "=" */ /* da direita para a esquerda */ 
}; 


/*-------------------------------------------------------------
    itensParaValores(iniFilaItens)
    
    Recebe uma lista ligada com cabeca iniFilaItens representado uma 
    fila de itens lexicos e converte o campo util de cada celula 
    para um valor como descrito a seguir. 

    Nessa conversao, o campo 'util' de cada celula recebe um valor 
    da seguinte maneira.

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um string que representa um float (FLOAT_STR), 
         o campo 'vFloat' deve recebe o valor desse float;

       - se o campo 'classe' da celula indica que 'item' e um ponteiro 
         para um operador, o campo 'prec' deve receber a precedencia
         desse operador.
 
         Para isto utilize o vetor 'precedencia'declarado antes 
         desta funcao. 

	 Nesta funcao voce pode utilizar qualquer funcao da biblioteca
         string do C, como, por exemplo, atof().

   Esta funcao _nao_ deve alocar celula alguma, no entanto ela
   deve dar free nas estruturas que deixarem de ser necessarias.
*/

void
itensParaValores(CelUtil *iniFilaItens)
{
  CelUtil* p;

  /* Percorre a fila de itens lexicos */
  for(p = iniFilaItens->prox; p != NULL; p = p->prox) {

    /* O item lexico e um FLOAT_STR, converte para FLOAT */
    if (p->classe == FLOAT_STR) {
      p->classe = FLOAT;
      p->vFloat = atof(p->item);
    }

    /* O item lexico e um operador, troca pela precedencia */
    else if (p->classe < 17)
      p->prec = precedencia[p->classe];
  }
}


/*-------------------------------------------------------------
  eval(iniPosfixa, mostrePilhaExecucao)
  
  Recebe uma lista ligada como cabeca iniPosfixa que representa
  uma expressao em notacao posfixa. 
  
  A funcao percorre a expressao calculando os valores resultantes.
  Para isto e utilizada uma pilha de execucao. 
  
  A pilha de execucao e representada atraves de uma lista ligada
  com cabeca em que cada elemento e do tipo CelUtil.
  
  Ao final a funcao retorna o endereco da celula no topo da 
  pilha de execucao.
  
  O parametro mostrePilhaExecucao indica se os valores
  na pilha devem ser exibidos depois de qualquer alteracao na
  pilha de execucao.
  
  Esta funcao _nao_ deve alocar celula alguma, no entanto ela
  deve dar free nas estruturas que deixarem de ser necessarias.

  CORRECAO em 28/SET: 
      Esta funcao, ou qualquer funcao chamada por ela,
      pode alocar __no maximo__ uma celula CelUtil para ser a 
      cabeca da pilha. Isto pode ser particularmente util
      para aqueles que desejarem escrever um interface e biblioteca 
      como stack.h e stack.c feitas na aula
      desta semana.  

*/

CelUtil *
eval (CelUtil *iniPosfixa, Bool mostrePilhaExecucao)
{
  CelUtil *p, n1, n2, n3, *topo; /* Variaveis usadas para o calculo das operacoes */
  Stack s;

  topo = (CelUtil*)mallocSafe(sizeof(CelUtil*));

  s = stackInit(100); /* ALTERAR VALOR DEPOIS, SE DER TEMPO */

  /* Percorre os valores da lista */
  for (p = iniPosfixa->prox; p != NULL; p = p->prox) {

    /* Encontramos um numero, adiciona na pilha de execucao */
    if (p->classe == FLOAT)
      stackPush(s, *p);

    /* Encontramos um operador, desempilha os itens, calcula e empilha o resultado */
    else 
    {
      switch(p->classe)
      {
        case OPER_IGUAL:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat == n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_DIFERENTE:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat != n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_MAIOR_IGUAL:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat >= n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_MENOR_IGUAL:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat <= n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_MAIOR:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat > n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_MENOR:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat < n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_EXPONENCIACAO:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = pow(n2.vFloat,n1.vFloat);
          stackPush(s, n3);
          break;

        case OPER_RESTO_DIVISAO:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = (float)((int)n2.vFloat % (int)n1.vFloat);
          stackPush(s, n3);
          break;

        case OPER_MULTIPLICACAO:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat * n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_DIVISAO:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat / n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_ADICAO:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat + n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_SUBTRACAO:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat - n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_MENOS_UNARIO:
          n1 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = -(n1.vFloat);
          stackPush(s, n3);
          break;

        case OPER_LOGICO_AND:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat && n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_LOGICO_OR:
          n1 = stackPop(s);
          n2 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = n2.vFloat || n1.vFloat;
          stackPush(s, n3);
          break;

        case OPER_LOGICO_NOT:
          n1 = stackPop(s);
          n3.classe = FLOAT;
          n3.vFloat = !(n1.vFloat);
          stackPush(s, n3);
          break;

        default:

        break;
      }
    }
  }

  *topo = stackTop(s);

  return topo;    
}


/*-------------------------------------------------------------
  Implementações da PILHA
*/
  


/*
 * PILHA: uma implementacao com lista encadeada sem cabeca
 */
typedef struct stackNode* Link;
struct stackNode { 
    CelUtil conteudo; 
    Link prox; 
};

struct stack { /* aqui esta especificado o que e' */
    Link topo;   /* uma pilha: um apontador para stacknode */
};


Stack
stackInit(int n)
{ 
    Stack s = (Stack) mallocSafe(sizeof *s);
    s->topo = NULL; 
    return s;
}

int 
stackEmpty(Stack s)
{ 
    return s->topo == NULL; 
}

void 
stackPush(Stack s, CelUtil conteudo)
{ 
    Link p = (Link) mallocSafe(sizeof *p);
    p->conteudo = conteudo;
    p->prox = s->topo;
    s->topo = p;
}

CelUtil 
stackPop(Stack s)
{ 
    Link p = s->topo;
    CelUtil conteudo;

    if (p == NULL) /* stackempty() */
    {
  fprintf(stderr,"Putz, voce nao sabe o que esta fazendo!\n");
  exit(-1);
    }
    /* tudo bem, a pilha nao esta vazia... */
    conteudo = p->conteudo;
    s->topo = p->prox;
    free(p);
    return conteudo;  
}

CelUtil
stackTop(Stack s)
{
    if (s->topo == NULL) /* stackempty() */
    {
  fprintf(stderr,"Putz, voce nao sabe o que esta fazendo!\n");
  exit(-1);
    }

    /* tudo bem, a pilha nao esta vazia... */
    return  s->topo->conteudo;
}

void 
stackFree(Stack s)
{
    while (s->topo != NULL) 
    {
  Link p = s->topo;
  s->topo = s->topo->prox;
  free(p);
    }

    free(s);
}


void
stackDump(Stack s)
{
    Link p = s->topo;
    fprintf(stdout, "pilha:");
    if (p == NULL) fprintf(stdout, "vazia.");
    while (p != NULL)
    {
      fprintf(stdout," %f", p->conteudo.vFloat);
      p = p->prox;
    }
    fprintf(stdout,"\n");
}