#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "team_functions.h"
#include "game_functions.h"


void init_hash_table_game(game **hash_table_game)
{
  int i;
  for (i = 0; i < 1997; i++)
  {
    hash_table_game[i] = 0;
  }

}

game *new_game(char *n_name, char *n_t1, char *n_t2, int n_g_t1, int n_g_t2)
{
  game *x = malloc(sizeof(struct stru_game));
  x->name = malloc(((sizeof(char)) * strlen(n_name)) + 1);
  x->t1 = malloc(((sizeof(char)) * strlen(n_t1)) + 1);
  x->t2 = malloc(((sizeof(char)) * strlen(n_t2)) + 1);
  strcpy(x->name, n_name);
  strcpy(x->t1, n_t1);
  strcpy(x->t2, n_t2);
  x->g_t1 = n_g_t1;
  x->g_t2 = n_g_t2;
  x->next = 0;
  return x;
}

game *insertBeginList_game(game *head, char *name, char *t1, char *t2, int g_t1, int g_t2)
{
  game *x;
  x = new_game(name, t1, t2, g_t1, g_t2);
  x->next = head;
  return x;
}

void insert_node(nodeGame **game_order, game *n_game)
{
  nodeGame *new_node = (nodeGame *) malloc(sizeof(nodeGame));
  new_node->Game = n_game;
  new_node->next = *game_order;
  new_node->prev = 0;
  if ((*game_order) != 0)
  {
    (*game_order)->prev = new_node;
  }
  else
  {
    
  }

  *game_order = new_node;
}

void HTinsert_game(char *name, char *t1, char *t2, int g_t1, int g_t2, game **hash_table_game, nodeGame **game_order)
{
  int index;
  index = hash(name);
  hash_table_game[index] = insertBeginList_game(hash_table_game[index], name, t1, t2, g_t1, g_t2);
  insert_node(game_order, hash_table_game[index]);
}

game *hash_table_lookup_game(char *name, game **hash_table_game)
{
  int index = hash(name);
  game *tmp = hash_table_game[index];
  while (tmp && (strcmp(tmp->name, name) != 0))
  {
    tmp = tmp->next;
  }

  return tmp;
}

void cmd_a(char *name, char *t1, char *t2, int g_t1, int g_t2, int NL, game **H_T_game, team **H_T_team, nodeGame **game_order)
{
  team *aux;
  if (hash_table_lookup_game(name, H_T_game))
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    if (!(hash_table_lookup_team(t1, H_T_team) && hash_table_lookup_team(t2, H_T_team)))
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      HTinsert_game(name, t1, t2, g_t1, g_t2, H_T_game, game_order);
      if (g_t1 > g_t2)
      {
        aux = hash_table_lookup_team(t1, H_T_team);
        aux->wins++;
      }
      else
      {
        if (g_t1 < g_t2)
        {
          aux = hash_table_lookup_team(t2, H_T_team);
          aux->wins++;
        }
        else
        {
          
        }

      }

    }

  }

}

