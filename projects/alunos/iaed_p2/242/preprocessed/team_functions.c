#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "team_functions.h"
#include "game_functions.h"


int hash(char *name)
{
  int h;
  int a;
  int b;
  a = 31415;
  b = 27183;
  for (h = 0; (*name) != '\0'; name++, a = (a * b) % (1997 - 1))
  {
    h = ((a * h) + (*name)) % 1997;
  }

  return h;
}

void init_hash_table_team(team **hash_table_team)
{
  int i;
  for (i = 0; i < 1997; i++)
  {
    hash_table_team[i] = 0;
  }

}

team *new_team(char *new_name, int n_wins)
{
  team *x = malloc(sizeof(struct stru_team));
  x->name = malloc(((sizeof(char)) * strlen(new_name)) + 1);
  strcpy(x->name, new_name);
  x->wins = n_wins;
  x->next = 0;
  return x;
}

team *insertBeginList_team(team *head, char *t_name, int wins)
{
  team *x;
  x = new_team(t_name, wins);
  x->next = head;
  return x;
}

void HTinsert_team(char *t_name, team **hash_table_team)
{
  int index;
  index = hash(t_name);
  hash_table_team[index] = insertBeginList_team(hash_table_team[index], t_name, 0);
}

team *hash_table_lookup_team(char *name, team **hash_table_team)
{
  int index = hash(name);
  team *tmp = hash_table_team[index];
  while (tmp && (strcmp(tmp->name, name) != 0))
  {
    tmp = tmp->next;
  }

  return tmp;
}

void cmd_A(char *t_name, int NL, team **hash_table_team)
{
  if (hash_table_lookup_team(t_name, hash_table_team) != 0)
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    HTinsert_team(t_name, hash_table_team);
  }

}

void cmd_P(char *t_name, int NL, team **hash_table_team)
{
  if (hash_table_lookup_team(t_name, hash_table_team) != 0)
  {
    team *tmp = hash_table_lookup_team(t_name, hash_table_team);
    printf("%d %s %d\n", NL, tmp->name, tmp->wins);
  }
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

}

int get_max(team **hash_t)
{
  int max = 0;
  int i;
  team *tmp;
  for (i = 0; i < 1997; i++)
  {
    tmp = hash_t[i];
    while (tmp != 0)
    {
      if (tmp->wins > max)
      {
        max = tmp->wins;
      }
      else
      {
        
      }

      tmp = tmp->next;
    }

  }

  return max;
}

team *insert_alpha(team *head, char *t_name, int wins)
{
  team *current;
  team *x;
  x = new_team(t_name, wins);
  if ((head == 0) || (strcmp(head->name, t_name) > 0))
  {
    x->next = head;
    return x;
  }
  else
  {
    current = head;
    while ((current->next != 0) && (strcmp(current->next->name, x->name) < 0))
    {
      current = current->next;
    }

    x->next = current->next;
    current->next = x;
    return head;
  }

}

void print_max(team **max_teams, int NL)
{
  team *tmp = *max_teams;
  if (tmp != 0)
  {
    printf("%d Melhores %d\n", NL, tmp->wins);
    while (tmp != 0)
    {
      printf("%d * %s\n", NL, tmp->name);
      tmp = tmp->next;
    }

  }
  else
  {
    
  }

}

void cmd_g(team **max_teams, int NL, team **hash_t_team)
{
  int max = get_max(hash_t_team);
  int i;
  team *tmp;
  for (i = 0; i < 1997; i++)
  {
    tmp = hash_t_team[i];
    while (tmp != 0)
    {
      if (tmp->wins == max)
      {
        *max_teams = insert_alpha(*max_teams, tmp->name, tmp->wins);
      }
      else
      {
        
      }

      tmp = tmp->next;
    }

  }

  print_max(max_teams, NL);
  destroy_teams_lst(max_teams);
}

void FREEnode_team(team *t)
{
  free(t->name);
  free(t);
}

team *pop_team(team *head)
{
  team *aux;
  aux = head;
  head = aux->next;
  FREEnode_team(aux);
  return head;
}

void destroy_teams_lst(team **list_t)
{
  while ((*list_t) != 0)
  {
    *list_t = pop_team(*list_t);
  }

}

void destroy_teams(team **hash_table_team)
{
  int i;
  for (i = 0; i < 1997; i++)
  {
    while (hash_table_team[i] != 0)
    {
      hash_table_team[i] = pop_team(hash_table_team[i]);
    }

  }

}
