#ifndef STRUCTS_H
#define STRUCTS_H
/*estrutura dos jogos que contem um nome, duas equipas e o respetivo score*/
typedef struct {
  char *nome,*equipa1,*equipa2;
  int score1,score2;
} jogo;
/*estrutura singular da listas interligadas que contem um jogo, um ponteiro para o proximo noh, e outros dois ponteiros para o elemento antes e depois da fila */
typedef struct noh {
  struct noh *prox;
  struct noh *prox_fila, *ant_fila;
  jogo *jogo;
} noh;
/*similar ao noh normal mas dedicado a guardar as equipas na hashtable*/
typedef struct noh_equipa {
  struct noh_equipa *prox;
  char *equipa;
  int jogos_ganhos;
} noh_equipa;
/*a fila e uma lista duplamente ligada em que se pode aceder ao primeiro e ultimo elemento com facilidade. utilizada para listar jogos pela ordem de insercao*/
typedef struct fila {
  noh *cabeca, *tail;
} fila;

#endif