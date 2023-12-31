#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "estruturas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void init_HTJ(jogo *HTjogo)
{
  int i;
  for (i = 0; i < 1097; i++)
  {
    HTjogo[i] = 0;
  }

}

jogo newjogo(char *nome, char *eq1, char *eq2, int sc1, int sc2, int id)
{
  jogo aux = malloc(sizeof(struct str_jogo));
  aux->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
  aux->eq1 = malloc((sizeof(char)) * (strlen(eq1) + 1));
  aux->eq2 = malloc((sizeof(char)) * (strlen(eq2) + 1));
  aux->sc1 = sc1;
  aux->sc2 = sc2;
  aux->id = id;
  strcpy(aux->nome, nome);
  strcpy(aux->eq1, eq1);
  strcpy(aux->eq2, eq2);
  aux->nextJ = 0;
  return aux;
}

jogo InsertBeginingJogo(jogo head, char *nome, char *eq1, char *eq2, int sc1, int sc2, int id)
{
  jogo aux = newjogo(nome, eq1, eq2, sc1, sc2, id);
  aux->nextJ = head;
  return aux;
}

void InsertJogo(char *nome, char *eq1, char *eq2, int sc1, int sc2, jogo *HTjogo, int id)
{
  int x = Hash(nome, 1097);
  HTjogo[x] = InsertBeginingJogo(HTjogo[x], nome, eq1, eq2, sc1, sc2, id);
}

jogo SearchJogo(char *nome, jogo *HTjogo)
{
  int i = Hash(nome, 1097);
  jogo aux;
  for (aux = HTjogo[i]; aux != 0; aux = aux->nextJ)
  {
    if (strcmp(aux->nome, nome) == 0)
    {
      return aux;
    }
    else
    {
      
    }

  }

  return 0;
}

jogo RemoveJogo(jogo head, char *nome)
{
  jogo t;
  jogo prev;
  for (t = head, prev = 0; t != 0; prev = t, t = t->nextJ)
  {
    if (strcmp(t->nome, nome) == 0)
    {
      if (t == head)
      {
        head = t->nextJ;
      }
      else
      {
        prev->nextJ = t->nextJ;
      }

      FreeJogo(t);
      return head;
    }
    else
    {
      
    }

  }

  return head;
}

void FreeHTjogo(jogo *HTjogo)
{
  int i;
  jogo aux;
  for (i = 0; i < 1097; i++)
  {
    while (HTjogo[i])
    {
      aux = HTjogo[i]->nextJ;
      FreeJogo(HTjogo[i]);
      HTjogo[i] = aux;
    }

  }

}

void FreeJogo(jogo aux)
{
  free(aux->nome);
  free(aux->eq1);
  free(aux->eq2);
  free(aux);
}

