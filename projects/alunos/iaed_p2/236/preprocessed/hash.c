#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"


unsigned int hash(char *name)
{
  int i;
  int length;
  unsigned int hash;
  length = strlen(name);
  hash = 0;
  for (i = 0; i < length; ++i)
  {
    hash += name[i];
    hash = (hash * name[i]) % 1000;
  }

  return hash;
}

