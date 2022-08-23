/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "games_dll.h"


dlst mk_list()
{
  dlst list = malloc(sizeof(struct dl_list));
  list->head = (list->last = 0);
  return list;
}

dl_node find_node(dlst list, Game game)
{
  dl_node aux = list->head;
  while (aux)
  {
    if (strcmp(aux->game->name, game->name) == 0)
    {
      return aux;
    }
    else
    {
      
    }

    aux = aux->next;
  }

  return 0;
}

void rm_node(dlst list, Game game)
{
  dl_node n = find_node(list, game);
  if (n->previous == 0)
  {
    list->head = n->next;
  }
  else
  {
    n->previous->next = n->next;
  }

  if (n->next == 0)
  {
    list->last = n->previous;
  }
  else
  {
    n->next->previous = n->previous;
  }

  free(n);
}

void add_last(dlst list, Game game)
{
  dl_node nn = malloc(sizeof(struct stru_node));
  nn->previous = list->last;
  nn->next = 0;
  nn->game = game;
  if (list->last)
  {
    list->last->next = nn;
  }
  else
  {
    list->head = nn;
  }

  list->last = nn;
}

void printGames(dlst list, int c)
{
  dl_node temp = list->head;
  while (temp)
  {
    printGame(temp->game, c);
    temp = temp->next;
  }

}

void dll_destroy(dlst list)
{
  while (list->head)
  {
    dl_node temp = list->head->next;
    free(list->head);
    list->head = temp;
  }

  free(list);
}

