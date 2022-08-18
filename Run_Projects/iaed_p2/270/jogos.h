#ifndef JOGOS_H
#define JOGOS_H
#include "equipas.h"

/* estrutura que representa as caracteristicas de um jogo */
struct jogo{
  char *nome;
  int golos1, golos2;
  pEquipa equipa1, equipa2;
  struct jogo *seguinte, *anterior; /*um jogo corresponde a um no de uma lista.d.ligada*/
};

/* abstracoes para a estrutura dos jogos */
typedef struct jogo* pJogo;
#define equipa1(a) (a->equipa1)
#define equipa2(a) (a->equipa2)
#define golos1(a) (a->golos1)
#define golos2(a) (a->golos2)


/*prototipos das funcoes referentes aos jogos */
void liberta_jogo(pJogo a);
void imprime_jogo(pJogo a);
pJogo novo_jogo(char *nome, pEquipa equipa1, pEquipa equipa2, int golos1, int golos2);

#endif
