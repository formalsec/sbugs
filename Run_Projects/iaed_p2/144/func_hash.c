#include "func_hash.h"

/* Funcao que calcula a chave numa hashtables, dada uma string. */
int hash(char *v, int M)
{
  int h, a = 31415, b = 27183;
  for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
  {
    h = (a*h + *v) % M;
  }
  return h;
}
/* Funcao que aloca memoria e copia uma string. */
char *str_dup(char *palavra)
{
  int comp = 0;
  char *pal;
  char *p;

  while (palavra[comp])
  {
    comp++;
  }

  pal = malloc(comp + 1);
  p = pal;

  while (*palavra)
  {
    *p++ = *palavra++;

  }
    
  *p = '\0';

  return pal;
}
