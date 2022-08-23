/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams.h"
#include "besteams.h"
#include "shared.h"


void init_list_teams(char **best_teams, int N)
{
  int i;
  for (i = 0; i < N; i++)
  {
    best_teams[i] = 0;
  }

}

void clear_list_teams(char **best_teams, int N)
{
  char *i;
  int j;
  for (j = 0; (best_teams[j] != 0) && (j < N); j++)
  {
    i = best_teams[j];
    free(i);
    best_teams[j] = 0;
  }

}

void search_and_add_teams_list(teams **lst_teams, char **best_teams, int number)
{
  teams *i;
  int j;
  int n = 0;
  for (j = 0; j < 517; j++)
  {
    for (i = lst_teams[j]; i != 0; i = i->next)
    {
      if (i->games_w == number)
      {
        {
          best_teams[n] = strduplicate(i->name);
          n++;
        }
      }
      else
      {
        
      }

    }

  }

}

void free_list_teams(char **best_teams)
{
  int j;
  for (j = 0; (j < 100) && (best_teams[j] != 0); j++)
  {
    free(best_teams[j]);
  }

  free(best_teams);
}

void print_best_teams(char **best_teams, int nl, int max)
{
  int i = 0;
  if (best_teams[0] != 0)
  {
    {
      printf("%d Melhores %d\n", nl, max);
    }
  }
  else
  {
    
  }

  for (; best_teams[i] != 0; i++)
  {
    printf("%d * %s\n", nl, best_teams[i]);
  }

}

int cmpstrings(const void *a, const void *b)
{
  char **str1;
  char **str2;
  str1 = (char **) a;
  str2 = (char **) b;
  return strcmp(*str1, *str2);
}

void sort_the_list(char **best_teams)
{
  int j = 0;
  int n = 0;
  for (; best_teams[j] != 0; j++)
  {
    n++;
  }

  if (n > 1)
  {
    {
      qsort(best_teams, n, sizeof(char *), cmpstrings);
    }
  }
  else
  {
    
  }

}

