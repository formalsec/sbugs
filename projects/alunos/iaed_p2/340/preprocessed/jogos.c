#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "jogos.h"


Jogo *cria_jogo(char *nome_j, char *eq1, char *eq2, int score1, int score2)
{
  Jogo *x = malloc(sizeof(Jogo));
  x->nome_jogo = malloc((sizeof(char)) * (strlen(nome_j) + 1));
  strcpy(x->nome_jogo, nome_j);
  x->equipa1 = malloc((sizeof(char)) * (strlen(eq1) + 1));
  strcpy(x->equipa1, eq1);
  x->equipa2 = malloc((sizeof(char)) * (strlen(eq2) + 1));
  strcpy(x->equipa2, eq2);
  x->score1 = score1;
  x->score2 = score2;
  x->next = 0;
  return x;
}

void free_jogo(Jogo *head)
{
  free(head->nome_jogo);
  free(head->equipa1);
  free(head->equipa2);
  free(head);
}
