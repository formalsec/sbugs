/*File generated by PreProcessor.py*/


#include "lista_jogos.h"
#include "equipa.h"
#include "hash_equipas.h"
#include "hash_jogos.h"
#include "jogo.h"
#include "lista_jogos.h"


list *LS_jg_init()
{
  list *l = calloc(1, sizeof(list));
  return l;
}

link_jogo LS_jg_insert(ptr_jogo jogo, list *l)
{
  link_jogo new = malloc(sizeof(struct node_jogo));
  new->prev = l->last;
  new->next = 0;
  new->jogo = jogo;
  if (l->last)
  {
    l->last->next = new;
  }
  else
  {
    l->head = new;
  }

  l->last = new;
  return new;
}

void LS_jg_delete(link_jogo ptr_node_jogo, list *l)
{
  if (ptr_node_jogo->prev == 0)
  {
    {
      l->head = ptr_node_jogo->next;
    }
  }
  else
  {
    {
      ptr_node_jogo->prev->next = ptr_node_jogo->next;
    }
  }

  if (ptr_node_jogo->next == 0)
  {
    {
      l->last = ptr_node_jogo->prev;
    }
  }
  else
  {
    {
      ptr_node_jogo->next->prev = ptr_node_jogo->prev;
    }
  }

  freeJogo(ptr_node_jogo->jogo);
  free(ptr_node_jogo);
}

void freeList(list *l)
{
  link_jogo temp = 0;
  link_jogo aux = 0;
  temp = l->head;
  while (temp != 0)
  {
    aux = temp;
    temp = temp->next;
    freeJogo(aux->jogo);
    free(aux);
  }

  free(l);
}

