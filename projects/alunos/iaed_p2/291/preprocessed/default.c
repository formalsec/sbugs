#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "default.h"


int hashU(char *v)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (3000 - 1))
    h = ((a * h) + (*v)) % 3000;

  return h;
}

