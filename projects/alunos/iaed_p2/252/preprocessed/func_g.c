#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func_g.h"


int compara_vitorias(const void *p, const void *q)
{
  Equipa **a = (Equipa **) p;
  Equipa **b = (Equipa **) q;
  int compara;
  if (((*b)->vitorias - (*a)->vitorias) == 0)
  {
    compara = strcmp((*a)->nome, (*b)->nome);
    if (compara < 0)
    {
      return -1;
    }
    else
    {
      if (compara > 0)
      {
        return 1;
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  return (*b)->vitorias - (*a)->vitorias;
}

void ordenaEquipas(team_list *l, int num_equipas, int NL)
{
  Equipa *temp = l->head;
  Equipa **Copy;
  int i;
  int maior;
  Copy = malloc((sizeof(Equipa *)) * num_equipas);
  if (temp == 0)
  {
    free(Copy);
    return;
  }
  else
  {
    
  }

  for (i = 0; (i < num_equipas) && (temp != 0); i++)
  {
    *(Copy + i) = temp;
    temp = temp->next;
  }

  qsort(Copy, num_equipas, sizeof(Equipa *), compara_vitorias);
  maior = (*(*Copy)).vitorias;
  printf("%d Melhores %d\n", NL, maior);
  for (i = 0; i < num_equipas; i++)
  {
    if ((*(*(Copy + i))).vitorias != maior)
    {
      break;
    }
    else
    {
      
    }

    printf("%d * %s\n", NL, (*(*(Copy + i))).nome);
  }

  free(Copy);
  return;
}

