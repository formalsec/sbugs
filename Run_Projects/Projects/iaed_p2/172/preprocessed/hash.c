/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hash.h"
#include "structs.h"


int hash(char *v, int M)
{
  unsigned int h = 0;
  unsigned int i = 233;
  unsigned int j = 113;
  for (; (*v) != '\0'; v++, i = (i * j) % (M - 1))
    h = ((h * i) + (*v)) % (M - 1);

  return h;
}

Game *STinitG(int M)
{
  int i;
  Game *stg;
  stg = (Game *) malloc(M * (sizeof(Game)));
  for (i = 0; i < M; i++)
    stg[i] = 0;

  return stg;
}

void STinsertG(Game g, int M, Game *stg)
{
  int i = hash(g->name, M);
  while (stg[i] != 0)
    i = (i + 1) % M;

  stg[i] = g;
}

void STdeleteG(char *v, int M, Game *stg)
{
  int j;
  int i = hash(v, M);
  Game g;
  while (stg[i] != 0)
  {
    if (strcmp(stg[i]->name, v) == 0)
    {
      break;
    }
    else
    {
      i = (i + 1) % M;
    }

  }

  if (stg[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  FreeGame(stg[i]);
  stg[i] = 0;
  for (j = (i + 1) % M; stg[j] != 0; j = (j + 1) % M)
  {
    g = stg[j];
    stg[j] = 0;
    STinsertG(g, M, stg);
  }

}

Game STsearchG(char *v, int M, Game *stg)
{
  int i = hash(v, M);
  while (stg[i] != 0)
  {
    if (strcmp(stg[i]->name, v) == 0)
    {
      return stg[i];
    }
    else
    {
      i = (i + 1) % M;
    }

  }

  return 0;
}

Team *STinitT(int M)
{
  int i;
  Team *stt;
  stt = (Team *) malloc(M * (sizeof(Team)));
  for (i = 0; i < M; i++)
    stt[i] = 0;

  return stt;
}

void STinsertT(Team t, int M, Team *stt)
{
  int i = hash(t->name, M);
  while (stt[i] != 0)
    i = (i + 1) % M;

  stt[i] = t;
}

void STdeleteT(char *v, int M, Team *stt)
{
  int j;
  int i = hash(v, M);
  Team t;
  while (stt[i] != 0)
  {
    if (strcmp(stt[i]->name, v) == 0)
    {
      break;
    }
    else
    {
      i = (i + 1) % M;
    }

  }

  if (stt[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  FreeTeam(stt[i]);
  stt[i] = 0;
  for (j = (i + 1) % M; stt[j] != 0; j = (j + 1) % M)
  {
    t = stt[j];
    stt[j] = 0;
    STinsertT(t, M, stt);
  }

}

Team STsearchT(char *v, int M, Team *stt)
{
  int i;
  i = hash(v, M);
  while (stt[i] != 0)
  {
    if (strcmp(stt[i]->name, v) == 0)
    {
      return stt[i];
    }
    else
    {
      i = (i + 1) % M;
    }

  }

  return 0;
}

