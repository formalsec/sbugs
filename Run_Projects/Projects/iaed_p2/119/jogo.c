#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "jogo.h"
#include "strdup.h"

link_j createJogo(const char *name, const char *e1, const char *e2, int s1, int s2 ,link_j next)
/* Devolve um link com um jogo*/
{
  link_j new = (link_j) malloc(sizeof(node_j));
  new->j.name = strdup(name);
  new->j.equipa1 = strdup(e1);
  new->j.equipa2 = strdup(e2);
  new->j.score1 = s1;
  new->j.score2 = s2;
  new->next = next;
  return new;
}

void freeJogo(link_j x)
{
  free(x->j.name);
  free(x->j.equipa1);
  free(x->j.equipa2);
  free(x);
}

void pushJogo(link_j *head, const char * name, const char *e1, const char *e2, int s1, int s2)
{
/* Adiciona um jogo ao inicio de uma lista ligada*/
  link_j x;
  if (*head == NULL)
  {
    *head = createJogo(name, e1, e2, s1, s2, NULL);
    return;
  }
  x = createJogo(name, e1, e2, s1, s2, *head);
  *head = x;
  return;
}

void popJogo(link_j *head, const char * name)
{
/* Remove um jogo numa lista ligada independentemente da posicao*/
  link_j x = *head;
  if (strcmp(x->j.name, name) == 0)
  {
    link_j x = *head;
    *head = (*head)->next;
    freeJogo(x);
    return;
  }
  while (x->next != NULL)
  {
    if (strcmp(x->next->j.name, name) == 0)
    {
      link_j tmp = x->next;
      x->next = x->next->next;
      freeJogo(tmp);
      return;
    }
    x = x->next;
  }
}

HT_J initJogo(int m)
{
/* inicializa uma hashtable de jogos*/
  HT_J new = (HT_J) malloc(sizeof(ht_j));
  new->L = (link_j *) malloc(m * sizeof(link_j));
  new->M = m;
  return new;
}

void insertJogo(HT_J Jogos, const char *name, const char *e1, const char *e2, int s1, int s2)
{
/* insere um jogo na hashtable */
  int index = hash(name, Jogos->M);
  pushJogo(&Jogos->L[index], name, e1, e2, s1, s2);
}

void removeJogo(HT_J Jogos, const char * name)
{
/* remove um jogo da hashtable*/
  int index = hash(name, Jogos->M);
  popJogo(&Jogos->L[index], name);
}

Jogo *searchJogo(HT_J Jogos, const char *name)
{
/* procura um jogo na hashtable*/
  int index = hash(name, Jogos->M);
  link_j x = Jogos->L[index];
  for (; x != NULL; x=x->next)
  {
    if (strcmp(x->j.name, name) == 0) return &x->j;
  }
  return NULL;
}