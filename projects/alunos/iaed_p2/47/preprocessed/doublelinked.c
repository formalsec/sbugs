#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "doublelinked.h"


GameLinkedList list_init()
{
  GameLinkedList list = malloc(sizeof(struct MasterNode));
  list->n_elementos = 0;
  list->head = 0;
  list->tail = 0;
  return list;
}

Link add_node(Link prev, Link next, GAME game)
{
  Link new = malloc(sizeof(struct Node));
  new->Game = game;
  new->prev = prev;
  new->next = next;
  if (prev != 0)
  {
    prev->next = new;
  }
  else
  {
    
  }

  if (next != 0)
  {
    next->prev = new;
  }
  else
  {
    
  }

  return new;
}

void delete_node(Link node)
{
  free(node);
}

int is_empty(GameLinkedList list)
{
  return get_n_elementos(list) == 0;
}

GAME get_GAME(Link h)
{
  if (h != 0)
  {
    return h->Game;
  }
  else
  {
    
  }

  return 0;
}

int get_n_elementos(GameLinkedList list)
{
  if (list != 0)
  {
    return list->n_elementos;
  }
  else
  {
    
  }

  return 0;
}

Link search_list(GameLinkedList list, gameKey key)
{
  Link current;
  for (current = list->head; current != 0; current = current->next)
  {
    if (strcmp(get_GAME(current)->Gamename, key) == 0)
    {
      return current;
    }
    else
    {
      
    }

  }

  return 0;
}

void append(GameLinkedList list, GAME i)
{
  Link newNode = add_node(list->tail, 0, i);
  list->tail = newNode;
  if (list->head == 0)
  {
    list->head = newNode;
  }
  else
  {
    
  }

  list->n_elementos++;
}

void pop(GameLinkedList list)
{
  Link oldHead;
  if ((list->head == 0) || is_empty(list))
  {
    return;
  }
  else
  {
    
  }

  oldHead = list->head;
  list->head = oldHead->next;
  if (list->head != 0)
  {
    list->head->prev = 0;
  }
  else
  {
    list->tail = 0;
  }

  delete_node(oldHead);
  list->n_elementos--;
}

void remove_last(GameLinkedList list)
{
  Link oldTail;
  if ((list == 0) || is_empty(list))
  {
    return;
  }
  else
  {
    
  }

  oldTail = list->tail;
  list->tail = oldTail->prev;
  if (list->tail != 0)
  {
    list->tail->next = 0;
  }
  else
  {
    list->head = 0;
  }

  delete_node(oldTail);
  list->n_elementos--;
}

void remove_Game_list(GameLinkedList list, gameKey k)
{
  Link current;
  if ((list == 0) || is_empty(list))
  {
    return;
  }
  else
  {
    
  }

  current = search_list(list, k);
  if (current == list->head)
  {
    pop(list);
  }
  else
  {
    if (current == list->tail)
    {
      remove_last(list);
    }
    else
    {
      current->prev->next = current->next;
      current->next->prev = current->prev;
      delete_node(current);
      list->n_elementos--;
    }

  }

}

void destroy_list(GameLinkedList list)
{
  Link current;
  Link aux;
  if (list == 0)
  {
    return;
  }
  else
  {
    
  }

  if (list->n_elementos != 0)
  {
    for (current = list->head, aux = list->head->next; current != 0; aux = current->next, delete_node(current), current = aux)
    {
    }

  }
  else
  {
    
  }

  free(list);
}

