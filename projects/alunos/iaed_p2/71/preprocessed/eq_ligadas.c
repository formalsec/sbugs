#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq_ligadas.h"


Lista_Equipas init_lista_eq()
{
  Lista_Equipas lista = malloc(sizeof(struct lista_ligada));
  lista->primeira = 0;
  lista->ultima = 0;
  return lista;
}

void acrescenta_eq(Lista_Equipas lista, Equipa equipa)
{
  int verifica = 0;
  eq_lig link = malloc(sizeof(struct node_equipas));
  eq_lig atual;
  eq_lig anterior = 0;
  link->equipa = equipa;
  if (lista->primeira == 0)
  {
    lista->primeira = link;
    lista->ultima = link;
    lista->primeira->seguinte = lista->ultima;
  }
  else
  {
    if (lista->primeira->equipa == lista->ultima->equipa)
    {
      if (strcmp(lista->primeira->equipa->nome, link->equipa->nome) > 0)
      {
        lista->primeira = link;
      }
      else
      {
        lista->ultima = link;
      }

      lista->primeira->seguinte = lista->ultima;
    }
    else
    {
      for (atual = lista->primeira; atual != lista->ultima; atual = atual->seguinte)
      {
        if (strcmp(atual->equipa->nome, link->equipa->nome) > 0)
        {
          verifica++;
          if (anterior == 0)
          {
            link->seguinte = lista->primeira;
            lista->primeira = link;
          }
          else
          {
            link->seguinte = atual;
            anterior->seguinte = link;
          }

          break;
        }
        else
        {
          
        }

        anterior = atual;
      }

      if (!verifica)
      {
        if (strcmp(lista->ultima->equipa->nome, link->equipa->nome) > 0)
        {
          link->seguinte = lista->ultima;
          anterior->seguinte = link;
        }
        else
        {
          lista->ultima->seguinte = link;
          lista->ultima = link;
          lista->ultima->seguinte = 0;
        }

      }
      else
      {
        
      }

    }

  }

  lista->ultima->seguinte = 0;
}

void print_lista_eq(Lista_Equipas lista, int linha, int max_ganhos)
{
  eq_lig x = lista->primeira;
  if (lista->primeira == 0)
  {
    return;
  }
  else
  {
    if (lista->ultima->equipa == lista->primeira->equipa)
    {
      printf("%d Melhores %d\n", linha, max_ganhos);
      printf("%d * %s\n", linha, x->equipa->nome);
    }
    else
    {
      printf("%d Melhores %d\n", linha, max_ganhos);
      while (x != lista->ultima)
      {
        printf("%d * %s\n", linha, x->equipa->nome);
        x = x->seguinte;
      }

      printf("%d * %s\n", linha, x->equipa->nome);
    }

  }

}

void destroi_eq_ligadas(Lista_Equipas lista)
{
  eq_lig atual;
  eq_lig seg;
  if (lista->primeira == 0)
  {
    free(lista);
    return;
  }
  else
  {
    if (lista->primeira->equipa == lista->ultima->equipa)
    {
      free(lista->primeira);
      free(lista);
    }
    else
    {
      atual = lista->primeira;
      seg = atual->seguinte;
      while (atual != lista->ultima)
      {
        free(atual);
        atual = seg;
        seg = seg->seguinte;
      }

      free(lista->ultima);
      free(lista);
    }

  }

}

