/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HASHTABLES.h"


unsigned int funcao_dispersao(char *nome, unsigned int M)
{
  unsigned int h;
  unsigned int a = 31415;
  unsigned int b = 27183;
  for (h = 0; (*nome) != '\0'; nome++, a = (a * b) % (M - 1))
  {
    h = ((a * h) + (*nome)) % M;
  }

  return h;
}

pJogo *init_tab_dispersao(unsigned int M)
{
  unsigned int i;
  pJogo *tab_dispersao = 0;
  tab_dispersao = (pJogo *) malloc(M * (sizeof(pJogo)));
  for (i = 0; i < M; i++)
  {
    tab_dispersao[i] = 0;
  }

  return tab_dispersao;
}

pJogo tab_dispersao_insere(pJogo *tab_dispersao, char *nome, char *equipa1, char *equipa2, int score1, int score2, unsigned int M)
{
  unsigned int i = funcao_dispersao(nome, M);
  while (tab_dispersao[i] != 0)
  {
    i = (i + 1) % M;
  }

  tab_dispersao[i] = (pJogo) malloc(sizeof(struct Jogo));
  tab_dispersao[i]->nome = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(tab_dispersao[i]->nome, nome);
  tab_dispersao[i]->equipa1 = equipa1;
  tab_dispersao[i]->equipa2 = equipa2;
  tab_dispersao[i]->score1 = score1;
  tab_dispersao[i]->score2 = score2;
  return tab_dispersao[i];
}

pJogo procura_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido, unsigned int M)
{
  unsigned int i = funcao_dispersao(nome_recebido, M);
  while (tab_dispersao[i] != 0)
  {
    if (!strcmp(tab_dispersao[i]->nome, nome_recebido))
    {
      return tab_dispersao[i];
    }
    else
    {
      i = (i + 1) % M;
    }

  }

  return 0;
}

void apaga_tab_dispersao(pJogo *tab_dispersao, char *nome_recebido, unsigned int M)
{
  unsigned int j;
  unsigned int aux;
  unsigned int i = funcao_dispersao(nome_recebido, M);
  while (tab_dispersao[i] != 0)
  {
    if (!strcmp(tab_dispersao[i]->nome, nome_recebido))
    {
      break;
    }
    else
    {
      
    }

    i = (i + 1) % M;
  }

  if (tab_dispersao[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  free(tab_dispersao[i]->nome);
  free(tab_dispersao[i]);
  tab_dispersao[i] = 0;
  do
  {
    for (j = (i + 1) % M; tab_dispersao[j] != 0; j = (j + 1) % M)
    {
      aux = funcao_dispersao(tab_dispersao[j]->nome, M);
      if (aux <= i)
      {
        tab_dispersao[i] = tab_dispersao[j];
        tab_dispersao[j] = 0;
        i = j;
        break;
      }
      else
      {
        
      }

    }

  }
  while (i == j);
  return;
}

pJogo *expande(pJogo *tab_dispersao, unsigned int M)
{
  unsigned int i;
  unsigned int j;
  pJogo *nova_tab_dispersao = 0;
  nova_tab_dispersao = init_tab_dispersao(M);
  for (i = 0; i < (M / 2); i++)
  {
    if (tab_dispersao[i] != 0)
    {
      j = funcao_dispersao(tab_dispersao[i]->nome, M);
      while (nova_tab_dispersao[j] != 0)
      {
        j = (j + 1) % M;
      }

      nova_tab_dispersao[j] = tab_dispersao[i];
    }
    else
    {
      
    }

  }

  free(tab_dispersao);
  return nova_tab_dispersao;
}

void free_tab_dispersao(pJogo *tab_dispersao, unsigned int M)
{
  unsigned int i;
  for (i = 0; i < M; i++)
  {
    if (tab_dispersao[i] != 0)
    {
      free(tab_dispersao[i]->nome);
      free(tab_dispersao[i]);
    }
    else
    {
      
    }

  }

  free(tab_dispersao);
}

unsigned int funcao_tab_equipas(char *equipa)
{
  unsigned int h;
  h = ((int) equipa[0]) + ((int) equipa[1]);
  return h;
}

void free_tab_equipas(link_equipa *tab_equipas)
{
  int i;
  link_equipa e = 0;
  link_equipa e_next = 0;
  for (i = 0; i < 512; i++)
    for (e = tab_equipas[i]; e != 0; e = e_next)
  {
    e_next = e->next;
    free(e->equipa);
    free(e);
  }


}

