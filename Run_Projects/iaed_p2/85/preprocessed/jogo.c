/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "aux.h"
#include "jogo.h"


list new_list()
{
  list ls;
  ls = malloc(sizeof(struct list));
  ls->head = (ls->last = 0);
  return ls;
}

pJogo cria_jogo(char *n_jogo, char *eq1, char *eq2, int sc1, int sc2, list ls)
{
  pJogo new = malloc(sizeof(struct jogo));
  new->next = 0;
  new->previous = ls->last;
  new->n_jogo = strdup(n_jogo);
  new->eq1 = strdup(eq1);
  new->eq2 = strdup(eq2);
  new->sc1 = sc1;
  new->sc2 = sc2;
  if (sc1 > sc2)
  {
    new->vencedora = strdup(eq1);
  }
  else
  {
    if (sc2 > sc1)
    {
      new->vencedora = strdup(eq2);
    }
    else
    {
      new->vencedora = 0;
    }

  }

  if (ls->last)
  {
    ls->last->next = new;
  }
  else
  {
    
  }

  ls->last = new;
  if (!ls->head)
  {
    ls->head = new;
  }
  else
  {
    
  }

  return new;
}

void print_j(pJogo j)
{
  printf("%s %s %s %d %d\n", j->n_jogo, j->eq1, j->eq2, j->sc1, j->sc2);
}

void free_jogo(pJogo j)
{
  free(j->n_jogo);
  free(j->eq1);
  free(j->eq2);
  if (j->vencedora)
  {
    free(j->vencedora);
  }
  else
  {
    
  }

  free(j);
}

void altera_score_aux(pJogo j, int sc1, int sc2)
{
  j->sc1 = sc1;
  j->sc2 = sc2;
  if (sc1 > sc2)
  {
    {
      free(j->vencedora);
      j->vencedora = strdup(j->eq1);
    }
  }
  else
  {
    if (sc1 < sc2)
    {
      {
        free(j->vencedora);
        j->vencedora = strdup(j->eq2);
      }
    }
    else
    {
      {
        free(j->vencedora);
        j->vencedora = 0;
      }
    }

  }

}

void remove_el(list ls, pJogo j)
{
  if ((!j->previous) && (!j->next))
  {
    ls->head = (ls->last = 0);
  }
  else
  {
    if (j->previous && (!j->next))
    {
      {
        ls->last = j->previous;
        j->previous->next = 0;
      }
    }
    else
    {
      if ((!j->previous) && j->next)
      {
        {
          j->next->previous = 0;
          ls->head = j->next;
        }
      }
      else
      {
        {
          j->previous->next = j->next;
          j->next->previous = j->previous;
        }
      }

    }

  }

}

void print_list(list ls, int NL)
{
  pJogo temp = ls->head;
  while (temp)
  {
    printf("%d ", NL);
    print_j(temp);
    temp = temp->next;
  }

}

void free_list(list ls)
{
  free(ls);
}

