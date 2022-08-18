/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "hash.h"


int hash(char *s)
{
  int hash;
  unsigned long int i;
  unsigned long int tamanho;
  tamanho = strlen(s);
  hash = s[0];
  for (i = 1; i < tamanho; i++)
  {
    hash = (hash + (s[i] * i)) % 9973;
  }

  return hash;
}

void FILAinit(fila Lst)
{
  Lst->head = 0;
  Lst->tail = 0;
}

void FILAclear(fila Lst)
{
  node aux;
  node aux_next;
  if (!Lst)
  {
    return;
  }
  else
  {
    
  }

  aux = Lst->head;
  while (aux)
  {
    aux_next = aux->next;
    free(aux);
    aux = aux_next;
  }

}

void FILAadd(fila Lst, void *v)
{
  node aux;
  aux = malloc(sizeof(struct str_node));
  aux->elem = v;
  aux->next = 0;
  aux->prev = Lst->tail;
  if (Lst->tail != 0)
  {
    Lst->tail->next = aux;
  }
  else
  {
    
  }

  Lst->tail = aux;
  if (Lst->head == 0)
  {
    Lst->head = aux;
  }
  else
  {
    
  }

}

void *FILAfind(fila Lst, void *v)
{
  node aux_b;
  node aux_e;
  if ((!Lst->head) || (!Lst->tail))
  {
    return 0;
  }
  else
  {
    
  }

  aux_b = Lst->head;
  aux_e = Lst->tail;
  while (aux_b && aux_e)
  {
    if (aux_b->elem == v)
    {
      return aux_b;
    }
    else
    {
      if (aux_e->elem == v)
      {
        return aux_e;
      }
      else
      {
        
      }

    }

    aux_b = aux_b->next;
    aux_e = aux_e->prev;
  }

  return 0;
}

void FILAremove(fila Lst, void *v)
{
  node aux;
  if (!Lst->head)
  {
    return;
  }
  else
  {
    
  }

  aux = FILAfind(Lst, v);
  if (aux->prev)
  {
    aux->prev->next = aux->next;
  }
  else
  {
    Lst->head = aux->next;
  }

  if (aux->next)
  {
    aux->next->prev = aux->prev;
  }
  else
  {
    Lst->tail = aux->prev;
  }

  free(aux);
  return;
}

