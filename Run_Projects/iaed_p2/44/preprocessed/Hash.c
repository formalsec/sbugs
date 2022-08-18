/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hash.h"


static int M;
int hash(char *v, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (M - 1))
    h = ((a * h) + (*v)) % M;

  return h;
}

link JnewNode(link next, jogo j)
{
  link l = (link) malloc(sizeof(struct node));
  l->j = j;
  l->next = next;
  return l;
}

jogo JsearchList(link head, Key v)
{
  link aux;
  for (aux = head; aux; aux = aux->next)
  {
    if (strcmp(v, aux->j->nome) == 0)
    {
      {
        return aux->j;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

link removeJ(link head, Key k)
{
  link aux;
  link aux2;
  for (aux = head, aux2 = 0; aux; aux2 = aux, aux = aux->next)
  {
    if (strcmp(k, aux->j->nome) == 0)
    {
      {
        if (aux == head)
        {
          {
            head = aux->next;
          }
        }
        else
        {
          {
            aux2->next = aux->next;
          }
        }

        if (aux->j->score1 > aux->j->score2)
        {
          {
            aux->j->equipa1->wins--;
          }
        }
        else
        {
          
        }

        if (aux->j->score1 < aux->j->score2)
        {
          {
            aux->j->equipa2->wins--;
          }
        }
        else
        {
          
        }

        freeJogo(aux->j);
        free(aux);
        return head;
      }
    }
    else
    {
      
    }

  }

  return head;
}

void JfreeHash(link head)
{
  link aux1;
  link aux2;
  if (!head)
  {
    return;
  }
  else
  {
    
  }

  for (aux1 = head, aux2 = head->next; aux1; aux2 = aux1->next, aux1 = aux2)
  {
    freeJogo(aux1->j);
    free(aux1);
  }

}

link *Jinit(int m)
{
  link *heads;
  int i;
  M = m;
  heads = (link *) malloc(M * (sizeof(link)));
  for (i = 0; i < M; i++)
  {
    heads[i] = 0;
  }

  return heads;
}

void Jinsert(link *heads, jogo j)
{
  int i = hash(j->nome, M);
  heads[i] = JnewNode(heads[i], j);
}

jogo Jsearch(link *heads, Key v)
{
  int i = hash(v, M);
  return JsearchList(heads[i], v);
}

void Jdelete(link *heads, Key v)
{
  int i = hash(v, M);
  heads[i] = removeJ(heads[i], v);
}

void JdestroyHash(link *heads)
{
  int i;
  for (i = 0; i < M; i++)
  {
    JfreeHash(heads[i]);
  }

  free(heads);
}

int getWins(Elink *tops, char team[1024])
{
  equipa eq;
  eq = Esearch(tops, team);
  return eq->wins;
}

int TeamOrder(const void *x, const void *y)
{
  const equipa a = *((const equipa *) x);
  const equipa b = *((const equipa *) y);
  return strcmp(a->nome, b->nome);
}

void getMostWins(Elink *tops, int count)
{
  int i;
  int j;
  int k;
  int maxWins;
  Elink aux;
  equipa *Array;
  for (i = 0, maxWins = -1; i < M; i++)
  {
    for (aux = tops[i]; aux; aux = aux->next)
    {
      j = 0;
      j = aux->e->wins;
      if (j > maxWins)
      {
        {
          maxWins = j;
        }
      }
      else
      {
        
      }

    }

  }

  if (maxWins == (-1))
  {
    return;
  }
  else
  {
    
  }

  k = 0;
  for (i = 0; i < M; i++)
  {
    for (aux = tops[i]; aux; aux = aux->next)
    {
      if (aux->e->wins == maxWins)
      {
        {
          k++;
        }
      }
      else
      {
        
      }

    }

  }

  Array = malloc((sizeof(equipa)) * k);
  i = 0;
  while (i < k)
  {
    for (j = 0; j < M; j++)
    {
      for (aux = tops[j]; aux; aux = aux->next)
      {
        if (aux->e->wins == maxWins)
        {
          {
            Array[i] = aux->e;
            i++;
          }
        }
        else
        {
          
        }

      }

    }

  }

  qsort(Array, k, sizeof(equipa), TeamOrder);
  printf("%d Melhores %d\n", count, maxWins);
  for (i = 0; i < k; i++)
  {
    printf("%d * %s\n", count, Array[i]->nome);
  }

  free(Array);
}

Elink EnewNode(Elink next, equipa e)
{
  Elink l = (Elink) malloc(sizeof(struct Enode));
  l->e = e;
  l->next = next;
  return l;
}

equipa EsearchList(Elink top, Point v)
{
  Elink aux;
  for (aux = top; aux; aux = aux->next)
  {
    if (strcmp(v, aux->e->nome) == 0)
    {
      {
        return aux->e;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

void EfreeHash(Elink top)
{
  Elink aux1;
  Elink aux2;
  if (!top)
  {
    return;
  }
  else
  {
    
  }

  for (aux1 = top, aux2 = top->next; aux1; aux2 = aux1->next, aux1 = aux2)
  {
    freeEquipa(aux1->e);
    free(aux1);
  }

}

Elink *Einit(int m)
{
  Elink *tops;
  int i;
  M = m;
  tops = (Elink *) malloc(M * (sizeof(Elink)));
  for (i = 0; i < M; i++)
  {
    tops[i] = 0;
  }

  return tops;
}

void Einsert(Elink *tops, equipa e)
{
  int i = hash(e->nome, M);
  tops[i] = EnewNode(tops[i], e);
}

equipa Esearch(Elink *tops, Point v)
{
  int i = hash(v, M);
  return EsearchList(tops[i], v);
}

void EdestroyHash(Elink *tops)
{
  int i;
  for (i = 0; i < M; i++)
  {
    EfreeHash(tops[i]);
  }

  free(tops);
}

