#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogo.h"


pJogo cria_jogo(const char *nome, const char *e1, const char *e2, const int s1, const int s2)
{
  pJogo j;
  j = malloc(sizeof(jogo));
  j->nome = strdup(nome);
  j->equipa1 = strdup(e1), j->equipa2 = strdup(e2);
  j->score1 = s1;
  j->score2 = s2;
  if (s1 > s2)
  {
    j->vencedora = strdup(e1);
  }
  else
  {
    if (s1 < s2)
    {
      j->vencedora = strdup(e2);
    }
    else
    {
      j->vencedora = 0;
    }

  }

  return j;
}

void altera_score_jogo(pJogo j, const int s1, const int s2)
{
  j->score1 = s1;
  j->score2 = s2;
  if (s1 > s2)
  {
    if (j->vencedora)
    {
      free(j->vencedora);
    }
    else
    {
      
    }

    j->vencedora = strdup(j->equipa1);
  }
  else
  {
    if (s1 < s2)
    {
      if (j->vencedora)
      {
        free(j->vencedora);
      }
      else
      {
        
      }

      j->vencedora = strdup(j->equipa2);
    }
    else
    {
      if (j->vencedora)
      {
        free(j->vencedora);
      }
      else
      {
        
      }

      j->vencedora = 0;
    }

  }

}

void FREEjogo(pJogo j)
{
  free(j->nome);
  free(j->equipa1);
  free(j->equipa2);
  if (j->vencedora)
  {
    free(j->vencedora);
  }
  else
  {
    
  }

  free(j);
}

