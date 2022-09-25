/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jogo.h"
#include "equipa.h"


jogo cria_jogo(char *nome, equipa e1, equipa e2, int s1, int s2)
{
  jogo j;
  j = malloc(sizeof(struct str_jogo));
  j->nome = malloc((strlen(nome) + 1) * (sizeof(char)));
  j->e1 = e1;
  j->e2 = e2;
  j->s1 = s1;
  j->s2 = s2;
  strcpy(j->nome, nome);
  if (s1 > s2)
  {
    muda_vitorias(j->e1, '+');
  }
  else
  {
    if (s2 > s1)
    {
      muda_vitorias(j->e2, '+');
    }
    else
    {
      
    }

  }

  return j;
}

void apaga_jogo(jogo j)
{
  if (j)
  {
    free(j->nome);
    free(j);
  }
  else
  {
    
  }

}

void altera_score(jogo j, int s1, int s2)
{
  j->s1 = s1;
  j->s2 = s2;
}

equipa obtem_vencedora(jogo j)
{
  if (j->s1 > j->s2)
  {
    return j->e1;
  }
  else
  {
    if (j->s1 < j->s2)
    {
      return j->e2;
    }
    else
    {
      return 0;
    }

  }

}

void escreve_jogo(int nL, jogo j)
{
  printf("%d %s %s %s %d %d\n", nL, j->nome, j->e1->nome, j->e2->nome, j->s1, j->s2);
}

