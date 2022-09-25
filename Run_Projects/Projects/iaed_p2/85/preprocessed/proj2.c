/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aux.h"
#include "hash_j.h"
#include "hash_eq.h"


void adiciona_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL);
void procura_jogo(hash_j hash_j, int NL);
void adiciona_equipa(hash_eq hash_eq, int NL);
void procura_equipa(hash_eq hash_eq, int NL);
void remove_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL);
void altera_score(hash_j hash_j, hash_eq hash_eq, int NL);
void lista_jogos(list ls, int NL);
void lista_equipas(hash_eq hash, int NL);
int main()
{
  int comando;
  int NL = 1;
  hash_j hash_j = init_hash_jogo(1057);
  hash_eq hash_eq = init_hash_eq(1057);
  list ls = new_list();
  while ((comando = getchar()) != EOF)
  {
    switch (comando)
    {
      case 'a':
        adiciona_jogo(ls, hash_j, hash_eq, NL);
        break;

      case 'p':
        procura_jogo(hash_j, NL);
        break;

      case 'A':
        adiciona_equipa(hash_eq, NL);
        break;

      case 'P':
        procura_equipa(hash_eq, NL);
        break;

      case 'r':
        remove_jogo(ls, hash_j, hash_eq, NL);
        break;

      case 's':
        altera_score(hash_j, hash_eq, NL);
        break;

      case 'l':
        lista_jogos(ls, NL);
        break;

      case 'g':
        lista_equipas(hash_eq, NL);
        break;

      case 'x':
        freeHash_j(hash_j);
        freeHash_eq(hash_eq);
        free_list(ls);
        return 0;

      default:
        fprintf(stderr, "Invalid input!\n");
        return 1;

    }

    getchar();
    NL++;
  }

  return 0;
}

void adiciona_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL)
{
  pJogo j;
  int sc1;
  int sc2;
  char n_jogo[1024];
  char eq1[1024];
  char eq2[1024];
  for (int n_jogo_index = 0; n_jogo_index < 10; n_jogo_index++)
  {
    n_jogo[n_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  n_jogo[10 - 1] = '\0';
  for (int eq1_index = 0; eq1_index < 10; eq1_index++)
  {
    eq1[eq1_index] = new_sym_var(sizeof(char) * 8);
  }

  eq1[10 - 1] = '\0';
  for (int eq2_index = 0; eq2_index < 10; eq2_index++)
  {
    eq2[eq2_index] = new_sym_var(sizeof(char) * 8);
  }

  eq2[10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  if (STsearch_jogo(hash_j, n_jogo))
  {
    printf("%d Jogo existente.\n", NL);
    return;
  }
  else
  {
    if ((!STsearch_eq(hash_eq, eq1)) || (!STsearch_eq(hash_eq, eq2)))
    {
      printf("%d Equipa inexistente.\n", NL);
      return;
    }
    else
    {
      
    }

  }

  j = cria_jogo(n_jogo, eq1, eq2, sc1, sc2, ls);
  if (j->vencedora)
  {
    STsearch_eq(hash_eq, j->vencedora)->wins++;
  }
  else
  {
    
  }

  STinsert_jogo(hash_j, j);
}

void procura_jogo(hash_j hash_j, int NL)
{
  pJogo j;
  char n_jogo[1024];
  for (int n_jogo_index = 0; n_jogo_index < 10; n_jogo_index++)
  {
    n_jogo[n_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  n_jogo[10 - 1] = '\0';
  j = STsearch_jogo(hash_j, n_jogo);
  if (!j)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  printf("%d ", NL);
  print_j(j);
}

void adiciona_equipa(hash_eq hash_eq, int NL)
{
  pEquipa eq;
  char n_eq[1024];
  for (int n_eq_index = 0; n_eq_index < 10; n_eq_index++)
  {
    n_eq[n_eq_index] = new_sym_var(sizeof(char) * 8);
  }

  n_eq[10 - 1] = '\0';
  if (STsearch_eq(hash_eq, n_eq))
  {
    printf("%d Equipa existente.\n", NL);
    return;
  }
  else
  {
    
  }

  eq = cria_equipa(n_eq);
  STinsert_eq(hash_eq, eq);
}

void procura_equipa(hash_eq hash_eq, int NL)
{
  pEquipa eq;
  char n_eq[1024];
  for (int n_eq_index = 0; n_eq_index < 10; n_eq_index++)
  {
    n_eq[n_eq_index] = new_sym_var(sizeof(char) * 8);
  }

  n_eq[10 - 1] = '\0';
  eq = STsearch_eq(hash_eq, n_eq);
  if (!eq)
  {
    printf("%d Equipa inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  printf("%d ", NL);
  print_eq(eq);
}

void remove_jogo(list ls, hash_j hash_j, hash_eq hash_eq, int NL)
{
  pJogo j;
  char n_jogo[1024];
  for (int n_jogo_index = 0; n_jogo_index < 10; n_jogo_index++)
  {
    n_jogo[n_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  n_jogo[10 - 1] = '\0';
  j = STsearch_jogo(hash_j, n_jogo);
  if (!j)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  if (j->vencedora)
  {
    STsearch_eq(hash_eq, j->vencedora)->wins--;
  }
  else
  {
    
  }

  remove_el(ls, j);
  STdelete_jogo(hash_j, n_jogo);
}

void altera_score(hash_j hash_j, hash_eq hash_eq, int NL)
{
  pJogo j;
  int sc1;
  int sc2;
  char *old_vencedora = 0;
  char n_jogo[1024];
  for (int n_jogo_index = 0; n_jogo_index < 10; n_jogo_index++)
  {
    n_jogo[n_jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  n_jogo[10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  j = STsearch_jogo(hash_j, n_jogo);
  if (!j)
  {
    printf("%d Jogo inexistente.\n", NL);
    return;
  }
  else
  {
    
  }

  if (j->vencedora)
  {
    old_vencedora = strdup(j->vencedora);
  }
  else
  {
    
  }

  altera_score_aux(j, sc1, sc2);
  corrige_wins(hash_eq, j, old_vencedora);
  if (old_vencedora)
  {
    free(old_vencedora);
  }
  else
  {
    
  }

}

void lista_jogos(list ls, int NL)
{
  print_list(ls, NL);
}

void lista_equipas(hash_eq hash, int NL)
{
  int max = 0;
  int num_eq = 0;
  calcula_max(hash, &max, &num_eq);
  if (num_eq == 0)
  {
    return;
  }
  else
  {
    
  }

  imprime_vencedoras(hash, max, num_eq, NL);
}

