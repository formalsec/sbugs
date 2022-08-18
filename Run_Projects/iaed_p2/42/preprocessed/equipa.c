/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipa.h"


void freeEquipa(pEquipa e)
{
  free(e->nome);
  free(e);
}

void printEquipa(pEquipa e)
{
  printf("%s %d\n", e->nome, e->vitorias);
}

pEquipa newEquipa(char *nome)
{
  pEquipa new = (pEquipa) malloc(sizeof(struct equipa));
  new->nome = (char *) malloc((sizeof(char)) * (strlen(nome) + 1));
  strcpy(new->nome, nome);
  new->vitorias = 0;
  return new;
}

