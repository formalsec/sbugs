/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "match.h"
#include "stack.h"
#include "strdup.h"


tlink tNEWnode(char *team, tlink next)
{
  tlink x = (tlink) malloc(sizeof(struct STACKteamsnode));
  x->team = team;
  x->next = next;
  return x;
}

void tFREEnode(tlink t)
{
  free(t->team);
  free(t);
}

tSTACK tSTACKinit()
{
  tSTACK ts = (tSTACK) malloc(sizeof(struct tstack));
  ts->head = 0;
  return ts;
}

int tSTACKempty(tSTACK ts)
{
  return ts->head == 0;
}

void tSTACKpush(tSTACK ts, char *team)
{
  ts->head = tNEWnode(team, ts->head);
}

char *tSTACKteamsearch(tSTACK ts, char *team)
{
  tlink t;
  for (t = ts->head; t != 0; t = t->next)
    if (strcmp(t->team, team) == 0)
  {
    return t->team;
  }
  else
  {
    
  }


  return 0;
}

int tSTACKlength(tSTACK ts)
{
  tlink t;
  int len = 0;
  for (t = ts->head; t != 0; t = t->next)
    len++;

  return len;
}

void tSTACKdelete(tSTACK ts)
{
  tlink aux;
  while (ts->head != 0)
  {
    aux = ts->head;
    ts->head = ts->head->next;
    free(aux->team);
    free(aux);
  }

  free(ts);
}

