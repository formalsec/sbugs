#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "funcoes_aux.h"


int hash(char *nome, int dim)
{
  int tamanho = 0;
  int res;
  int i = 0;
  while (nome[i] != '\0')
  {
    tamanho += nome[i];
    i++;
  }

  res = tamanho % dim;
  return res;
}

