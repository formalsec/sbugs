#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "functions.h"


int main()
{
  int M;
  int N;
  int x = 0;
  int counter = 1;
  int Nequipas = 0;
  int max = 0;
  char buffer[3075];
  char comando;
  char rest[3074];
  games *games_list;
  teams *lista_equipas;
  struct Jogos *first = 0;
  struct Jogos *top = 0;
  struct Equipas *false_t = (struct Equipas *) malloc(sizeof(struct Equipas));
  struct Jogos *false_g = (struct Jogos *) malloc(sizeof(struct Jogos));
  M = 20287;
  N = 20287;
  false_t->ID = malloc((strlen("NONE") + 1) * (sizeof(char)));
  strcpy(false_t->ID, "NONE");
  false_g->ID = malloc((strlen("none") + 1) * (sizeof(char)));
  strcpy(false_g->ID, "none");
  lista_equipas = malloc(N * (sizeof(teams)));
  games_list = malloc(M * (sizeof(games)));
  for (x = 0; x < M; x++)
    games_list[x] = 0;

  for (x = 0; x < N; x++)
    lista_equipas[x] = 0;

  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  comando = new_sym_var(sizeof(char) * 8);
  for (int rest_index = 0; rest_index < 10; rest_index++)
  {
    rest[rest_index] = new_sym_var(sizeof(char) * 8);
  }

  rest[10 - 1] = '\0';
  while (comando != 'x')
  {
    if (comando == 'a')
    {
      Inseret(games_list, &first, rest, M, counter, lista_equipas, false_t, &top, false_g, N);
    }
    else
    {
      
    }

    if (comando == 'A')
    {
      x = InseretEquipa(lista_equipas, rest, N, counter, false_t);
      if (x == 1)
      {
        ++Nequipas;
      }
      else
      {
        
      }

    }
    else
    {
      
    }

    if (comando == 'p')
    {
      encontraJogo(games_list, rest, true, M, counter, false_g);
    }
    else
    {
      
    }

    if (comando == 'P')
    {
      encontraEquipa(lista_equipas, rest, true, N, counter, false_t);
    }
    else
    {
      
    }

    if (comando == 'l')
    {
      showByDate(first, counter);
    }
    else
    {
      
    }

    if (comando == 'r')
    {
      deleteGame(games_list, &first, rest, lista_equipas, false_t, M, counter, false_g, &top, N);
    }
    else
    {
      
    }

    if (comando == 's')
    {
      alteraScore(games_list, rest, M, counter, lista_equipas, false_t, N);
    }
    else
    {
      
    }

    if (comando == 'g')
    {
      max = FindMax(lista_equipas, N);
      lista(lista_equipas, Nequipas, counter, max, N);
    }
    else
    {
      
    }

    if (comando == 'w')
    {
      max = FindMax(lista_equipas, N);
      printf("<%d>\n", max);
    }
    else
    {
      
    }

    ++counter;
    for (int buffer_index = 0; buffer_index < 10; buffer_index++)
    {
      buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
    }

    buffer[10 - 1] = '\0';
    comando = new_sym_var(sizeof(char) * 8);
    for (int rest_index = 0; rest_index < 10; rest_index++)
    {
      rest[rest_index] = new_sym_var(sizeof(char) * 8);
    }

    rest[10 - 1] = '\0';
  }

  freeStruct(&first, lista_equipas, N);
  free(false_t->ID);
  free(false_t);
  free(false_g->ID);
  free(false_g);
  free(lista_equipas);
  free(games_list);
  return 0;
}

