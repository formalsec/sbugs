#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "matches.h"
#include "teams.h"
#include "aux.h"
#include <string.h>


int hash(char *desc, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*desc) != '\0'; desc++, a = (a * b) % (M - 1))
    h = ((a * h) + (*desc)) % M;

  return h;
}

void change_victories(node_team *n_team1, node_team *n_team2, int old_score[2], int new_score[2])
{
  if (!((((old_score[0] < old_score[1]) && (new_score[0] < new_score[1])) || ((old_score[0] > old_score[1]) && (new_score[0] > new_score[1]))) || ((old_score[0] == old_score[1]) && (new_score[0] == new_score[1]))))
  {
    if ((old_score[0] > old_score[1]) && (new_score[0] == new_score[1]))
    {
      n_team1->victories = n_team1->victories - 1;
    }
    else
    {
      if ((old_score[0] < old_score[1]) && (new_score[0] == new_score[1]))
      {
        n_team2->victories = n_team2->victories - 1;
      }
      else
      {
        if (old_score[0] > old_score[1])
        {
          n_team1->victories = n_team1->victories - 1;
          n_team2->victories = n_team2->victories + 1;
        }
        else
        {
          if (old_score[0] < old_score[1])
          {
            n_team1->victories = n_team1->victories + 1;
            n_team2->victories = n_team2->victories - 1;
          }
          else
          {
            if (old_score[0] == old_score[1])
            {
              if (new_score[0] < new_score[1])
              {
                n_team2->victories = n_team2->victories + 1;
              }
              else
              {
                n_team1->victories = n_team1->victories + 1;
              }

            }
            else
            {
              
            }

          }

        }

      }

    }

  }
  else
  {
    
  }

}

void inicialize_lists(hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_teams *linked_teams, linked_list_matches *linked_matches)
{
  int i;
  for (i = 0; i < 1000; i++)
  {
    hash_teams->nodes[i] = 0;
    hash_matches->nodes[i] = 0;
  }

  linked_teams->head = 0;
  linked_teams->last = 0;
  linked_matches->head = 0;
  linked_matches->last = 0;
}

void destroy(hash_table_teams *hash_teams, hash_table_matches *hash_matches, linked_list_teams *linked_teams, linked_list_matches *linked_matches)
{
  destroy_hash_teams(hash_teams);
  destroy_linked_teams(linked_teams);
  destroy_hash_matches(hash_matches);
  destroy_linked_matches(linked_matches);
}

int less(char x[], char y[])
{
  return (strcmp(x, y) < 0) ? (1) : (0);
}

void merge(node_team *a[], node_team *aux[], int l, int m, int r)
{
  int i;
  int j;
  int k;
  for (i = m + 1; i > l; i--)
    aux[i - 1] = a[i - 1];

  for (j = m; j < r; j++)
    aux[(r + m) - j] = a[j + 1];

  for (k = l; k <= r; k++)
  {
    if (less(aux[j]->desc, aux[i]->desc))
    {
      a[k] = aux[j--];
    }
    else
    {
      a[k] = aux[i++];
    }

  }

}

void merge_sort(node_team *a[], node_team *aux[], int l, int r)
{
  int m = (r + l) / 2;
  if (r <= l)
  {
    return;
  }
  else
  {
    
  }

  merge_sort(a, aux, l, m);
  merge_sort(a, aux, m + 1, r);
  merge(a, aux, l, m, r);
}

