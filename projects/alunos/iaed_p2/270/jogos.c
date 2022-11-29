#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "jogos.h"

/* Recebe um ponteiro para um jogo e Liberta a memoria alocada por ele
 * (nome do jogo, das equipas e ponteiro para a estrutura do jogo)*/
void liberta_jogo(pJogo a){
  free(nome(a)); free(a);
}

/* Recebe um ponteiro para um jogo e imprime no stdout o nome do jogo, das
 * equipas e a pontucao do jogo */
void imprime_jogo(pJogo a){
  printf("%s %s %s %d %d\n",
  nome(a), nome(equipa1(a)), nome(equipa2(a)),
  a->golos1, a->golos2);
}

/* Recebe um ponteiro para o nome do jogo a criar e para os nomes das equipas
 * que o constituem e devolve um ponteiro para a estrutura do jogo alocando
 * memoria para o mesmo e para os nomes */
pJogo novo_jogo(char* nome, pEquipa equipa1, pEquipa equipa2, int golos1, int golos2){
  pJogo jg_aux = can_fail_malloc(sizeof(struct jogo));
  nome(jg_aux) = strdup(nome);
  equipa1(jg_aux) = equipa1; equipa2(jg_aux) = equipa2;
  jg_aux->golos1 = golos1; jg_aux->golos2 = golos2;
  return jg_aux;
}