void cmd_p(char *g, int NL, game **hash_table_game)
{
  if (hash_table_lookup_game(g, hash_table_game) != 0)
  {
    game *tmp = hash_table_lookup_game(g, hash_table_game);
    printf("%d %s %s %s %d %d\n", NL, tmp->name, tmp->t1, tmp->t2, tmp->g_t1, tmp->g_t2);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void cmd_l(nodeGame *game_order, int NL)
{
  nodeGame *aux;
  aux = game_order;
  while (aux != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, aux->Game->name, aux->Game->t1, aux->Game->t2, aux->Game->g_t1, aux->Game->g_t2);
    aux = aux->next;
  }

}

void cmd_s(team **hash_table_team, game **hash_table_game, char *name, int g_t1, int g_t2, int NL)
{
  team *tmp_t;
  game *tmp_g;
  tmp_g = hash_table_lookup_game(name, hash_table_game);
  if (tmp_g != 0)
  {
    if (tmp_g->g_t1 > tmp_g->g_t2)
    {
      if (g_t1 == g_t2)
      {
        tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
        tmp_t->wins--;
      }
      else
      {
        if (g_t1 < g_t2)
        {
          tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
          tmp_t->wins--;
          tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
          tmp_t->wins++;
        }
        else
        {
          
        }

      }

    }
    else
    {
      if (tmp_g->g_t1 == tmp_g->g_t2)
      {
        if (g_t1 > g_t2)
        {
          tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
          tmp_t->wins++;
        }
        else
        {
          if (g_t1 < g_t2)
          {
            tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
            tmp_t->wins++;
          }
          else
          {
            
          }

        }

      }
      else
      {
        if (tmp_g->g_t1 < tmp_g->g_t2)
        {
          if (g_t1 > g_t2)
          {
            tmp_t = hash_table_lookup_team(tmp_g->t1, hash_table_team);
            tmp_t->wins++;
            tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
            tmp_t->wins--;
          }
          else
          {
            if (g_t1 == g_t2)
            {
              tmp_t = hash_table_lookup_team(tmp_g->t2, hash_table_team);
              tmp_t->wins--;
            }
            else
            {
              
            }

          }

        }
        else
        {
          
        }

      }

    }

    tmp_g->g_t1 = g_t1;
    tmp_g->g_t2 = g_t2;
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void FREEnode_game(game *t)
{
  free(t->name);
  free(t->t1);
  free(t->t2);
  free(t);
}

game *pop_game(game *head)
{
  game *aux;
  aux = head;
  head = aux->next;
  FREEnode_game(aux);
  return head;
}

void destroy_games(game **hash_table_game)
{
  int i;
  for (i = 0; i < 1997; i++)
  {
    while (hash_table_game[i] != 0)
    {
      hash_table_game[i] = pop_game(hash_table_game[i]);
    }

  }

}

nodeGame *pop_node(nodeGame *head)
{
  nodeGame *aux;
  aux = head;
  head = aux->next;
  free(aux);
  return head;
}

void destroy_order(nodeGame **game_order)
{
  while ((*game_order) != 0)
  {
    *game_order = pop_node(*game_order);
  }

}

game *delete_1game(game *head, char *name)
{
  game *t;
  game *prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->next)
  {
    if (strcmp(t->name, name) == 0)
    {
      if (t == head)
      {
        head = t->next;
      }
      else
      {
        prev->next = t->next;
      }

      FREEnode_game(t);
      return head;
    }
    else
    {
      
    }

  }

  return head;
}

void delete_node(nodeGame **game_order, char *txt)
{
  nodeGame *t;
  for (t = *game_order; t != 0; t = t->next)
  {
    if (strcmp(t->Game->name, txt) == 0)
    {
      if (t == (*game_order))
      {
        *game_order = t->next;
      }
      else
      {
        
      }

      if (t->next != 0)
      {
        t->next->prev = t->prev;
      }
      else
      {
        
      }

      if (t->prev != 0)
      {
        t->prev->next = t->next;
      }
      else
      {
        
      }

      free(t);
      return;
    }
    else
    {
      
    }

  }

  return;
}

void reverse(nodeGame **list)
{
  nodeGame *temp = 0;
  nodeGame *current = *list;
  while (current != 0)
  {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }

  if (temp != 0)
  {
    *list = temp->prev;
  }
  else
  {
    
  }

}

void cmd_r(team **H_T_team, game **H_T_game, char *name, int NL, nodeGame **game_order)
{
  team *tmp_t;
  game *tmp_g;
  int index;
  tmp_g = hash_table_lookup_game(name, H_T_game);
  if (tmp_g != 0)
  {
    if (tmp_g->g_t1 > tmp_g->g_t2)
    {
      tmp_t = hash_table_lookup_team(tmp_g->t1, H_T_team);
      tmp_t->wins--;
    }
    else
    {
      if (tmp_g->g_t1 < tmp_g->g_t2)
      {
        tmp_t = hash_table_lookup_team(tmp_g->t2, H_T_team);
        tmp_t->wins--;
      }
      else
      {
        
      }

    }

    index = hash(name);
    delete_node(game_order, name);
    H_T_game[index] = delete_1game(H_T_game[index], name);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

