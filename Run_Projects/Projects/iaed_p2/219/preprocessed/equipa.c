/*File generated by PreProcessor.py*/


#include <stdio.h>
#include "equipa.h"


equipa *cria_equipa()
{
  equipa *nova_equipa = malloc((sizeof(equipa)) + 1);
  nova_equipa->nome = 0;
  return nova_equipa;
}

lista_equipas *cria_lista_equipas()
{
  lista_equipas *nova_lista = malloc(sizeof(lista_equipas));
  nova_lista->head = (nova_lista->last = 0);
  return nova_lista;
}

void free_equipa(equipa *eq)
{
  free(eq->nome);
  free(eq);
}

void preenche_equipa(equipa *eq, char *nome)
{
  eq->nome = malloc(((sizeof(char)) * strlen(nome)) + 1);
  eq->ganhos = 0;
  strcpy(eq->nome, nome);
}

void adiciona_equipa(equipa *eq, lista_equipas *l_equipas)
{
  equipa *old_first;
  if (l_equipas->head == 0)
  {
    {
      l_equipas->head = eq;
      eq->equipa_anterior = 0;
      eq->equipa_seguinte = 0;
      l_equipas->last = eq;
    }
  }
  else
  {
    {
      old_first = l_equipas->head;
      old_first->equipa_anterior = eq;
      eq->equipa_seguinte = old_first;
      eq->equipa_anterior = 0;
      l_equipas->head = eq;
    }
  }

  l_equipas->num_equipas++;
}

void free_equipas(lista_equipas *l_equipas)
{
  while (l_equipas->head)
  {
    equipa *auxequipa = l_equipas->head->equipa_seguinte;
    free_equipa(l_equipas->head);
    l_equipas->head = auxequipa;
  }

  free(l_equipas);
}

