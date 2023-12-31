#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "jogos.h"
#include "equipas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


lista *init_lista()
{
  lista *ls = (lista *) malloc(sizeof(lista));
  ls->head = 0;
  ls->last = 0;
  return ls;
}

void insere_lista_ult(lista *ls, jogos *jogo)
{
  node *novo_node = (node *) malloc(sizeof(node));
  novo_node->jogo = jogo;
  novo_node->next = 0;
  novo_node->previous = ls->last;
  if (ls->head == 0)
  {
    ls->head = novo_node;
    ls->last = novo_node;
  }
  else
  {
    ls->last->next = novo_node;
    ls->last = novo_node;
  }

}

void remove_lista(lista *ls, char *nome)
{
  node *aux = ls->head;
  while (strcmp(aux->jogo->nome, nome))
  {
    aux = aux->next;
  }

  if ((aux == ls->last) && (aux == ls->head))
  {
    ls->head = 0;
    ls->last = 0;
  }
  else
  {
    if (aux->previous == 0)
    {
      aux->next->previous = 0;
      ls->head = aux->next;
    }
    else
    {
      if (aux->next == 0)
      {
        aux->previous->next = 0;
        ls->last = aux->previous;
      }
      else
      {
        aux->previous->next = aux->next;
        aux->next->previous = aux->previous;
      }

    }

  }

  free(aux);
}

void free_lista(lista *ls)
{
  node *aux;
  while (ls->head != 0)
  {
    aux = ls->head->next;
    free(ls->head);
    ls->head = aux;
  }

  free(ls);
}

hashtable_jogos *init_hash_jogos(int tamanho)
{
  int i = 0;
  hashtable_jogos *hash_table = (hashtable_jogos *) malloc(sizeof(hashtable_jogos));
  hash_table->hash = (jogos **) malloc((sizeof(jogos *)) * tamanho);
  hash_table->tamanho = tamanho;
  hash_table->n_elem = 0;
  for (; i < tamanho; i++)
  {
    hash_table->hash[i] = 0;
  }

  return hash_table;
}

int hash_jogos(hashtable_jogos *hash_table, char *nome)
{
  int i = 0;
  int a = 293;
  int chave = 0;
  for (; nome[i] != '\0'; i++)
  {
    chave = ((a * chave) + nome[i]) % hash_table->tamanho;
  }

  return chave;
}

void insere_hash_jogos(hashtable_jogos *hash_table, jogos *jogo)
{
  int i = hash_jogos(hash_table, jogo->nome);
  for (; hash_table->hash[i] != 0; i = (i + 1) % hash_table->tamanho)
    ;

  hash_table->hash[i] = jogo;
  hash_table->n_elem++;
  if (hash_table->n_elem >= (hash_table->tamanho / 2))
  {
    expandir_hash_jogos(hash_table);
  }
  else
  {
    
  }

}

jogos *procura_hash_jogos(hashtable_jogos *hash_table, char *nome)
{
  int i = hash_jogos(hash_table, nome);
  for (; hash_table->hash[i] != 0; i = (i + 1) % hash_table->tamanho)
  {
    if (!strcmp(hash_table->hash[i]->nome, nome))
    {
      return hash_table->hash[i];
    }
    else
    {
      
    }

  }

  return 0;
}

void remove_hash_jogos(hashtable_jogos *hash_table, char *nome)
{
  jogos *jogo;
  int i = hash_jogos(hash_table, nome);
  for (; hash_table->hash[i] != 0; i = (i + 1) % hash_table->tamanho)
  {
    if (!strcmp(hash_table->hash[i]->nome, nome))
    {
      break;
    }
    else
    {
      
    }

  }

  free(hash_table->hash[i]->nome);
  free(hash_table->hash[i]->equipa1);
  free(hash_table->hash[i]->equipa2);
  free(hash_table->hash[i]);
  hash_table->hash[i] = 0;
  hash_table->n_elem--;
  for (i = (i + 1) % hash_table->tamanho; hash_table->hash[i] != 0; i = (i + 1) % hash_table->tamanho)
  {
    jogo = hash_table->hash[i];
    hash_table->hash[i] = 0;
    insere_hash_jogos(hash_table, jogo);
  }

}

void expandir_hash_jogos(hashtable_jogos *hash_table)
{
  int i = 0;
  hashtable_jogos *nova_hash = init_hash_jogos(hash_table->tamanho * 2);
  for (; i < hash_table->tamanho; i++)
  {
    if (hash_table->hash[i] != 0)
    {
      insere_hash_jogos(nova_hash, hash_table->hash[i]);
    }
    else
    {
      
    }

  }

  free(hash_table->hash);
  hash_table->hash = nova_hash->hash;
  hash_table->tamanho = nova_hash->tamanho;
  free(nova_hash);
}

void free_hash_jogos(hashtable_jogos *hash_table)
{
  int i = 0;
  for (; i != hash_table->tamanho; i++)
  {
    if (hash_table->hash[i] != 0)
    {
      free(hash_table->hash[i]->nome);
      free(hash_table->hash[i]->equipa1);
      free(hash_table->hash[i]->equipa2);
      free(hash_table->hash[i]);
    }
    else
    {
      
    }

  }

  free(hash_table->hash);
  free(hash_table);
}

