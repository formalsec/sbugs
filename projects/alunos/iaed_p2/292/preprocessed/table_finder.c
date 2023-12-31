#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "functions.h"


long int hash(char palavra[], int M)
{
  int i = 0;
  int sum = 0;
  while (palavra[i] != '\0')
  {
    sum += 3 ^ ((i + 3) * ((int) palavra[i]));
    ++i;
  }

  sum = sum % M;
  return sum;
}

struct Jogos *encontraJogo(struct Jogos **jogos, char nome[], bool print, int M, int NL, struct Jogos *false_g)
{
  struct Jogos *next;
  int x = hash(nome, M);
  next = jogos[x];
  while (next != 0)
  {
    if (!strcmp(nome, next->ID))
    {
      if (print)
      {
        printf("%d %s %s %s %d %d\n", NL, next->ID, next->team_1, next->team_2, next->score1, next->score2);
      }
      else
      {
        
      }

      return next;
    }
    else
    {
      
    }

    next = next->next_tabela;
  }

  if (print)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    
  }

  return false_g;
}

struct Equipas *encontraEquipa(struct Equipas **Team, char nome[], bool print, int N, int NL, struct Equipas *false_t)
{
  struct Equipas *nt;
  int x = hash(nome, N);
  nt = Team[x];
  while (nt != 0)
  {
    if (!strcmp(nome, nt->ID))
    {
      if (print)
      {
        printf("%d %s %d\n", NL, nt->ID, nt->wins);
      }
      else
      {
        
      }

      return nt;
    }
    else
    {
      
    }

    nt = nt->next;
  }

  if (print)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    
  }

  return false_t;
}

void showByDate(struct Jogos *jogos, int NL)
{
  while (jogos != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, jogos->ID, jogos->team_1, jogos->team_2, jogos->score1, jogos->score2);
    jogos = jogos->next;
  }

  return;
}

int compara_palavras(const void *team_A, const void *team_B)
{
  const char *teamA = *((const char **) team_A);
  const char *teamB = *((const char **) team_B);
  return strcmp(teamA, teamB);
}

void lista(struct Equipas **elemento, int Nequipas, int NL, int max, int N)
{
  int i;
  int p = 0;
  int count = 0;
  char **tabela;
  if (Nequipas == 0)
  {
    return;
  }
  else
  {
    
  }

  tabela = (char **) malloc(Nequipas * (sizeof(char *)));
  for (i = 0; i < N; i++)
  {
    if (elemento[i] != 0)
    {
      struct Equipas *temp = elemento[i];
      while (temp != 0)
      {
        if ((*temp).wins == max)
        {
          tabela[p] = malloc((strlen((*temp).ID) + 1) * (sizeof(char)));
          strcpy(tabela[p], (*temp).ID);
          ++count;
          ++p;
          temp = temp->next;
        }
        else
        {
          temp = temp->next;
        }

      }

    }
    else
    {
      
    }

  }

  qsort(tabela, count, sizeof(char *), compara_palavras);
  printf("%d Melhores %d\n", NL, max);
  for (i = 0; i < count; i++)
  {
    printf("%d * %s\n", NL, tabela[i]);
  }

  for (i = 0; i < count; i++)
    free(tabela[i]);

  free(tabela);
}

int FindMax(struct Equipas **games_list, int N)
{
  int i;
  int max = 0;
  for (i = 0; i < N; i++)
  {
    if (games_list[i] != 0)
    {
      struct Equipas *temp = games_list[i];
      while (temp != 0)
      {
        if (temp->wins > max)
        {
          max = temp->wins;
        }
        else
        {
          
        }

        temp = temp->next;
      }

    }
    else
    {
      
    }

  }

  return max;
}

