/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "teams.h"


char *strdup(const char *s)
{
  size_t len = strlen(s) + 1;
  void *new = malloc(len);
  if (new == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return (char *) memcpy(new, s, len);
}

teamList *addTeam(teamList *t, char *name)
{
  teamList *newTeam = 0;
  teamList *head = t;
  newTeam = malloc(sizeof(teamList));
  if (!newTeam)
  {
    exit(1);
  }
  else
  {
    
  }

  if (!head)
  {
    newTeam->next = 0;
  }
  else
  {
    newTeam->next = head;
  }

  head = newTeam;
  newTeam->name = strdup(name);
  newTeam->won = 0;
  return head;
}

gameList *addGame(gameList *g, char *name, teamList *team1, teamList *team2, int score1, int score2)
{
  gameList *newGame = 0;
  gameList *head = g;
  gameList *tail = g;
  newGame = malloc(sizeof(gameList));
  if (!newGame)
  {
    exit(1);
  }
  else
  {
    
  }

  if (!head)
  {
    head = newGame;
    newGame->prev = 0;
  }
  else
  {
    while (tail->next)
      tail = tail->next;

    tail->next = newGame;
    newGame->prev = tail;
  }

  newGame->next = 0;
  newGame->name = strdup(name);
  newGame->team1 = team1;
  newGame->team2 = team2;
  newGame->score1 = score1;
  newGame->score2 = score2;
  return head;
}

teamList *findTeam(teamList *t, char *name)
{
  teamList *cur = t;
  while (cur)
  {
    if (!strcmp(cur->name, name))
    {
      return cur;
    }
    else
    {
      
    }

    cur = cur->next;
  }

  return 0;
}

gameList *findGame(gameList *g, char *name)
{
  gameList *cur = g;
  while (cur)
  {
    if (!strcmp(cur->name, name))
    {
      return cur;
    }
    else
    {
      
    }

    cur = cur->next;
  }

  return 0;
}

gameList *deleteGame(gameList *g, gameList *game)
{
  gameList *prev;
  gameList *next;
  if ((!game) || (!g))
  {
    return g;
  }
  else
  {
    
  }

  prev = game->prev;
  next = game->next;
  if (g == game)
  {
    g = g->next;
  }
  else
  {
    
  }

  if (prev)
  {
    prev->next = next;
  }
  else
  {
    
  }

  if (next)
  {
    next->prev = prev;
  }
  else
  {
    
  }

  free(game->name);
  free(game);
  return g;
}

void freeTeams(teamList *t)
{
  teamList *cur = t;
  teamList *next;
  while (cur)
  {
    next = cur->next;
    free(cur->name);
    free(cur);
    cur = next;
  }

}

void freeGames(gameList *g)
{
  gameList *cur = g;
  gameList *next;
  while (cur)
  {
    next = cur->next;
    free(cur->name);
    free(cur);
    cur = next;
  }

}

