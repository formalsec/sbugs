/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_jogo.h"
#include "lista_jogo.h"
#include "auxiliar.h"


void FREEnode_jogo(link_jogo t)
{
  FREEel_lista(t->el);
  free(t);
}

link_jogo insereLista_jogo(link_jogo head, el_lista_jogo *el)
{
  link_jogo old_head = head;
  head = malloc(sizeof(node_jogo));
  head->next = old_head;
  head->el = el;
  return head;
}

el_lista_jogo *procuraLista_jogo(link_jogo head, char *s)
{
  link_jogo temp;
  if (!head)
  {
    return 0;
  }
  else
  {
    
  }

  for (temp = head; temp; temp = temp->next)
  {
    if (!strcmp(temp->el->j->nome, s))
    {
      return temp->el;
    }
    else
    {
      
    }

  }

  return 0;
}

link_jogo removeJogoLista(link_jogo head, char *v)
{
  link_jogo t;
  link_jogo prev;
  if (!head)
  {
    return 0;
  }
  else
  {
    
  }

  for (t = head, prev = 0; t; prev = t, t = t->next)
  {
    if (!strcmp(t->el->j->nome, v))
    {
      if (t == head)
      {
        head = t->next;
      }
      else
      {
        prev->next = t->next;
      }

      FREEnode_jogo(t);
      break;
    }
    else
    {
      
    }

  }

  return head;
}

hashtable_jogo *cria_hash_jogo(int m)
{
  int i;
  hashtable_jogo *ht = (hashtable_jogo *) malloc(sizeof(hashtable_jogo));
  ht->M = m;
  ht->heads = (link_jogo *) malloc(ht->M * (sizeof(link_jogo)));
  for (i = 0; i < ht->M; i++)
  {
    ht->heads[i] = 0;
  }

  return ht;
}

void insereHash_jogo(hashtable_jogo *ht, el_lista_jogo *el)
{
  int i = hash(el->j->nome, ht->M);
  ht->heads[i] = insereLista_jogo(ht->heads[i], el);
}

el_lista_jogo *procuraHash_jogo(hashtable_jogo *ht, char *v)
{
  int i = hash(v, ht->M);
  return procuraLista_jogo(ht->heads[i], v);
}

void apagaHash_jogo(hashtable_jogo *ht, char *v)
{
  int i = hash(v, ht->M);
  ht->heads[i] = removeJogoLista(ht->heads[i], v);
}

void FREEhash_jogo(hashtable_jogo *ht)
{
  int i;
  link_jogo head;
  link_jogo x;
  for (i = 0; i < ht->M; i++)
  {
    head = ht->heads[i];
    while (head)
    {
      x = head;
      head = head->next;
      FREEnode_jogo(x);
    }

  }

  free(ht->heads);
  free(ht);
}
