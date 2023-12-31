#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "projeto2.h"


int existe_equipa(e_node **hashtable, int location, char *texto)
{
  e_node *aux;
  int procura = 0;
  for (aux = hashtable[location]; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->nome, texto) == 0)
    {
      procura = 1;
      break;
    }
    else
    {
      
    }

  }

  return procura;
}

void remove_vitoria(node *aux, e_node **equipas)
{
  e_node *tmp;
  int location;
  if (aux->jogo->score1 > aux->jogo->score2)
  {
    location = get_location(aux->jogo->equipa1);
    for (tmp = equipas[location]; tmp != 0; tmp = tmp->next)
    {
      if (strcmp(aux->jogo->equipa1, tmp->nome) == 0)
      {
        tmp->vitorias -= 1;
        break;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  if (aux->jogo->score1 < aux->jogo->score2)
  {
    location = get_location(aux->jogo->equipa2);
    for (tmp = equipas[location]; tmp != 0; tmp = tmp->next)
    {
      if (strcmp(aux->jogo->equipa2, tmp->nome) == 0)
      {
        tmp->vitorias -= 1;
        break;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

}

void remove_jogo(jogos *jg, node *aux)
{
  if (aux->jogo->previous == 0)
  {
    jg->head = aux->jogo->next;
  }
  else
  {
    aux->jogo->previous->next = aux->jogo->next;
  }

  if (aux->jogo->next == 0)
  {
    jg->last = aux->jogo->previous;
  }
  else
  {
    aux->jogo->next->previous = aux->jogo->previous;
  }

  aux->jogo->previous = 0;
  aux->jogo->next = 0;
}

vencedores copia_produto(vencedores l)
{
  vencedores copia;
  strcpy(copia.vencedor, l.vencedor);
  return copia;
}

void listar_vencedores(e_node **equipas, int maior, int conta, int NL)
{
  e_node *aux;
  int i;
  int j = 0;
  int tmp;
  vencedores *lista = malloc((sizeof(vencedores)) * conta);
  vencedores palavra;
  for (i = 0; i != conta; i++)
    strcpy(lista[i].vencedor, "0");

  for (i = 0; i < 1021; i++)
  {
    if (equipas[i] != 0)
    {
      for (aux = equipas[i]; aux != 0; aux = aux->next)
      {
        if (aux->vitorias == maior)
        {
          strcpy(lista[j].vencedor, aux->nome);
          j++;
        }
        else
        {
          
        }

      }

    }
    else
    {
      
    }

  }

  tmp = j;
  printf("%d Melhores %d\n", NL, maior);
  for (j = 0; j < tmp; j++)
  {
    for (i = 0; i < tmp; i++)
    {
      if (i != (tmp - 1))
      {
        if (strcmp(lista[i].vencedor, lista[i + 1].vencedor) > 0)
        {
          palavra = copia_produto(lista[i]);
          lista[i] = copia_produto(lista[i + 1]);
          lista[i + 1] = copia_produto(palavra);
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

  }

  for (i = 0; i != tmp; i++)
  {
    printf("%d * %s\n", NL, lista[i].vencedor);
  }

  free(lista);
}

