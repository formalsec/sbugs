/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Equipa.h"


equipa novaEquipa(char *nom)
{
  equipa e = malloc(sizeof(struct equipa));
  e->nome = malloc((sizeof(char)) * (strlen(nom) + 1));
  strcpy(e->nome, nom);
  e->wins = 0;
  return e;
}

void freeEquipa(equipa e)
{
  if (e)
  {
    free(e->nome);
    free(e);
  }
  else
  {
    
  }

}

void printEquipa(equipa e)
{
  if (e)
  {
    printf("%s\n", e->nome);
  }
  else
  {
    
  }

}

