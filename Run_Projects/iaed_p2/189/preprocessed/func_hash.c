/*File generated by PreProcessor.py*/


#include "func_hash.h"


int func_hash(char *chave)
{
  unsigned int valor = 0;
  unsigned int n = 103;
  for (; (*chave) != '\0'; chave++)
    valor = ((valor * n) + (*chave)) % 1009;

  return valor;
}
