#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipas.h"
#include "jogos.h"


link_jogo *inicializa_ht_jogos()
{
  int i;
  link_jogo *ht = malloc(4111 * (sizeof(link_jogo)));
  for (i = 0; i < 4111; i++)
    ht[i] = 0;

  return ht;
}

lista_jogos *inicializa_lista_jogos()
{
  lista_jogos *lista = malloc(sizeof(lista_jogos));
  lista->primeiro = 0;
  lista->ultimo = 0;
  return lista;
}

link_jogo novo_jogo(char *nome_jogo, char *equipa1, char *equipa2, int score1, int score2, link_equipa *ht_equipas)
{
  link_jogo novo = malloc(sizeof(struct node_jogo));
  novo->nome_jogo = malloc((sizeof(char)) * (strlen(nome_jogo) + 1));
  strcpy(novo->nome_jogo, nome_jogo);
  novo->equipa1 = procura_equipa(equipa1, ht_equipas);
  novo->equipa2 = procura_equipa(equipa2, ht_equipas);
  novo->score1 = score1;
  novo->score2 = score2;
  novo->next_ht = 0;
  novo->next_lista = 0;
  return novo;
}

void adiciona_jogo_lista(link_jogo jogo, lista_jogos *lista)
{
  if (!lista->primeiro)
  {
    lista->primeiro = jogo;
    lista->ultimo = jogo;
    return;
  }
  else
  {
    
  }

  lista->ultimo->next_lista = jogo;
  lista->ultimo = jogo;
}

void adiciona_jogo_ht(link_jogo jogo, link_jogo *ht)
{
  int i = hash(jogo->nome_jogo);
  if (!ht[i])
  {
    ht[i] = jogo;
    return;
  }
  else
  {
    
  }

  jogo->next_ht = ht[i];
  ht[i] = jogo;
}

link_jogo procura_jogo(char *nome_jogo, link_jogo *ht)
{
  link_jogo t;
  int i = hash(nome_jogo);
  for (t = ht[i]; t != 0; t = t->next_ht)
    if (strcmp(t->nome_jogo, nome_jogo) == 0)
  {
    return t;
  }
  else
  {
    
  }


  return 0;
}

void remove_jogo_lista(link_jogo jogo, lista_jogos *lista)
{
  link_jogo t;
  link_jogo prev;
  for (t = lista->primeiro, prev = 0; t != 0; prev = t, t = t->next_lista)
  {
    if (strcmp(t->nome_jogo, jogo->nome_jogo) == 0)
    {
      if (t == lista->primeiro)
      {
        lista->primeiro = t->next_lista;
      }
      else
      {
        prev->next_lista = t->next_lista;
      }

      if (t->next_lista == 0)
      {
        lista->ultimo = prev;
      }
      else
      {
        
      }

      break;
    }
    else
    {
      
    }

  }

}

void remove_jogo_ht(link_jogo jogo, link_jogo *ht)
{
  link_jogo t;
  link_jogo prev;
  int i = hash(jogo->nome_jogo);
  for (t = ht[i], prev = 0; t != 0; prev = t, t = t->next_ht)
  {
    if (strcmp(t->nome_jogo, jogo->nome_jogo) == 0)
    {
      if (t == ht[i])
      {
        ht[i] = t->next_ht;
      }
      else
      {
        prev->next_ht = t->next_ht;
      }

      break;
    }
    else
    {
      
    }

  }

}

void liberta_jogo(link_jogo jogo)
{
  free(jogo->nome_jogo);
  free(jogo);
}

void destroi_estrut_jogos(lista_jogos *lista, link_jogo *ht)
{
  link_jogo aux;
  while (lista->primeiro)
  {
    aux = lista->primeiro->next_lista;
    liberta_jogo(lista->primeiro);
    lista->primeiro = aux;
  }

  free(lista);
  free(ht);
}

