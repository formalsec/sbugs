#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "projeto2.h"


void hash_initializer(TEAM *hashT[], GAME *hashG[])
{
  int i;
  for (i = 0; i < 2000; i++)
  {
    hashT[i] = (TEAM *) calloc(1, sizeof(TEAM));
    hashG[i] = (GAME *) calloc(1, sizeof(GAME));
  }

  return;
}
