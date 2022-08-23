/*File generated by PreProcessor.py*/


#include "hash.h"


int gera_hash(char *string, unsigned int modulo)
{
  int hash;
  int a;
  int b;
  hash = 0;
  a = 31415;
  b = 27813;
  for (; (*string) != '\0'; string++, a = (a * b) % modulo)
    hash = ((a * hash) + (*string)) % modulo;

  return hash;
}

