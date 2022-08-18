/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table_jogo.h"
#include "comandos.h"


jogo *init_hash_table_jogo(jogo *hash[2000])
{
  int i;
  for (i = 0; i < 2000; i++)
  {
    hash[i] = 0;
  }

  return *hash;
}

jogo *hash_table_jogo_insert(jogo *j, jogo *hash[2000])
{
  int indice;
  indice = hash_function(j->nome_jogo);
  j->next = hash[indice];
  hash[indice] = j;
  return *hash;
}

jogo *hash_table_jogo_lookup(char *nome, jogo *hash[2000])
{
  int indice;
  jogo *aux;
  indice = hash_function(nome);
  for (aux = hash[indice]; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->nome_jogo, nome) == 0)
    {
      {
        return aux;
      }
    }
    else
    {
      
    }

  }

  return 0;
}

jogo *hash_table_jogo_delete(char *nome, jogo *hash[2000])
{
  int indice;
  jogo *aux;
  jogo *aux_ant;
  indice = hash_function(nome);
  aux = hash[indice];
  aux_ant = 0;
  while ((aux != 0) && (strcmp(aux->nome_jogo, nome) != 0))
  {
    aux_ant = aux;
    aux = aux->next;
  }

  if (aux == 0)
  {
    {
      return 0;
    }
  }
  else
  {
    
  }

  if (aux_ant == 0)
  {
    {
      hash[indice] = aux->next;
    }
  }
  else
  {
    {
      aux_ant->next = aux->next;
    }
  }

  return *hash;
}

