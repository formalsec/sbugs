/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"


int hash(Key n, int M)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*n) != '\0'; n++, a = (a * b) % (M - 1))
    h = ((a * h) + (*n)) % M;

  return h;
}

Hashtable cria_hash(int max)
{
  int i;
  Item *endereco;
  Hashtable hasht;
  hasht = (Hashtable) malloc(sizeof(struct hasht));
  hasht->M = 2 * max;
  hasht->N = 0;
  endereco = (Item *) malloc((2 * max) * (sizeof(Item)));
  hasht->endereco = endereco;
  for (i = 0; i < (2 * max); i++)
    endereco[i] = 0;

  return hasht;
}

void insere_hash(Item item, Hashtable hasht)
{
  Item *endereco = hasht->endereco;
  int M = hasht->M;
  int i = hash(item->nome, M);
  while (endereco[i] != 0)
    i = (i + 1) % M;

  endereco[i] = item;
  hasht->N++;
}

Item procura_hash(Key n, Hashtable hasht)
{
  Item *endereco = hasht->endereco;
  int M = hasht->M;
  int i = hash(n, M);
  while (endereco[i] != 0)
    if (!strcmp(n, endereco[i]->nome))
  {
    return endereco[i];
  }
  else
  {
    i = (i + 1) % M;
  }


  return 0;
}

Item apaga_hash(Key n, Hashtable hasht)
{
  int M = hasht->M;
  int i = hash(n, M);
  int j;
  Item *endereco = hasht->endereco;
  Item jogo;
  Item aux;
  while (endereco[i] != 0)
    if (!strcmp(n, endereco[i]->nome))
  {
    break;
  }
  else
  {
    i = (i + 1) % M;
  }


  jogo = endereco[i];
  if (jogo == 0)
  {
    return jogo;
  }
  else
  {
    
  }

  endereco[i] = 0;
  hasht->N--;
  for (j = (i + 1) % M; endereco[j] != 0; j = (j + 1) % M, hasht->N--)
  {
    aux = endereco[j];
    endereco[j] = 0;
    insere_hash(aux, hasht);
  }

  return jogo;
}

void liberta_hash(Hashtable hasht)
{
  Item *endereco = hasht->endereco;
  int M = hasht->M;
  int i;
  for (i = 0; i < M; i++)
    if (endereco[i] != 0)
  {
    free_item(endereco[i]);
  }
  else
  {
    
  }


  free(endereco);
  free(hasht);
}

