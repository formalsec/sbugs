#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable_jogos.h"


item_hash_jg *HashJogos_inic()
{
  int i;
  item_hash_jg *hash_jogos = (item_hash_jg *) malloc(1091 * (sizeof(item_hash_jg)));
  for (i = 0; i < 1091; i++)
  {
    hash_jogos[i] = 0;
  }

  return hash_jogos;
}

item_hash_jg encontra_jogo(item_hash_jg *hash_jogos, char *nome)
{
  int key = hashfunc(nome);
  item_hash_jg aux = hash_jogos[key];
  while (aux != 0)
  {
    if (strcmp(aux->pno->jogo->nome, nome) == 0)
    {
      return aux;
    }
    else
    {
      
    }

    aux = aux->next;
  }

  return 0;
}

void HashJogos_insere(item_hash_jg *hash_jogos, linkjg pno)
{
  int key = hashfunc(pno->jogo->nome);
  item_hash_jg new = (item_hash_jg) malloc(sizeof(struct item_hash_jogo));
  new->pno = pno;
  if (hash_jogos[key] != 0)
  {
    new->next = hash_jogos[key];
    new->prev = 0;
    hash_jogos[key]->prev = new;
    hash_jogos[key] = new;
  }
  else
  {
    hash_jogos[key] = new;
    hash_jogos[key]->next = (hash_jogos[key]->prev = 0);
  }

}

