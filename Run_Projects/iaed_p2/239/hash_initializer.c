#include "projeto2.h"

void hash_initializer (TEAM* hashT[], GAME* hashG[])
{
  int i;
  for (i = 0 ; i < hash_size ; i++)
  {
    hashT[i] = (TEAM*)calloc(1,sizeof(TEAM));
    hashG[i] = (GAME*)calloc(1,sizeof(GAME));
  }
  return;
}
