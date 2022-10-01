/*File generated by PreProcessor.py*/


#include "lista.h"


void lst_init(Lista *lst)
{
  *lst = (Lista) malloc(sizeof(struct lista_str));
  (*lst)->head = 0;
  (*lst)->tail = 0;
}

lst_link lst_cria(pJogo jogo)
{
  lst_link link = (lst_link) malloc(sizeof(struct lst_node));
  link->jogo = jogo;
  link->next = 0;
  return link;
}

lst_link lst_insere(pJogo jogo, Lista lst)
{
  lst_link link = lst_cria(jogo);
  if (lst->head == 0)
  {
    lst->head = link;
    link->prev = 0;
  }
  else
  {
    link->prev = lst->tail;
    lst->tail->next = link;
  }

  lst->tail = link;
  return link;
}

void lst_remove(lst_link link, Lista lst)
{
  lst_link l;
  lst_link r;
  l = link->prev;
  r = link->next;
  if (lst->head == lst->tail)
  {
    lst->head = 0;
    lst->tail = 0;
  }
  else
  {
    if (lst->head == link)
    {
      r->prev = 0;
      lst->head = r;
    }
    else
    {
      if (lst->tail == link)
      {
        l->next = 0;
        lst->tail = l;
      }
      else
      {
        l->next = r;
        r->prev = l;
      }

    }

  }

  jogo_free(link->jogo);
  free(link);
}

void lst_print(Lista lst, int NL)
{
  lst_link link;
  for (link = lst->head; link != 0; link = link->next)
    jogo_print(link->jogo, NL);

}

void lst_node_free(lst_link link)
{
  jogo_free(link->jogo);
  free(link);
}

void lst_free(Lista lst)
{
  free(lst);
}
