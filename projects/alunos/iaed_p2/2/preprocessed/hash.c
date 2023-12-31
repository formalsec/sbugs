#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "hash.h"


HashTable HTinit(int max, void *(*keyfunc)(void *))
{
  HashTable ht;
  ht.M = 2 * max;
  ht.N = 0;
  ht.keyfunc = keyfunc;
  ht.t = calloc(ht.M, sizeof(void *));
  return ht;
}

void HTinsert(void *pItem, HashTable *ht)
{
  int i = hashItem((Itemkey) ht->keyfunc(pItem), ht->M);
  while (ht->t[i] != 0)
    i = (i + 1) % ht->M;

  ht->t[i] = pItem;
  if ((ht->N++) > (ht->M / 2))
  {
    int i;
    void **tmp = ht->t;
    *ht = HTinit(ht->M, ht->keyfunc);
    for (i = 0; i < (ht->M / 2); i++)
      if (tmp[i] != 0)
    {
      HTinsert(tmp[i], ht);
    }
    else
    {
      
    }


    free(tmp);
  }
  else
  {
    
  }

}

void *HTsearch(Itemkey k, HashTable *ht)
{
  int i = hashItem(k, ht->M);
  while ((ht->t[i] != 0) && strcmp((Itemkey) ht->keyfunc(ht->t[i]), k))
    i = (i + 1) % ht->M;

  return ht->t[i];
}

void HTremove(Itemkey k, HashTable *ht)
{
  int i = hashItem(k, ht->M);
  while ((ht->t[i] != 0) && strcmp((Itemkey) ht->keyfunc(ht->t[i]), k))
    i = (i + 1) % ht->M;

  if (ht->t[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  ht->t[i] = 0;
  while (ht->t[i = (i + 1) % ht->M] != 0)
  {
    void *v = ht->t[i];
    ht->t[i] = 0;
    ht->N--;
    HTinsert(v, ht);
  }

  ht->N--;
}

void HTdestroy(HashTable *ht)
{
  free(ht->t);
}

void HTdestroy_with_item_free(HashTable *ht)
{
  int i;
  for (i = 0; i < ht->M; i++)
    if (ht->t[i] != 0)
  {
    free((Itemkey) ht->keyfunc(ht->t[i]));
    free(ht->t[i]);
  }
  else
  {
    
  }


  free(ht->t);
}

