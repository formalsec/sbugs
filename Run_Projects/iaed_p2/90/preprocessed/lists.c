/*File generated by PreProcessor.py*/


#include "lists.h"


list *list_init()
{
  list *new;
  new = malloc(sizeof(list));
  new->head = 0;
  new->tail = 0;
  return new;
}

lst_node *list_append(list *l, void *val)
{
  lst_node *new;
  new = malloc(sizeof(lst_node));
  new->next = 0;
  new->prev = l->tail;
  new->value = val;
  if (l->tail != 0)
  {
    l->tail->next = new;
  }
  else
  {
    l->head = new;
  }

  l->tail = new;
  return new;
}

list *remove_node(list *l, lst_node *nd)
{
  if (nd->prev != 0)
  {
    nd->prev->next = nd->next;
  }
  else
  {
    l->head = nd->next;
  }

  if (nd->next != 0)
  {
    nd->next->prev = nd->prev;
  }
  else
  {
    l->tail = nd->prev;
  }

  free(nd);
  return l;
}

void destroy_list(list *l, void (*del)(void *nd))
{
  lst_node *cursor;
  lst_node *next;
  cursor = l->head;
  while (cursor != 0)
  {
    next = cursor->next;
    del(cursor->value);
    free(cursor);
    cursor = next;
  }

  free(l);
  return;
}

