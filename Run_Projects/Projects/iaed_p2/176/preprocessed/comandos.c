/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"


void comando_A(int cont, lista_equipa le, ht_equipas ht_e)
{
  char *ptexto = (char *) malloc((sizeof(char)) * 1024);
  getchar();
  for (int ptexto_index = 0; ptexto_index < 10; ptexto_index++)
  {
    ptexto[ptexto_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto[10 - 1] = '\0';
  if (procura_equipa_hash_equipas(ht_e, ptexto) != (-1))
  {
    {
      printf("%d Equipa existente.\n", cont);
    }
  }
  else
  {
    {
      inserir_equipa(le, ptexto);
      insere_equipa_hash_equipas(ht_e, le->head->e);
    }
  }

  free(ptexto);
}

void comando_P(int cont, ht_equipas ht_e)
{
  int i;
  char *ptexto = (char *) malloc((sizeof(char)) * 1024);
  getchar();
  for (int ptexto_index = 0; ptexto_index < 10; ptexto_index++)
  {
    ptexto[ptexto_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto[10 - 1] = '\0';
  i = procura_equipa_hash_equipas(ht_e, ptexto);
  if (i == (-1))
  {
    {
      printf("%d Equipa inexistente.\n", cont);
    }
  }
  else
  {
    {
      printf("%d %s %d\n", cont, ht_e->hash_equipas[i]->nome, ht_e->hash_equipas[i]->vitorias);
    }
  }

  free(ptexto);
}

void comando_a(int cont, lista_jogos lj, ht_jogos ht_j, ht_equipas ht_e)
{
  int ie1;
  int ie2;
  int score1;
  int score2;
  char *ptexto = (char *) malloc((sizeof(char)) * 1024);
  char *ptexto_e1 = (char *) malloc((sizeof(char)) * 1024);
  char *ptexto_e2 = (char *) malloc((sizeof(char)) * 1024);
  getchar();
  for (int ptexto_index = 0; ptexto_index < 10; ptexto_index++)
  {
    ptexto[ptexto_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto[10 - 1] = '\0';
  getchar();
  for (int ptexto_e1_index = 0; ptexto_e1_index < 10; ptexto_e1_index++)
  {
    ptexto_e1[ptexto_e1_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto_e1[10 - 1] = '\0';
  getchar();
  for (int ptexto_e2_index = 0; ptexto_e2_index < 10; ptexto_e2_index++)
  {
    ptexto_e2[ptexto_e2_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto_e2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  ie1 = procura_equipa_hash_equipas(ht_e, ptexto_e1);
  ie2 = procura_equipa_hash_equipas(ht_e, ptexto_e2);
  if (procura_jogo_hash_jogos(ht_j, ptexto) != (-1))
  {
    {
      printf("%d Jogo existente.\n", cont);
    }
  }
  else
  {
    if ((ie1 == (-1)) || (ie2 == (-1)))
    {
      {
        printf("%d Equipa inexistente.\n", cont);
      }
    }
    else
    {
      {
        inserir_jogo(lj, ptexto, ht_e->hash_equipas[ie1], ht_e->hash_equipas[ie2], score1, score2);
        insere_jogo_hash_jogos(ht_j, lj->tail);
        aumenta_vitorias(lj->tail->j);
      }
    }

  }

  free(ptexto);
  free(ptexto_e1);
  free(ptexto_e2);
}

void comando_p(int cont, ht_jogos ht_j)
{
  int i;
  char *ptexto = (char *) malloc((sizeof(char)) * 1024);
  getchar();
  for (int ptexto_index = 0; ptexto_index < 10; ptexto_index++)
  {
    ptexto[ptexto_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto[10 - 1] = '\0';
  i = procura_jogo_hash_jogos(ht_j, ptexto);
  if (i == (-1))
  {
    {
      printf("%d Jogo inexistente.\n", cont);
    }
  }
  else
  {
    {
      printf("%d %s %s %s %d %d\n", cont, ht_j->hash_jogos[i]->j->nome, ht_j->hash_jogos[i]->j->e1->nome, ht_j->hash_jogos[i]->j->e2->nome, ht_j->hash_jogos[i]->j->s1, ht_j->hash_jogos[i]->j->s2);
    }
  }

  free(ptexto);
}

void comando_l(int cont, lista_jogos lj)
{
  imprimir_lista_jogos(cont, lj);
}

void comando_s(int cont, ht_jogos ht_j)
{
  int i;
  int novo_s1;
  int novo_s2;
  char *ptexto = (char *) malloc((sizeof(char)) * 1024);
  getchar();
  for (int ptexto_index = 0; ptexto_index < 10; ptexto_index++)
  {
    ptexto[ptexto_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto[10 - 1] = '\0';
  novo_s1 = new_sym_var(sizeof(int) * 8);
  novo_s2 = new_sym_var(sizeof(int) * 8);
  i = procura_jogo_hash_jogos(ht_j, ptexto);
  if (i == (-1))
  {
    {
      printf("%d Jogo inexistente.\n", cont);
    }
  }
  else
  {
    {
      altera_scores(ht_j->hash_jogos[i], novo_s1, novo_s2);
    }
  }

  free(ptexto);
}

void comando_r(int cont, ht_jogos ht_j, lista_jogos lj)
{
  int i;
  char *ptexto = (char *) malloc((sizeof(char)) * 1024);
  getchar();
  for (int ptexto_index = 0; ptexto_index < 10; ptexto_index++)
  {
    ptexto[ptexto_index] = new_sym_var(sizeof(char) * 8);
  }

  ptexto[10 - 1] = '\0';
  i = procura_jogo_hash_jogos(ht_j, ptexto);
  if (i == (-1))
  {
    {
      printf("%d Jogo inexistente.\n", cont);
    }
  }
  else
  {
    {
      diminui_vitorias(ht_j->hash_jogos[i]->j);
      elimina_jogo_lista_jogos(lj, ht_j->hash_jogos[i]);
      elimina_jogo_hash_jogos(ht_j, i);
    }
  }

  free(ptexto);
}

void comando_g(int cont, lista_equipa le)
{
  if (le->tamanho == 0)
  {
    return;
  }
  else
  {
    {
      procura_max_vitorias(le);
      encontra_max_vitorias(cont, le);
      le->max_vitorias = 0;
      le->cont_equipas_max_vit = 0;
    }
  }

}

void comando_x(lista_equipa le, lista_jogos lj, ht_equipas ht_e, ht_jogos ht_j)
{
  eliminar_lista_jogos(lj);
  eliminar_hash_jogos(ht_j->hash_jogos, ht_j->max);
  eliminar_hash_equipas(ht_e->hash_equipas, ht_e->max);
  eliminar_lista_equipa(le);
  free(ht_e);
  free(ht_j);
}

