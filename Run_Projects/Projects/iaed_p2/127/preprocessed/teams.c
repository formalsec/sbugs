/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams.h"
#include "games.h"


team *create_team(char *name)
{
  team *new_team;
  new_team = malloc(sizeof(team));
  new_team->name = malloc((sizeof(char)) * (strlen(name) + 1));
  strcpy(new_team->name, name);
  new_team->nr_wins = 0;
  new_team->next = 0;
  return new_team;
}

void table_t_init(team **team_t, long int m)
{
  long int i;
  for (i = 0; i < m; i++)
    *(team_t + i) = 0;

}

team **add_team_to_table(team **teams_t, team *t, long int *max_len)
{
  long int m = *(max_len + 2);
  long int hash;
  hash = table_hash(t->name, m);
  while ((*(teams_t + hash)) != 0)
    hash = (hash + 1) % m;

  *(teams_t + hash) = t;
  (*(max_len + 3))++;
  if ((*(max_len + 3)) > (m / 2))
  {
    return expand_t(teams_t, max_len);
  }
  else
  {
    return teams_t;
  }

}

team **expand_t(team **teams_tab, long int *max_len)
{
  long int i;
  long int old_m;
  team **new_tab = malloc(((sizeof(link)) * (*(max_len + 2))) * 2);
  old_m = *(max_len + 2);
  *(max_len + 2) = (*(max_len + 2)) * 2;
  table_t_init(new_tab, *(max_len + 2));
  for (i = 0; i < old_m; i++)
    if ((*(teams_tab + i)) != 0)
  {
    add_team_to_table(new_tab, *(teams_tab + i), max_len);
    (*(max_len + 3))--;
  }
  else
  {
    
  }


  free(teams_tab);
  return new_tab;
}

team *search_t(char *team_name, team **teams_tab, long int m)
{
  long int i = table_hash(team_name, m);
  while ((*(teams_tab + i)) != 0)
  {
    if (strcmp(team_name, (*(teams_tab + i))->name) == 0)
    {
      return *(teams_tab + i);
    }
    else
    {
      i = (i + 1) % m;
    }

  }

  return 0;
}

void destroy_team_st(team *last_team)
{
  team *t = last_team;
  team *aux;
  while (t != 0)
  {
    aux = t->next;
    free(t->name);
    free(t);
    t = aux;
  }

}

