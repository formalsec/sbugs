#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "teams.h"


team_table *init_teams()
{
  int i;
  team_table *teams = malloc(sizeof(team_table));
  for (i = 0; i < 1009; i++)
  {
    teams->table[i] = 0;
  }

  teams->len_top_winners = 10;
  teams->top_winners_names = malloc(10 * (sizeof(char *)));
  return teams;
}

int hash_team(char *name)
{
  int key;
  int i;
  for (key = 0, i = 0; name[i] != '\0'; i++)
  {
    key += (1023 - i) * name[i];
  }

  key = key % 1009;
  return key;
}

void push_team(team_table *teams, team *team)
{
  int key;
  team_node *taken_node;
  team_node *new_node = malloc(sizeof(team_node));
  key = hash_team(team->name);
  new_node->team = team;
  new_node->next_node = 0;
  if (teams->table[key] == 0)
  {
    teams->table[key] = new_node;
    new_node->previous_node = 0;
  }
  else
  {
    taken_node = teams->table[key];
    while (taken_node->next_node != 0)
    {
      taken_node = taken_node->next_node;
    }

    taken_node->next_node = new_node;
    new_node->previous_node = taken_node;
  }

}

void new_team(team_table *teams, char *name)
{
  team *new_team = malloc(sizeof(team));
  new_team->name = name;
  new_team->won_games = 0;
  push_team(teams, new_team);
  update_team_wins(new_team, 0);
}

team *get_team(team_table *teams, char *name)
{
  int key;
  team_node *node;
  key = hash_team(name);
  node = teams->table[key];
  while (node != 0)
  {
    if (!strcmp(node->team->name, name))
    {
      return node->team;
    }
    else
    {
      
    }

    node = node->next_node;
  }

  return 0;
}

char *get_team_name(team *team)
{
  return team->name;
}

int same_team(team *team_1, team *team_2)
{
  if (!strcmp(team_1->name, team_2->name))
  {
    return 1;
  }
  else
  {
    
  }

  return 0;
}

void update_team_wins(team *team, int value)
{
  team->won_games += value;
}

void print_team(team *team)
{
  printf("%s %d\n", team->name, team->won_games);
}

char **get_top_winners_names(team_table *teams)
{
  int i;
  int no_top_winners = 0;
  int max_no_wins = 0;
  team_node *node;
  for (i = 0; i < 1009; i++)
  {
    if ((node = teams->table[i]) != 0)
    {
      while (node != 0)
      {
        if (node->team->won_games == max_no_wins)
        {
          if ((++no_top_winners) >= teams->len_top_winners)
          {
            teams->len_top_winners += 10;
            teams->top_winners_names = realloc(teams->top_winners_names, teams->len_top_winners * (sizeof(char *)));
          }
          else
          {
            
          }

          teams->top_winners_names[no_top_winners - 1] = node->team->name;
        }
        else
        {
          if (node->team->won_games > max_no_wins)
          {
            no_top_winners = 1;
            max_no_wins = node->team->won_games;
            teams->top_winners_names[0] = node->team->name;
          }
          else
          {
            
          }

        }

        node = node->next_node;
      }

    }
    else
    {
      
    }

  }

  teams->top_winners_names[no_top_winners] = 0;
  teams->max_no_wins = max_no_wins;
  qsort(teams->top_winners_names, no_top_winners, sizeof(char *), compare_names);
  return teams->top_winners_names;
}

int compare_names(const void *pointer_1, const void *pointer_2)
{
  const char *name_1 = *((const char **) pointer_1);
  const char *name_2 = *((const char **) pointer_2);
  return strcmp(name_1, name_2);
}

int get_max_win_number(team_table *teams)
{
  return teams->max_no_wins;
}

void free_teams(team_table *teams)
{
  int i;
  team_node *node;
  team_node *tmp;
  for (i = 0; i < 1009; i++)
  {
    if (teams->table[i] != 0)
    {
      node = teams->table[i];
      while (node != 0)
      {
        free(node->team->name);
        free(node->team);
        tmp = node->next_node;
        free(node);
        node = tmp;
      }

    }
    else
    {
      
    }

  }

  free(teams->top_winners_names);
  free(teams);
}

