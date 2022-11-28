#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "jogo.h"
#include "abstract.h"
#include "equipa.h"


void freeJogo(ptr_jogo a)
{
  free(a->nome);
  free(a);
}

ptr_jogo newJogo(char *nome, ptr_equipa equipa1, ptr_equipa equipa2, int score1, int score2)
{
  ptr_jogo new = (ptr_jogo) malloc(sizeof(struct jogo));
  new->nome = malloc((strlen(nome) + 1) * (sizeof(char)));
  strcpy(new->nome, nome);
  new->equipa1 = equipa1;
  new->equipa2 = equipa2;
  new->score1 = score1;
  new->score2 = score2;
  return new;
}
