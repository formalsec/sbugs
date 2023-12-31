#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "HashtableEquipa.h"


Hashtable_Equipa *ht_criar_equipa(int max)
{
  Hashtable_Equipa *ht = malloc(sizeof(Hashtable_Equipa));
  int i;
  ht->entradas = malloc((sizeof(Lista_Ligada_Equipa)) * max);
  ht->cap = max;
  ht->qtd = 0;
  for (i = 0; i < max; ++i)
    ht->entradas[i] = ll_criar_equipa();

  return ht;
}

int ht_hash_equipa(Hashtable_Equipa *ht, char *chave)
{
  unsigned long int valor = 0;
  int i;
  int tam = strlen(chave);
  for (i = 0; i < tam; ++i)
    valor = (valor * 37) + chave[i];

  return valor % ht->cap;
}

void ht_inserir_equipa(Hashtable_Equipa *ht, Equipa *equipa, char *chave)
{
  int i = ht_hash_equipa(ht, chave);
  Lista_Ligada_Equipa *lista = ht->entradas[i];
  ll_inserir_equipa(lista, equipa, chave);
  ht->qtd++;
}

Equipa *ht_pesquisar_equipa(Hashtable_Equipa *ht, char *chave)
{
  int index_hash = ht_hash_equipa(ht, chave);
  No_Equipa *n = ht->entradas[index_hash]->inicio;
  while (n)
  {
    if (strcmp(n->chave, chave) == 0)
    {
      return n->equipa;
    }
    else
    {
      
    }

    n = n->prox;
  }

  return 0;
}

void free_hash_equipa(Hashtable_Equipa *ht)
{
  int i;
  No_Equipa *tmp;
  No_Equipa *aux;
  for (i = 0; i < ht->cap; i++)
  {
    for (tmp = ht->entradas[i]->inicio; tmp != 0; tmp = aux)
    {
      aux = tmp->prox;
      free(tmp->chave);
      free(tmp);
    }

    free(ht->entradas[i]);
  }

  free(ht->entradas);
  free(ht);
}

