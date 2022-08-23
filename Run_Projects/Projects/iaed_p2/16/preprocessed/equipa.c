/*File generated by PreProcessor.py*/


#include "codigoAux.h"
#include "equipa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


equipa *criaEquipa(char *nome)
{
  equipa *novaEquipa;
  novaEquipa = (equipa *) malloc(sizeof(equipa));
  novaEquipa->nome = duplicaString(nome);
  novaEquipa->numeroVitorias = 0;
  return novaEquipa;
}

void freeEquipa(equipa *Equipa)
{
  free(Equipa->nome);
  free(Equipa);
}

void printEquipa(equipa *Equipa, int *pNL)
{
  printf("%d %s %d\n", *pNL, Equipa->nome, Equipa->numeroVitorias);
}

