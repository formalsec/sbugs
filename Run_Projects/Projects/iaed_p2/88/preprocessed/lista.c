/*File generated by PreProcessor.py*/


#include "lista.h"


no *novo_no(void *item)
{
  no *no_aux = (no *) malloc(sizeof(no));
  no_aux->item = item;
  no_aux->prox = 0;
  return no_aux;
}

no *insere(no *cabeca, void *item)
{
  no *no_aux = novo_no(item);
  if (cabeca == 0)
  {
    return no_aux;
  }
  else
  {
    no_aux->prox = cabeca;
    cabeca = no_aux;
    return cabeca;
  }

}

no *retira(no *cabeca, void *item, int (*igual)(void *, void *), void (*liberta_item)(void *))
{
  no *no_aux = cabeca;
  no *no_ant = 0;
  while (no_aux != 0)
  {
    if ((*igual)(no_aux->item, item))
    {
      if (no_aux == cabeca)
      {
        (*liberta_item)(no_aux->item);
        cabeca = no_aux->prox;
        free(no_aux);
        return cabeca;
      }
      else
      {
        no_ant->prox = no_aux->prox;
        (*liberta_item)(no_aux->item);
        free(no_aux);
        return cabeca;
      }

    }
    else
    {
      
    }

    no_ant = no_aux;
    no_aux = no_aux->prox;
  }

  return cabeca;
}

void *procura(no *cabeca, void *item, int (*igual)(void *, void *))
{
  no *no_aux;
  for (no_aux = cabeca; no_aux != 0; no_aux = no_aux->prox)
  {
    if ((*igual)(no_aux->item, item))
    {
      return no_aux->item;
    }
    else
    {
      
    }

  }

  return 0;
}

void liberta_lista(no *cabeca, void (*liberta_item)(void *))
{
  no *no_aux = cabeca;
  no *prox;
  while (no_aux != 0)
  {
    prox = no_aux->prox;
    (*liberta_item)(no_aux->item);
    free(no_aux);
    no_aux = prox;
  }

}

