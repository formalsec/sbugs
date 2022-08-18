/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include "jogo.h"


pEquipa NEWequipa(char *nome)
{
  pEquipa eq = malloc(sizeof(struct equipa));
  eq->nome = strdup(nome);
  eq->ganhos = 0;
  return eq;
}

ItemDL NEWjogo(char *nome, pEquipa eq1, pEquipa eq2, int sc1, int sc2)
{
  ItemDL p = malloc(sizeof(struct jogo));
  p->nome = strdup(nome);
  p->eq1 = eq1;
  p->eq2 = eq2;
  p->sc1 = sc1;
  p->sc2 = sc2;
  return p;
}

ItemkeyDL keyDL(ItemDL v)
{
  return v->nome;
}

void freeItemDL(ItemDL v)
{
  free(v->nome);
  free(v);
}

int hashItem(char *s, int M)
{
  int h = 0;
  int a = 127;
  for (; (*s) != '\0'; s++)
    h = ((a * h) + (*s)) % M;

  return h;
}

char *strdup(const char *src)
{
  char *dst = malloc(strlen(src) + 1);
  if (dst == 0)
  {
    return 0;
  }
  else
  {
    
  }

  strcpy(dst, src);
  return dst;
}

void *keyEquipa(void *eq)
{
  return ((pEquipa) eq)->nome;
}

void *keyJogo(void *lk)
{
  return (void *) (*((ItemDL *) lk))->nome;
}

