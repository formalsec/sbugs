#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 1024
#include "estruturas.h"

/*Esta funcao insere um jogo no final da lista*/
link insertEnd(link* head,pjogo teste)
{
  link t;
  link new = (link)can_fail_malloc(sizeof(struct node));
  new->next = NULL;
  new->jogo = teste;
  if ((*head)==NULL)
  {
    return new;
  }
  for (t=(*head);t->next!=NULL;t=t->next)
    ;
  t->next = new;
  return (*head);
}

/*Esta funcao insere uma equipa no final da lista*/
link insertEnd_equipas(link* head,pequipa teste)
{
  link t;
  link new = (link)can_fail_malloc(sizeof(struct node));
  new->next = NULL;
  new->equipa = teste;
  if ((*head)==NULL)
  {
    return new;
  }
  for (t=(*head);t->next!=NULL;t=t->next)
    ;
  t->next = new;
  return (*head);
}

/*Esta funcao da free a todos os jogos alocados previamente*/
void da_free_st(link* head)
{
  link t,teste;
  for(t=(*head); t != NULL ;)
  {
    teste = t->next;
    free(t->jogo->nome_jogo);
    free(t->jogo->equipa1);
    free(t->jogo->equipa2);
    free(t->jogo);
    free(t);
    t = teste;
  }
}

/*Esta funcao da free a todas as equipas alocadas previamente*/
void da_free_ht(link* head_2)
{
  link t,teste;
  for(t=(*head_2); t != NULL ;)
  {
    teste = t->next;
    free(t->equipa->equipa);
    free(t->equipa);
    free(t);
    t = teste;
  }
}
