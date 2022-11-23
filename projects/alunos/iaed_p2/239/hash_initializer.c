#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "projeto2.h"

void hash_initializer (TEAM* hashT[], GAME* hashG[])
{
  int i;
  for (i = 0 ; i < hash_size ; i++)
  {
    hashT[i] = (TEAM*)can_fail_calloc(1,sizeof(TEAM));
    hashG[i] = (GAME*)can_fail_calloc(1,sizeof(GAME));
  }
  return;
}
