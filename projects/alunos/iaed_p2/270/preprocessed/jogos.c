#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "jogos.h"


void liberta_jogo(pJogo a)
{
  free(a->nome);
  free(a);
}

void imprime_jogo(pJogo a)
{
  printf("%s %s %s %d %d\n", a->nome, a->equipa1->nome, a->equipa2->nome, a->golos1, a->golos2);
}

pJogo novo_jogo(char *nome, pEquipa equipa1, pEquipa equipa2, int golos1, int golos2)
{
  pJogo jg_aux = malloc(sizeof(struct jogo));
  jg_aux->nome = strdup(nome);
  jg_aux->equipa1 = equipa1;
  jg_aux->equipa2 = equipa2;
  jg_aux->golos1 = golos1;
  jg_aux->golos2 = golos2;
  return jg_aux;
}

