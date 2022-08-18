/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "structures.h"


listJogo *mkListJogo()
{
  listJogo *l = malloc(sizeof(listJogo));
  l->head = (l->last = 0);
  return l;
}

listEquipa *mkListEquipa()
{
  listEquipa *l = malloc(sizeof(listEquipa));
  l->head = (l->last = 0);
  return l;
}

void freeNodeJogo(nodeJogo *n)
{
  free(n->nomeJogo);
  free(n->nomeEquipa1);
  free(n->nomeEquipa2);
  free(n);
}

void freeNodeEquipa(nodeEquipa *n)
{
  free(n->nomeEquipa);
  free(n);
}

void freeListJogo(listJogo *l)
{
  while (l->head)
  {
    nodeJogo *tmp = l->head->next;
    freeNodeJogo(l->head);
    l->head = tmp;
  }

  free(l);
}

void freeListEquipa(listEquipa *l)
{
  while (l->head)
  {
    nodeEquipa *tmp = l->head->next;
    freeNodeEquipa(l->head);
    l->head = tmp;
  }

  free(l);
}

void removeNodeJogo(listJogo *l, nodeJogo *n)
{
  if (n->previous == 0)
  {
    {
      l->head = n->next;
    }
  }
  else
  {
    {
      n->previous->next = n->next;
    }
  }

  if (n->next == 0)
  {
    {
      l->last = n->previous;
    }
  }
  else
  {
    {
      n->next->previous = n->previous;
    }
  }

  freeNodeJogo(n);
}

void removeNodeEquipa(listEquipa *l, nodeEquipa *n)
{
  if (n->previous == 0)
  {
    {
      l->head = n->next;
    }
  }
  else
  {
    {
      n->previous->next = n->next;
    }
  }

  if (n->next == 0)
  {
    {
      l->last = n->previous;
    }
  }
  else
  {
    {
      n->next->previous = n->previous;
    }
  }

  freeNodeEquipa(n);
}

void addNodeJogo(listJogo *l, const char *_nomeJogo, const char *_nomeEquipa1, const char *_nomeEquipa2, int _resultado1, int _resultado2)
{
  nodeJogo *n = malloc(sizeof(nodeJogo));
  n->previous = l->last;
  n->next = 0;
  n->nomeJogo = malloc((sizeof(char)) * (strlen(_nomeJogo) + 1));
  strcpy(n->nomeJogo, _nomeJogo);
  n->nomeEquipa1 = malloc((sizeof(char)) * (strlen(_nomeEquipa1) + 1));
  strcpy(n->nomeEquipa1, _nomeEquipa1);
  n->nomeEquipa2 = malloc((sizeof(char)) * (strlen(_nomeEquipa2) + 1));
  strcpy(n->nomeEquipa2, _nomeEquipa2);
  n->resultado1 = _resultado1;
  n->resultado2 = _resultado2;
  if (l->last)
  {
    l->last->next = n;
  }
  else
  {
    l->head = n;
  }

  l->last = n;
}

void addNodeEquipa(listEquipa *l, const char *_nomeEquipa)
{
  nodeEquipa *n = malloc(sizeof(nodeEquipa));
  n->previous = l->last;
  n->next = 0;
  n->nomeEquipa = malloc((sizeof(char)) * (strlen(_nomeEquipa) + 1));
  strcpy(n->nomeEquipa, _nomeEquipa);
  n->vitorias = 0;
  if (l->last)
  {
    l->last->next = n;
  }
  else
  {
    l->head = n;
  }

  l->last = n;
}

nodeJogo *searchListJogo(listJogo *lstJogo, char *_nomeJogo)
{
  nodeJogo *currentNode;
  for (currentNode = lstJogo->head; currentNode != 0; currentNode = currentNode->next)
  {
    if (strcmp(currentNode->nomeJogo, _nomeJogo) == 0)
    {
      return currentNode;
    }
    else
    {
      
    }

  }

  return currentNode->next;
}

nodeEquipa *searchListEquipa(listEquipa *lstEquipa, char *_nomeEquipa)
{
  nodeEquipa *currentNode;
  for (currentNode = lstEquipa->head; currentNode != 0; currentNode = currentNode->next)
  {
    if (strcmp(currentNode->nomeEquipa, _nomeEquipa) == 0)
    {
      return currentNode;
    }
    else
    {
      
    }

  }

  return currentNode->next;
}

int existJogo(listJogo *lstJogo, char *_nomeJogo)
{
  nodeJogo *currentNode;
  for (currentNode = lstJogo->head; currentNode != 0; currentNode = currentNode->next)
  {
    if (strcmp(currentNode->nomeJogo, _nomeJogo) == 0)
    {
      {
        return 0;
      }
    }
    else
    {
      
    }

  }

  return 1;
}

int existEquipa(listEquipa *lstEquipa, char *_nomeEquipa)
{
  nodeEquipa *currentNode;
  for (currentNode = lstEquipa->head; currentNode != 0; currentNode = currentNode->next)
  {
    if (strcmp(currentNode->nomeEquipa, _nomeEquipa) == 0)
    {
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

