#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "games.h"


gLink gInsert_begin(gLink head, pGame game)
{
  gLink new = (gLink) malloc(sizeof(struct gNode));
  if (head != 0)
  {
    head->prev = new;
  }
  else
  {
    
  }

  new->game = game;
  new->next = head;
  new->prev = 0;
  return new;
}

gLink gRemove(gLink head, char *name)
{
  gLink aux;
  for (aux = head; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->game->name, name) == 0)
    {
      if ((aux->prev == 0) && (aux->next == 0))
      {
        head = 0;
      }
      else
      {
        if (aux->prev == 0)
        {
          if (aux == head)
          {
            head = aux->next;
          }
          else
          {
            
          }

          aux->next->prev = 0;
        }
        else
        {
          if (aux->next == 0)
          {
            aux->prev->next = 0;
          }
          else
          {
            aux->prev->next = aux->next;
            aux->next->prev = aux->prev;
          }

        }

      }

      break;
    }
    else
    {
      
    }

  }

  free(aux);
  return head;
}

pGame gSearch(gLink head, char *name)
{
  gLink aux;
  for (aux = head; aux != 0; aux = aux->next)
  {
    if (strcmp(aux->game->name, name) == 0)
    {
      return aux->game;
    }
    else
    {
      
    }

  }

  return 0;
}

int gHash(char *v)
{
  int h = 0;
  int a = 127;
  for (; (*v) != '\0'; v++)
    h = ((a * h) + (*v)) % 1009;

  return h;
}

gLink *gInit(gLink *hash)
{
  int i;
  hash = (gLink *) malloc(1009 * (sizeof(gLink)));
  for (i = 0; i < 1009; i++)
    hash[i] = 0;

  return hash;
}

pGame gHTsearch(gLink *hash, char *name)
{
  int i = gHash(name);
  return gSearch(hash[i], name);
}

void gHTinsert(gLink *hash, pGame game)
{
  int i = gHash(game->name);
  hash[i] = gInsert_begin(hash[i], game);
}

void gHTdelete(gLink *hash, char *name)
{
  int i = gHash(name);
  hash[i] = gRemove(hash[i], name);
}

void freeGame(pGame g)
{
  free(g->team1);
  free(g->team2);
  free(g->name);
  free(g);
}

