/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipa.h"


Equipa nova_equipa(char *nome)
{
  Equipa nova = (Equipa) malloc(sizeof(struct eq));
  nova->nome = strdup(nome);
  nova->vitorias = 0;
  return nova;
}

char *nome_equipa(Equipa eq)
{
  return eq->nome;
}

int vitorias_equipa(Equipa eq)
{
  return eq->vitorias;
}

void altera_vitorias_eq(Equipa eq, int v)
{
  eq->vitorias += v;
}

void apaga_equipa(Equipa eq)
{
  free(eq->nome);
  free(eq);
}

int compara_eq(const void *a, const void *b)
{
  Equipa eq1;
  Equipa eq2;
  eq1 = *((Equipa *) a);
  eq2 = *((Equipa *) b);
  return strcmp(eq1->nome, eq2->nome);
}

char *strdup(const char *str)
{
  int n = strlen(str) + 1;
  char *dup = malloc(n);
  if (dup)
  {
    {
      strcpy(dup, str);
    }
  }
  else
  {
    
  }

  return dup;
}

