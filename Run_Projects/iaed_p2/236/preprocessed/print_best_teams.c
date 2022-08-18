/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "structures.h"


void merge_sort(char *arr[], int l, int r);
void printBestTeams(team *team_hash_table[], int NL)
{
  int wins;
  int size;
  int iter;
  int i;
  team *tmp_team;
  char **names;
  wins = 0;
  for (i = 0; i < 1000; ++i)
  {
    tmp_team = team_hash_table[i];
    while (tmp_team != 0)
    {
      if (tmp_team->wins > wins)
      {
        wins = tmp_team->wins;
      }
      else
      {
        
      }

      tmp_team = tmp_team->next;
    }

  }

  iter = 0;
  size = 0;
  for (i = 0; i < 1000; ++i)
  {
    tmp_team = team_hash_table[i];
    while (tmp_team != 0)
    {
      if (tmp_team->wins == wins)
      {
        {
          size++;
        }
      }
      else
      {
        
      }

      tmp_team = tmp_team->next;
    }

  }

  names = malloc(size * (sizeof(char *)));
  if (size != 0)
  {
    {
      for (i = 0; i < 1000; ++i)
      {
        tmp_team = team_hash_table[i];
        while (tmp_team != 0)
        {
          if (tmp_team->wins == wins)
          {
            {
              names[iter] = tmp_team->name;
              iter++;
            }
          }
          else
          {
            
          }

          tmp_team = tmp_team->next;
        }

      }

      merge_sort(names, 0, size - 1);
      printf("%d Melhores %d\n", NL, wins);
      for (i = 0; i < size; ++i)
      {
        printf("%d * %s\n", NL, names[i]);
      }

    }
  }
  else
  {
    
  }

  free(names);
  free(tmp_team);
}

