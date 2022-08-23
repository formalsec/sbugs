/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doublinklist.h"


void DLinsertEnd(ItemDL v)
{
  link p = malloc(sizeof(struct node));
  p->v = v;
  p->next = 0;
  if (head == 0)
  {
    {
      head = p;
    }
  }
  else
  {
    {
      head->prev->next = p;
      p->prev = head->prev;
    }
  }

  head->prev = p;
}

link DLsearch(ItemkeyDL k)
{
  link p = head;
  while (p && strcmp(keyDL(p->v), k))
    p = p->next;

  return p;
}

void DLremove_with_item_free(link p)
{
  if (!p)
  {
    return;
  }
  else
  {
    
  }

  if (p == head)
  {
    {
      if (p->next)
      {
        p->next->prev = p->prev;
      }
      else
      {
        
      }

      head = p->next;
    }
  }
  else
  {
    {
      p->prev->next = p->next;
      if (p->next)
      {
        p->next->prev = p->prev;
      }
      else
      {
        head->prev = p->prev;
      }

    }
  }

  freeItemDL(p->v);
  free(p);
}

void DLdestroy_with_item_free()
{
  link p;
  while (head)
  {
    p = head;
    head = head->next;
    freeItemDL(p->v);
    free(p);
  }

}

