#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include "LDL_jogos.h"


lista *cria_lista_jogos()
{
  lista *ret;
  ret = malloc(sizeof(lista));
  ret->inicio = 0;
  ret->fim = 0;
  return ret;
}

void apaga_lista_jogos(lista *l)
{
  elem_j *tmp;
  if (l->fim != l->inicio)
  {
    while (l->fim != l->inicio)
    {
      tmp = l->fim->ante;
      liberta_jogo(l->fim->jogo);
      free(l->fim);
      l->fim = tmp;
    }

    liberta_jogo(l->inicio->jogo);
    free(l->inicio);
  }
  else
  {
    if (l->inicio != 0)
    {
      liberta_jogo(l->inicio->jogo);
      free(l->inicio);
    }
    else
    {
      
    }

  }

  free(l);
}

void liberta_lista_jogos(lista *l)
{
  elem_j *aux = l->inicio;
  elem_j *tmp;
  while (aux != 0)
  {
    tmp = aux;
    aux = aux->prox;
    free(tmp);
  }

  free(l);
}

void adiciona_jogo_lista(lista *l, Item_j *el)
{
  elem_j *add;
  add = malloc(sizeof(elem_j));
  add->jogo = el;
  add->prox = 0;
  add->ante = l->fim;
  if (l->fim != 0)
  {
    l->fim->prox = add;
  }
  else
  {
    
  }

  l->fim = add;
  if (l->inicio == 0)
  {
    l->inicio = l->fim;
  }
  else
  {
    
  }

}

void remove_jogo_lista(lista *l, elem_j *el)
{
  if ((l->inicio == el) && (l->fim == el))
  {
    l->inicio = 0;
    l->fim = 0;
  }
  else
  {
    if ((l->inicio != el) && (l->fim != el))
    {
      el->ante->prox = el->prox;
      el->prox->ante = el->ante;
    }
    else
    {
      if (l->inicio == el)
      {
        l->inicio = el->prox;
        l->inicio->ante = 0;
      }
      else
      {
        
      }

      if (l->fim == el)
      {
        l->fim = el->ante;
        l->fim->prox = 0;
      }
      else
      {
        
      }

    }

  }

  free(el);
}

elem_j *encontra_jogo_lista(lista *l, char *nome)
{
  elem_j *tmp;
  tmp = l->inicio;
  while (tmp != 0)
  {
    if (!strcmp(tmp->jogo->nome, nome))
    {
      return tmp;
    }
    else
    {
      
    }

    tmp = tmp->prox;
  }

  return 0;
}

Item_j *acede_jogo(elem_j *el)
{
  return el->jogo;
}

elem_j *acede_inicio_lista_jogos(lista *l)
{
  return l->inicio;
}

elem_j *prox_elem(elem_j *el)
{
  return el->prox;
}

