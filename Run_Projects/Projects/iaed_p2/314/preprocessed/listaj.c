/*File generated by PreProcessor.py*/


#include "listaj.h"
#include <stdlib.h>
#include <string.h>


listj *mk_listj()
{
  listj *l = malloc(sizeof(listj));
  l->head = 0;
  l->last = 0;
  return l;
}

void free_nodej(nodej *n)
{
  free(n);
}

void free_listj(listj *l)
{
  while (l->head)
  {
    nodej *tmp = l->head->next;
    free_nodej(l->head);
    l->head = tmp;
  }

  free(l);
}

void apaga_nodej(listj *l, nodej *n)
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

  free_nodej(n);
}

void adiciona_j(listj *l, jogo *n)
{
  nodej *nn = malloc(sizeof(nodej));
  nn->previous = l->last;
  nn->next = 0;
  nn->j = n;
  if (l->last)
  {
    {
      l->last->next = nn;
    }
  }
  else
  {
    {
      l->head = nn;
    }
  }

  l->last = nn;
}

