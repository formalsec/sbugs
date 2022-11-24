#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "projeto2.h"

int hash_function(char string[])
{
  char manipulation[MAX_STRING];
  int i, sum;
  for(i = 0; string[i] != '\0'; i++)
  {
  	manipulation[i] = string[i]%10;
  	manipulation[i] = manipulation[i]%10;
  	manipulation[i] = manipulation[i]+48;
    sum = sum + atoi(&string[i]);
    
  }
  
  sum = sum*397;
  sum = sum%hash_size;

  return sum;
}
