/*File generated by PreProcessor.py*/


#include "hashtable.h"
#include "strdup.h"
#include <stdlib.h>
#include <string.h>


static MATCH *st;
static int M;
unsigned int hash(char *v)
{
  unsigned int val = 0;
  unsigned int a;
  a = strlen(v);
  for (; (*v) != '\0'; v++)
    val = (a * val) + (*v);

  return val % M;
}

void STinit()
{
  int i;
  M = 2 * 10151;
  st = (MATCH *) malloc(M * (sizeof(MATCH)));
  for (i = 0; i < M; i++)
    st[i] = 0;

}

void STinsert(MATCH match)
{
  unsigned int i;
  i = hash(match->name);
  while (st[i] != 0)
    i = (i + 1) % M;

  st[i] = matchdup(match);
  free(match->name);
  free(match->team1);
  free(match->team2);
  free(match);
}

void STdelete(char *name)
{
  unsigned int i;
  unsigned int j;
  MATCH v;
  i = hash(name);
  while (st[i] != 0)
  {
    if (strcmp(st[i]->name, name) == 0)
    {
      break;
    }
    else
    {
      i = (i + 1) % M;
    }

  }

  if (st[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  free(st[i]->name);
  free(st[i]->team1);
  free(st[i]->team2);
  free(st[i]);
  st[i] = 0;
  for (j = (i + 1) % M; st[j] != 0; j = (j + 1) % M)
  {
    v = matchdup(st[j]);
    free(st[j]->name);
    free(st[j]->team1);
    free(st[j]->team2);
    free(st[j]);
    st[j] = 0;
    STinsert(v);
  }

}

MATCH STsearch(char *name)
{
  unsigned int i;
  i = hash(name);
  while (st[i] != 0)
  {
    if (strcmp(st[i]->name, name) == 0)
    {
      return st[i];
    }
    else
    {
      i = (i + 1) % M;
    }

  }

  return 0;
}

void STdeletetable()
{
  int i;
  for (i = 0; i < M; i++)
  {
    if (st[i] != 0)
    {
      {
        free(st[i]->name);
        free(st[i]->team1);
        free(st[i]->team2);
        free(st[i]);
      }
    }
    else
    {
      
    }

  }

  free(st);
}

