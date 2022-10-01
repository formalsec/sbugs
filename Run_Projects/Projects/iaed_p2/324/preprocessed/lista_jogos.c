/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


jogos *mk_list_jg()
{
  jogos *l = malloc(sizeof(jogos));
  l->head = (l->last = 0);
  return l;
}

jg_node *add_last_jg(jogos *l, const char *nome, const char *equipa1, const char *equipa2, int score1, int score2)
{
  jg_node *nn = malloc(sizeof(jg_node));
  nn->previous = l->last;
  nn->next = 0;
  nn->value = malloc((sizeof(char)) * (strlen(nome) + 1));
  nn->equipa1 = malloc((sizeof(char)) * (strlen(equipa1) + 1));
  nn->equipa2 = malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(nn->value, nome);
  strcpy(nn->equipa1, equipa1);
  strcpy(nn->equipa2, equipa2);
  nn->score1 = score1;
  nn->score2 = score2;
  if (l->last)
  {
    l->last->next = nn;
  }
  else
  {
    l->head = nn;
  }

  l->last = nn;
  return nn;
}
