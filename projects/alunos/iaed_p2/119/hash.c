#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hash.h"

int hash(const char * str, int x)
{
  const char *c;
  int sum = 0;
  for (c = str; *c != '\0'; c++) sum += *c;
  return sum % x;
}