/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"


JOGO **ht_jogos_init()
{
  int i;
  JOGO **ht = malloc((sizeof(JOGO)) * 419);
  for (i = 0; i < 419; i++)
    ht[i] = 0;

  return ht;
}

LISTA *lista_jogos_init()
{
  LISTA *nova_lista;
  nova_lista = 0;
  return nova_lista;
}

JOGO *cria_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2, EQUIPA **ht)
{
  JOGO *novo_jogo = malloc(sizeof(JOGO));
  novo_jogo->nome = malloc((sizeof(char *)) * (strlen(nome) + 1));
  strcpy(novo_jogo->nome, nome);
  novo_jogo->equipa1 = procura_equipa_aux(equipa1, ht);
  novo_jogo->equipa2 = procura_equipa_aux(equipa2, ht);
  novo_jogo->score1 = score1;
  novo_jogo->score2 = score2;
  if (score1 > score2)
  {
    novo_jogo->equipa1->jogos_ganhos++;
  }
  else
  {
    
  }

  if (score1 < score2)
  {
    novo_jogo->equipa2->jogos_ganhos++;
  }
  else
  {
    
  }

  return novo_jogo;
}

LISTA **adiciona_jg_lista(LISTA **lista, JOGO *jogo)
{
  LISTA *aux = *lista;
  LISTA *nova_lista = malloc(sizeof(LISTA));
  nova_lista->jogo = jogo;
  nova_lista->next = 0;
  if ((*lista) == 0)
  {
    {
      *lista = nova_lista;
      return lista;
    }
  }
  else
  {
    
  }

  nova_lista->next = aux;
  *lista = nova_lista;
  return lista;
}

JOGO *procura_jogo_aux(char *nome, JOGO **ht)
{
  int hash;
  JOGO *jogo;
  hash = funcao_hash(nome, 419);
  jogo = ht[hash];
  if (jogo == 0)
  {
    return 0;
  }
  else
  {
    
  }

  while (jogo != 0)
  {
    if (strcmp(jogo->nome, nome) == 0)
    {
      return jogo;
    }
    else
    {
      
    }

    jogo = jogo->next;
  }

  return 0;
}

void apaga_jg_ht(JOGO **ht_jg, JOGO *jogo)
{
  int hash;
  JOGO *anterior;
  JOGO *node;
  hash = funcao_hash(jogo->nome, 419);
  node = ht_jg[hash];
  if ((node != 0) && (strcmp(node->nome, jogo->nome) == 0))
  {
    {
      ht_jg[hash] = ht_jg[hash]->next;
      free(jogo->nome);
      free(jogo);
      return;
    }
  }
  else
  {
    
  }

  while ((node != 0) && (strcmp(node->nome, jogo->nome) != 0))
  {
    anterior = node;
    node = node->next;
  }

  anterior->next = node->next;
  free(jogo->nome);
  free(jogo);
}

void apaga_jg_lista(LISTA **lista, JOGO *jogo)
{
  LISTA *node = *lista;
  LISTA *aux;
  if (node->next == 0)
  {
    {
      *lista = 0;
      free(node);
      return;
    }
  }
  else
  {
    
  }

  if (strcmp(node->jogo->nome, jogo->nome) == 0)
  {
    {
      *lista = node->next;
      free(node);
      return;
    }
  }
  else
  {
    
  }

  while (node->next != 0)
  {
    if (strcmp(node->next->jogo->nome, jogo->nome) == 0)
    {
      {
        aux = node->next;
        node->next = node->next->next;
        free(aux);
        return;
      }
    }
    else
    {
      
    }

    node = node->next;
  }

}

void destroi_ht_jg(JOGO **ht_jg)
{
  int hash = 0;
  JOGO *jogo;
  for (; hash < 419; hash++)
  {
    while (ht_jg[hash] != 0)
    {
      jogo = ht_jg[hash];
      ht_jg[hash] = ht_jg[hash]->next;
      free(jogo->nome);
      free(jogo);
    }

  }

}

void destroi_lista_jg(LISTA **lista)
{
  LISTA *node = *lista;
  LISTA *aux;
  while (node != 0)
  {
    aux = node;
    node = node->next;
    free(aux);
  }

  free(node);
}

