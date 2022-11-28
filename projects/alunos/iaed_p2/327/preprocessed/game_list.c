#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include "game_list.h"


game_node *mk_game_node(game *gm)
{
  game_node *node = malloc(sizeof(game_node));
  node->gm = gm;
  node->prev = 0;
  node->next = 0;
  return node;
}

void free_game_node(game_node *node)
{
  free_game(node->gm);
  free(node);
  return;
}

game_list *mk_game_list()
{
  game_list *lst = malloc(sizeof(game_list));
  lst->head = 0;
  lst->last = 0;
  return lst;
}

game_node *add_game_list(game_list *lst, game *gm)
{
  game_node *node = mk_game_node(gm);
  node->prev = lst->last;
  if (lst->last)
  {
    lst->last->next = node;
  }
  else
  {
    lst->head = node;
  }

  lst->last = node;
  return node;
}

void print_game_list(int NL, game_list *lst)
{
  game_node *node = lst->head;
  while (node)
  {
    print_game(NL, node->gm);
    node = node->next;
  }

  return;
}

void rm_game_list(game_list *lst, game_node *node)
{
  if (node->prev)
  {
    node->prev->next = node->next;
  }
  else
  {
    lst->head = node->next;
  }

  if (node->next)
  {
    node->next->prev = node->prev;
  }
  else
  {
    lst->last = node->prev;
  }

  free_game_node(node);
  return;
}

void free_game_list(game_list *lst)
{
  game_node *node = lst->head;
  game_node *next;
  while (node)
  {
    next = node->next;
    free_game_node(node);
    node = next;
  }

  free(lst);
  return;
}
