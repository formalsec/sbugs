#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "games.h"


match creates_match(char *name, char *team1, char *team2, int score1, int score2)
{
  match new = (match) malloc(sizeof(struct my_game));
  new->name = name;
  new->team1 = team1;
  new->team2 = team2;
  new->score1 = score1;
  new->score2 = score2;
  return new;
}

void deletes_match(match game)
{
  if (game)
  {
    free(game->name);
    free(game->team1);
    free(game->team2);
    free(game);
  }
  else
  {
    
  }

}

dl_list create_dl_list()
{
  dl_list lst = malloc(sizeof(struct doubly_linked_list));
  lst->size = 0;
  lst->head = 0;
  lst->tail = 0;
  return lst;
}

dl_link create_dl_node(dl_link next, dl_link previous, match game)
{
  dl_link new = malloc(sizeof(struct dl_node));
  new->value = game;
  new->next = next;
  new->previous = previous;
  if (previous != 0)
  {
    previous->next = new;
  }
  else
  {
    
  }

  if (next != 0)
  {
    next->previous = new;
  }
  else
  {
    
  }

  return new;
}

void deletes_dl_node(dl_link node)
{
  deletes_match(get_node_match(node));
  free(node);
}

int dl_list_length(dl_list lst)
{
  return (lst != 0) ? (lst->size) : (0);
}

int dl_list_is_empty(dl_list lst)
{
  return dl_list_length(lst) == 0;
}

int dl_list_is_valid(dl_list lst)
{
  return (lst != 0) ? (1) : (0);
}

match get_node_match(dl_link node)
{
  return (node != 0) ? (node->value) : (0);
}

void insert_begin(dl_list lst, match game)
{
  dl_link new = create_dl_node(lst->head, 0, game);
  lst->head = new;
  if (dl_list_is_empty(lst))
  {
    lst->tail = new;
  }
  else
  {
    
  }

  lst->size++;
}

void remove_begin(dl_list lst)
{
  dl_link old_head = 0;
  if ((!dl_list_is_valid(lst)) || dl_list_is_empty(lst))
  {
    return;
  }
  else
  {
    
  }

  old_head = lst->head;
  lst->head = old_head->next;
  if (lst->head != 0)
  {
    lst->head->previous = 0;
  }
  else
  {
    lst->tail = 0;
  }

  deletes_dl_node(old_head);
  lst->size--;
}

void remove_end(dl_list lst)
{
  dl_link old_tail = 0;
  if ((!dl_list_is_valid(lst)) || dl_list_is_empty(lst))
  {
    return;
  }
  else
  {
    
  }

  old_tail = lst->tail;
  lst->tail = old_tail->previous;
  if (lst->tail != 0)
  {
    lst->tail->next = 0;
  }
  else
  {
    lst->head = 0;
  }

  deletes_dl_node(old_tail);
  lst->size--;
}

void remove_node(dl_list lst, dl_link del_node)
{
  if ((!dl_list_is_valid(lst)) || dl_list_is_empty(lst))
  {
    return;
  }
  else
  {
    
  }

  if (del_node == 0)
  {
    return;
  }
  else
  {
    
  }

  if (del_node == lst->head)
  {
    remove_begin(lst);
  }
  else
  {
    if (del_node == lst->tail)
    {
      remove_end(lst);
    }
    else
    {
      del_node->previous->next = del_node->next;
      del_node->next->previous = del_node->previous;
      deletes_dl_node(del_node);
      lst->size--;
    }

  }

}

void dl_list_destroy(dl_list lst)
{
  dl_link ite;
  dl_link ite_aux;
  if (!dl_list_is_valid(lst))
  {
    return;
  }
  else
  {
    
  }

  if (!dl_list_is_empty(lst))
  {
    for (ite = lst->head, ite_aux = lst->head->next; ite != 0; ite_aux = ite->next, deletes_dl_node(ite), ite = ite_aux)
      ;

  }
  else
  {
    
  }

  free(lst);
}
