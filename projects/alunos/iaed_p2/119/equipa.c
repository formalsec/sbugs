#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"
#include "hash.h"
#include "strdup.h"

link_e createEquipa(const char *name, link_e next)
/* Cria um link com uma equipa*/
{
  link_e x = (link_e) can_fail_malloc(sizeof(node_e));
  x->e.name = strdup(name);
  x->e.wins = 0;
  x->next = next;
  return x;
}

void freeEquipa(link_e x) {free(x->e.name);free(x);}

void pushEquipa(link_e *head, const char * name)
/* acrescenta uma equipa no inicio de uma lista ligada*/
{
  link_e x;
  if (*head == NULL)
  {
    *head = createEquipa(name, NULL);
    return;
  }
  x = createEquipa(name, *head);
  *head = x;
  return;
}

void popEquipa(link_e *head, const char * name)
/* remove uma equipa numa lista ligada, idependentemente da posicao*/
{
  link_e x = *head;
  if (strcmp(x->e.name, name) == 0)
  {
    *head = (*head)->next;
    freeEquipa(x);
    return;
  }
  while (x->next != NULL)
  {
    if (strcmp(x->next->e.name, name) == 0)
    {
      link_e tmp = x->next;
      x->next = x->next->next;
      freeEquipa(tmp);
      return;
    }
    x = x->next;
  }
}

HT_E initEquipa(int m)
/* inicializa uma hashtable para equipas*/
{
  HT_E new = (HT_E) can_fail_malloc(sizeof(ht_e));
  new->L = (link_e *) can_fail_malloc(m * sizeof(link_e));
  new->M = m;
  return new;
}

void insertEquipa(HT_E Equipas, const char * name)
{
/* Insere uma equipa numa hashtable*/
  int index = hash(name, Equipas->M);
  pushEquipa(&Equipas->L[index], name);
}

void removeEquipa(HT_E Equipas, const char * name)
{
/* Retira uma equipa de uma hashtable*/
  int index = hash(name, Equipas->M);
  popEquipa(&Equipas->L[index], name);
}

Equipa *searchEquipa(HT_E Equipas, const char *name)
{
/* Procura uma equipa numa hashtable*/
  int index = hash(name, Equipas->M);
  link_e x = Equipas->L[index];
  for (; x != NULL; x=x->next)
  {
    if (strcmp(x->e.name, name) == 0) return &x->e;
  }
  return NULL;
}


void incWin(HT_E Equipas, const char *name, int direction)
{
/* Incrementa ou decrementa as vitorias de uma equipa, a variavel direction controla se existe incrementacao ou decrementacao*/
  Equipa* ptr = searchEquipa(Equipas, name);
  if (ptr != NULL)
  {
    if (direction > 0) ptr->wins++;
    else ptr->wins--;
  }
}