#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gameHTable.h"


glink **init_HTgame(int number)
{
  int i;
  glink **HTgame = malloc((number * 2) * (sizeof(glink *)));
  for (i = 0; i < (9677 * 2); i++)
  {
    HTgame[i] = 0;
  }

  return HTgame;
}

glink **init_STgame(int number)
{
  int i;
  glink **simple = malloc((number * 2) * (sizeof(glink *)));
  memset(simple, 0x0, ((sizeof(glink *)) * 2) * 9677);
  for (i = 0; i < (9677 * 2); i++)
  {
    simple[i] = 0;
  }

  return simple;
}

glink **simplexpand(glink **STgame, int number)
{
  int i;
  int conta = -1;
  glink **nv = STgame;
  glink **newSTgame;
  newSTgame = init_STgame(number * 4);
  for (i = 0; i < (number * 2); i++)
  {
    if (nv[i]->g->name != 0)
    {
      gorderInsert(&nv[i], newSTgame, conta++);
    }
    else
    {
      
    }

  }

  free(nv);
  return newSTgame;
}

glink **gorderInsert(glink **link, glink **STgame, int count)
{
  STgame[count] = *link;
  return link;
}

glink **expand(glink **HTgame, int number)
{
  int i;
  glink **t = HTgame;
  glink **newHTgame;
  newHTgame = init_HTgame(number * 2);
  for (i = 0; i < (number * 2); i++)
  {
    if (t[i]->g->name != 0)
    {
      gsimplyInsert(t[i], newHTgame);
    }
    else
    {
      
    }

  }

  free(t);
  return newHTgame;
}

glink **gorderRemove(char *buffer0, glink **STgame, int counter_game)
{
  int i = 0;
  int j;
  glink *aux;
  for (i = 0; i < counter_game; i++)
  {
    if (strcmp(buffer0, STgame[i]->g->name) == 0)
    {
      break;
    }
    else
    {
      
    }

  }

  STgame[i] = 0;
  for (j = i; j < counter_game; j++)
  {
    aux = STgame[j + 1];
    STgame[j] = aux;
  }

  return STgame;
}

int verifica_jogo(char *buffer0, char *buffer1, char *buffer2, glink **HTgame, tlink **HTteams)
{
  if (search_game(HTgame, buffer0) != 0)
  {
    return 1;
  }
  else
  {
    if ((search_team(HTteams, buffer1) == 0) || (search_team(HTteams, buffer2) == 0))
    {
      return 4;
    }
    else
    {
      return 5;
    }

  }

}

pGame *create_game(char *buffer0, char *buffer1, char *buffer2, int res1, int res2, tlink **HTteams)
{
  pGame *jogo = malloc(sizeof(struct game));
  jogo->score1 = res1;
  jogo->score2 = res2;
  jogo->name = my_strdup(buffer0);
  jogo->team1 = search_team(HTteams, buffer1)->t;
  jogo->team2 = search_team(HTteams, buffer2)->t;
  if (res1 > res2)
  {
    change_win_team(HTteams, buffer1, 2);
  }
  else
  {
    if (res2 > res1)
    {
      change_win_team(HTteams, buffer2, 2);
    }
    else
    {
      
    }

  }

  return jogo;
}

glink *glinkInsert(char *buffer0, char *buffer1, char *buffer2, int res1, int res2, glink *link, glink **HTgame, tlink **HTteams)
{
  int i;
  int k;
  link->g = create_game(buffer0, buffer1, buffer2, res1, res2, HTteams);
  i = hash(link->g->name);
  k = hashtwo(link->g->name);
  while (HTgame[i] != 0)
    i = (i + k) % (9677 * 2);

  HTgame[i] = link;
  return link;
}

glink *gsimplyInsert(glink *new, glink **HTgame)
{
  int i;
  int k;
  i = hash(new->g->name);
  k = hashtwo(new->g->name);
  printf("volto a inserir %s\n", new->g->name);
  while (HTgame[i] != 0)
    i = (i + k) % 9677;

  HTgame[i] = new;
  return new;
}

void glinkRemove(char *buffer0, glink **HTgame)
{
  int i;
  int j = 0;
  int k;
  glink *gaux;
  i = hash(buffer0);
  k = hashtwo(buffer0);
  while (HTgame[i] != 0)
  {
    if (strcmp(buffer0, HTgame[i]->g->name) == 0)
    {
      break;
    }
    else
    {
      i = (i + k) % 9677;
    }

  }

  if (HTgame[i] == 0)
  {
    return;
  }
  else
  {
    
  }

  free(HTgame[i]->g->name);
  free(HTgame[i]->g);
  HTgame[i] = 0;
  for (j = (i + k) % 9677; HTgame[j] != 0; j = (j + k) % 9677)
  {
    gaux = HTgame[j];
    HTgame[j] = 0;
    gaux = gsimplyInsert(gaux, HTgame);
  }

}

glink *search_game(glink **HTgame, char *nome)
{
  int i;
  int k;
  glink *link;
  i = hash(nome);
  k = hashtwo(nome);
  while (HTgame[i] != 0)
  {
    link = HTgame[i];
    if (strcmp(nome, link->g->name) == 0)
    {
      return HTgame[i];
    }
    else
    {
      i = (i + k) % (9677 * 2);
    }

  }

  return 0;
}

glink *gchangeScore(char *buffer0, int res1, int res2, glink **HTgame, tlink **HTteams)
{
  int i;
  int k;
  glink *link;
  i = hash(buffer0);
  k = hashtwo(buffer0);
  link = search_game(HTgame, buffer0);
  if (link != 0)
  {
    link->g->score1 = res1;
    link->g->score2 = res2;
    while (HTgame[i] != 0)
      i = (i + k) % 9677;

    HTgame[i] = link;
    if (res1 > res2)
    {
      change_win_team(HTteams, link->g->team1->name, 2);
      change_win_team(HTteams, link->g->team2->name, 3);
    }
    else
    {
      if (res2 > res1)
      {
        change_win_team(HTteams, link->g->team2->name, 2);
        change_win_team(HTteams, link->g->team1->name, 3);
      }
      else
      {
        
      }

    }

  }
  else
  {
    
  }

  return link;
}

bool isEmpty(glink **HTgame)
{
  int i;
  for (i = 0; i < (9677 * 2); i++)
  {
    if (HTgame[i] != 0)
    {
      return true;
    }
    else
    {
      
    }

  }

  return false;
}

void gameFree(pGame *g)
{
  free(g->name);
  free(g->team1);
  free(g->team2);
  free(g);
}

void free_gTable(glink *gtable)
{
  int i;
  pGame *g;
  for (i = 0; i <= 9677; i++)
  {
    g = &gtable->g[i];
    if (g != 0)
    {
      gameFree(g);
    }
    else
    {
      
    }

  }

  free(gtable->g);
  free(gtable);
}

