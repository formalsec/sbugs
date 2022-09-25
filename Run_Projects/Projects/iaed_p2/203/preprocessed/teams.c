/*File generated by PreProcessor.py*/


#include "teams.h"


int get_list_size(Teams *head)
{
  int count = 0;
  Teams *current = head;
  while (current != 0)
  {
    count++;
    current = current->next;
  }

  return count;
}

Teams *add_team_to_list(Teams **head, char *name)
{
  Teams *new_team = (Teams *) malloc(sizeof(Teams));
  Teams *current = *head;
  memcpy(new_team->team_name, name, strlen(name) + 1);
  new_team->matches_won = 0;
  new_team->next = 0;
  if ((*head) == 0)
  {
    *head = new_team;
  }
  else
  {
    while (current->next != 0)
      current = current->next;

    current->next = new_team;
  }

  return *head;
}

Teams *delete_team_from_list(Teams **head, char *t_name)
{
  Teams *current;
  Teams *prev;
  prev = 0;
  for (current = *head; current != 0; prev = current, current = current->next)
  {
    if (strcmp(current->team_name, t_name) == 0)
    {
      if (prev == 0)
      {
        *head = current->next;
      }
      else
      {
        prev->next = current->next;
      }

      free(current);
      return *head;
    }
    else
    {
      
    }

  }

  return *head;
}

Teams *add_team_highest(Teams **teams_highest, Teams **teams, int highest_won)
{
  Teams *current;
  for (current = *teams; current != 0; current = current->next)
  {
    if (current->matches_won == highest_won)
    {
      *teams_highest = add_team_to_list(teams_highest, current->team_name);
    }
    else
    {
      
    }

  }

  sort_teams_alpha(teams_highest);
  return *teams_highest;
}

Teams *increment_matches_won(Teams **head, char *name)
{
  Teams *current;
  for (current = *head; current != 0; current = current->next)
  {
    if (strcmp(current->team_name, name) == 0)
    {
      current->matches_won++;
    }
    else
    {
      
    }

  }

  return *head;
}

Teams *decrement_matches_won(Teams **head, char *name)
{
  Teams *current;
  for (current = *head; current != 0; current = current->next)
  {
    if (strcmp(current->team_name, name) == 0)
    {
      current->matches_won--;
    }
    else
    {
      
    }

  }

  return *head;
}

bool team_exists(Teams **head, char *name)
{
  Teams *current;
  for (current = *head; current != 0; current = current->next)
  {
    if (strcmp(current->team_name, name) == 0)
    {
      return true;
    }
    else
    {
      
    }

  }

  return false;
}

int max_won(Teams **head)
{
  int max = 0;
  Teams *current;
  for (current = *head; current != 0; current = current->next)
  {
    if (max < current->matches_won)
    {
      max = current->matches_won;
    }
    else
    {
      
    }

  }

  return max;
}

void print_matches_won(Teams **head, char *name)
{
  Teams *current;
  for (current = *head; current != 0; current = current->next)
  {
    if (strcmp(current->team_name, name) == 0)
    {
      printf("%s %d\n", current->team_name, current->matches_won);
    }
    else
    {
      
    }

  }

}

void print_team_list(int nl, Teams *head)
{
  Teams *current = head;
  while (current != 0)
  {
    printf("%d * %s\n", nl, current->team_name);
    current = current->next;
  }

}

void free_teams(Teams *head)
{
  Teams *tmp;
  while (head != 0)
  {
    tmp = head;
    head = head->next;
    free(tmp);
  }

}

void sort_teams_alpha(Teams **head)
{
  Teams *current;
  char *tmp = malloc(1024);
  current = *head;
  if (current)
  {
    while (current && current->next)
    {
      memset(tmp, 0, 1024);
      if (strcmp(current->team_name, current->next->team_name) > 0)
      {
        strcpy(tmp, current->team_name);
        strcpy(current->team_name, current->next->team_name);
        strcpy(current->next->team_name, tmp);
      }
      else
      {
        
      }

      current = current->next;
    }

  }
  else
  {
    
  }

  free(tmp);
}

