/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JogoEquipa.h"


char *strndup(const char *s, size_t n)
{
  char *p = memchr(s, '\0', n);
  if (p != 0)
  {
    n = p - s;
  }
  else
  {
    
  }

  p = malloc(n + 1);
  if (p != 0)
  {
    {
      memcpy(p, s, n);
      p[n] = '\0';
    }
  }
  else
  {
    
  }

  return p;
}

void freeJogo(Jogo a)
{
  free(a->nome);
  free(a->equipa1);
  free(a->equipa2);
  free(a);
}

void printJogo(Jogo a)
{
  printf("%s %s %s %d %d\n", a->nome, a->equipa1, a->equipa2, a->score1, a->score2);
}

Jogo newJogo(char *nome, char *equipa1, char *equipa2, int score1, int score2)
{
  Jogo new = (Jogo) malloc(sizeof(struct struct_Jogo));
  new->nome = strndup(nome, 1023);
  new->equipa1 = strndup(equipa1, 1023);
  new->equipa2 = strndup(equipa2, 1023);
  new->score1 = score1;
  new->score2 = score2;
  return new;
}

void freeEquipa(Equipa a)
{
  free(a->nome);
  free(a);
}

void printEquipa(Equipa a)
{
  printf("%s %d\n", a->nome, a->vitorias);
}

Equipa newEquipa(char *nome, int vitorias)
{
  Equipa new = (Equipa) malloc(sizeof(struct struct_Equipa));
  new->nome = strndup(nome, 1023);
  new->vitorias = vitorias;
  return new;
}

