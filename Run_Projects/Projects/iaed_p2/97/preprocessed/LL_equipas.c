/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include "LL_equipas.h"


elem_eq *inicializa_lista_equipa()
{
  elem_eq *ret;
  ret = 0;
  return ret;
}

elem_eq *apaga_primeira_equipa_lista(elem_eq *cabeca)
{
  elem_eq *antigo;
  if (cabeca != 0)
  {
    antigo = cabeca;
    cabeca = cabeca->prox;
    liberta_equipa(antigo->equipa);
    free(antigo);
  }
  else
  {
    
  }

  return cabeca;
}

elem_eq *adiciona_equipa_lista(elem_eq *cabeca, Item_eq *equipa)
{
  elem_eq *novo;
  novo = malloc(sizeof(elem_eq));
  novo->equipa = equipa;
  novo->prox = cabeca;
  return novo;
}

elem_eq *apaga_lista_equipas(elem_eq *cabeca)
{
  while (cabeca != 0)
  {
    cabeca = apaga_primeira_equipa_lista(cabeca);
  }

  return cabeca;
}

elem_eq *liberta_lista_equipas(elem_eq *cabeca)
{
  elem_eq *antigo;
  while (cabeca != 0)
  {
    antigo = cabeca;
    cabeca = cabeca->prox;
    free(antigo);
  }

  return cabeca;
}

elem_eq *encontra_equipa_lista(elem_eq *cabeca, char *nome)
{
  while (cabeca != 0)
  {
    if (!strcmp(nome_equipa(cabeca->equipa), nome))
    {
      return cabeca;
    }
    else
    {
      
    }

    cabeca = cabeca->prox;
  }

  return 0;
}

elem_eq *prox_equipa(elem_eq *el)
{
  return el->prox;
}

Item_eq *acede_equipa(elem_eq *el)
{
  return el->equipa;
}

int tamanho(elem_eq *el)
{
  int i = 0;
  while (el != 0)
  {
    i++;
    el = el->prox;
  }

  return i;
}

