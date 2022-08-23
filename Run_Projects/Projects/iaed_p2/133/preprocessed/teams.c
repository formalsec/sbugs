/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams.h"
#include "shared.h"


void init_teams(teams **lst_teams, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    lst_teams[i] = 0;
  }

}

teams *new_team(teams *team, char *name)
{
  team->name = strduplicate(name);
  team->games_w = 0;
  team->next = 0;
  return team;
}

void add_victory(teams **lst_teams, char *name)
{
  teams *team = get_team(lst_teams, name);
  team->games_w++;
}

void remove_victory(teams **lst_teams, char *name)
{
  teams *team = get_team(lst_teams, name);
  team->games_w--;
}

int look_team(teams **lst_teams, char *name)
{
  int i = hash(name);
  teams *head = lst_teams[i];
  for (; head != 0; head = head->next)
  {
    if (strcmp(head->name, name) == 0)
    {
      return 1;
    }
    else
    {
      
    }

  }

  return 0;
}

void insert_new_team(teams **lst_teams, teams *new)
{
  teams *head;
  int i;
  i = hash(new->name);
  head = lst_teams[i];
  lst_teams[i] = new;
  new->next = head;
}

teams *get_team(teams **lst_teams, char *name)
{
  int i = hash(name);
  teams *head = lst_teams[i];
  for (; head != 0; head = head->next)
  {
    if (strcmp(head->name, name) == 0)
    {
      {
        return head;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

int most_wins(teams **lst_teams)
{
  int i = 0;
  int best_res = 0;
  teams *head;
  for (i = 0; i <= 517; i++)
  {
    for (head = lst_teams[i]; head != 0; head = head->next)
    {
      if (head->games_w > best_res)
      {
        {
          best_res = head->games_w;
        }
      }
      else
      {
        
      }

    }

  }

  return best_res;
}

void clear_the_teams(teams **lst_teams)
{
  teams *i;
  teams *follow;
  int j;
  for (j = 0; j < 517; j++)
  {
    for (i = lst_teams[j], follow = i; follow != 0;)
    {
      i = follow;
      follow = i->next;
      free(i->name);
      free(i);
    }

  }

  free(lst_teams);
}

