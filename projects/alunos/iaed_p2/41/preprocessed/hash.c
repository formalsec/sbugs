#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "hash.h"


unsigned long hash_function(char *str)
{
  unsigned long hash = 0;
  int c;
  while (c = *(str++))
    hash = ((c + (hash << 6)) + (hash << 16)) - hash;

  return hash % 1009;
}
