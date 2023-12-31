#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "comandos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void comando_a(Jogos *jogos, Jogo_hash *j, Equipas_hash *e, int M, int E, int NL)
{
  char nome_jogo[1024];
  char equipa1[1024];
  char equipa2[1024];
  int s1 = 0;
  int s2 = 0;
  Equipas_hash um;
  Equipas_hash dois;
  jogo *x;
  for (int nome_jogo_index = 0; nome_jogo_index < 10; nome_jogo_index++)
  {
    nome_jogo[nome_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  nome_jogo[10 - 1] = '\0';
  for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
  {
    equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa1[10 - 1] = '\0';
  for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
  {
    equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa2[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  um = SearchE(e, equipa1, E);
  dois = SearchE(e, equipa2, E);
  x = Search(j, nome_jogo, M);
  if (x == 0)
  {
    if ((um != 0) && (dois != 0))
    {
      x = adiciona_jogo(jogos, nome_jogo, um, dois, s1, s2);
      insert_jogo(j, x, M);
      if (s1 > s2)
      {
        um->jogos_ganhos++;
      }
      else
      {
        if (s2 > s1)
        {
          dois->jogos_ganhos++;
        }
        else
        {
          
        }

      }

    }
    else
    {
      printf("%d Equipa inexistente.\n", NL);
    }

  }
  else
  {
    printf("%d Jogo existente.\n", NL);
  }

}

void comando_l(Jogos *jogos, int NL)
{
  jogo *aux = jogos->head;
  for (; aux != 0; aux = aux->next)
  {
    printf("%d %s %s %s %d %d\n", NL, aux->nome, aux->equipa1->nome_equipa, aux->equipa2->nome_equipa, aux->score1, aux->score2);
  }

}

void comando_p(Jogo_hash *j, int M, int NL)
{
  jogo *x;
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  x = Search(j, buffer, M);
  if (x != 0)
  {
    printf("%d %s %s %s %d %d\n", NL, x->nome, x->equipa1->nome_equipa, x->equipa2->nome_equipa, x->score1, x->score2);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void comando_r(Jogos *jogos, Jogo_hash *j, Equipas_hash *e, int M, int E, int NL)
{
  jogo *x;
  Equipas_hash e1;
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  x = Search(j, buffer, M);
  if (x != 0)
  {
    if (x->score1 > x->score2)
    {
      e1 = SearchE(e, x->equipa1->nome_equipa, E);
      e1->jogos_ganhos--;
    }
    else
    {
      if (x->score1 < x->score2)
      {
        e1 = SearchE(e, x->equipa2->nome_equipa, E);
        e1->jogos_ganhos--;
      }
      else
      {
        
      }

    }

    delete_jogo(j, x, M);
    delete_jogoP(jogos, x);
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

void comando_s(Jogo_hash *j, Equipas_hash *e, int M, int E, int NL)
{
  jogo *x;
  Equipas_hash e1;
  Equipas_hash e2;
  int s1;
  int s2;
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  s1 = new_sym_var(sizeof(int) * 8);
  s2 = new_sym_var(sizeof(int) * 8);
  x = Search(j, buffer, M);
  if (x != 0)
  {
    e1 = SearchE(e, x->equipa1->nome_equipa, E);
    e2 = SearchE(e, x->equipa2->nome_equipa, E);
    if ((x->score1 > x->score2) && (s1 == s2))
    {
      e1->jogos_ganhos--;
    }
    else
    {
      if ((x->score1 > x->score2) && (s1 < s2))
      {
        e1->jogos_ganhos--;
        e2->jogos_ganhos++;
      }
      else
      {
        if ((x->score1 == x->score2) && (s1 < s2))
        {
          e2->jogos_ganhos++;
        }
        else
        {
          if ((x->score1 < x->score2) && (s1 == s2))
          {
            e2->jogos_ganhos--;
          }
          else
          {
            if ((x->score1 < x->score2) && (s1 > s2))
            {
              e1->jogos_ganhos++;
              e2->jogos_ganhos--;
            }
            else
            {
              if ((x->score1 == x->score2) && (s1 > s2))
              {
                e1->jogos_ganhos++;
              }
              else
              {
                
              }

            }

          }

        }

      }

    }

    x->score1 = s1;
    x->score2 = s2;
  }
  else
  {
    printf("%d Jogo inexistente.\n", NL);
  }

}

int comando_A(Equipas_hash *e, int E, int total_equipas, int NL)
{
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (SearchE(e, buffer, E) == 0)
  {
    insert_equipa(e, buffer, E);
    total_equipas++;
  }
  else
  {
    printf("%d Equipa existente.\n", NL);
  }

  return total_equipas;
}

void comando_P(Equipas_hash *e, int E, int NL)
{
  Equipas_hash e1;
  char buffer[1024];
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  e1 = SearchE(e, buffer, E);
  if (e1 != 0)
  {
    printf("%d %s %d\n", NL, e1->nome_equipa, e1->jogos_ganhos);
  }
  else
  {
    printf("%d Equipa inexistente.\n", NL);
  }

}

int compare(const void *a, const void *b)
{
  struct str_equipa *pa = *((struct str_equipa **) a);
  struct str_equipa *pb = *((struct str_equipa **) b);
  return strcmp(pa->nome_equipa, pb->nome_equipa);
}

void comando_g(Equipas_hash *e, int E, int total_equipas, int NL)
{
  struct str_equipa **array = 0;
  struct str_equipa *aux = 0;
  long i;
  long k;
  long max = 0;
  long total = 0;
  if (total_equipas > 0)
  {
    array = malloc(total_equipas * (sizeof(struct str_equipa)));
    for (i = 0; i < E; i++)
    {
      aux = e[i];
      for (k = 0; aux != 0; aux = aux->next, k++)
      {
        if (aux->jogos_ganhos > max)
        {
          max = aux->jogos_ganhos;
        }
        else
        {
          
        }

      }

    }

    i = 0;
    k = 0;
    while (i < E)
    {
      aux = e[i];
      while (aux != 0)
      {
        if (aux->jogos_ganhos == max)
        {
          array[k] = aux;
          total++;
          k++;
        }
        else
        {
          
        }

        aux = aux->next;
      }

      i++;
    }

    qsort(array, total, sizeof(struct str_equipa *), compare);
    printf("%d Melhores %ld\n", NL, max);
    for (i = 0; i < total; i++)
    {
      printf("%d * %s\n", NL, array[i]->nome_equipa);
    }

    free(array);
  }
  else
  {
    
  }

}

