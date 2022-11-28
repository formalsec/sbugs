#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"
#include "hash.h"
#include "list.h"


static hash *games;
static hash *teams;
unsigned int hashCode(char *str)
{
  unsigned long hash = 5381;
  int pos;
  int c;
  while (c = *(str++))
    hash = ((hash << 5) + hash) + c;

  pos = hash % 1009;
  return pos;
}

void HASHinit()
{
  int i;
  games = (hash *) malloc(1009 * (sizeof(hash)));
  teams = (hash *) malloc(1009 * (sizeof(hash)));
  for (i = 0; i < 1009; i++)
  {
    games[i] = 0;
    teams[i] = 0;
  }

}

void hashInsertTeam(Team *team)
{
  hash new = (hash) malloc(sizeof(struct hash_node));
  new->id = nameOfTeam(team);
  new->item = (void *) team;
  new->next = 0;
  hashInsert(teams, new, nameOfTeam(team));
}

void hashInsertGame(Game *game)
{
  hash new = (hash) malloc(sizeof(struct hash_node));
  new->id = getName(game);
  new->item = (void *) game;
  new->next = 0;
  hashInsert(games, new, getName(game));
}

void hashInsert(hash *table, hash item, char *str)
{
  unsigned int pos = hashCode(str);
  hash aux;
  if (table[pos] == 0)
  {
    table[pos] = item;
  }
  else
  {
    for (aux = table[pos]; aux->next != 0; aux = aux->next)
      ;

    aux->next = item;
  }

}

Game *searchGameHash(char *str)
{
  Game *game = (Game *) hashSearch(games, str);
  return game;
}

Team *searchTeamHash(char *str)
{
  Team *team = (Team *) hashSearch(teams, str);
  return team;
}

void *hashSearch(hash *table, char *str)
{
  unsigned int pos = hashCode(str);
  hash aux;
  if (table[pos] == 0)
  {
    return 0;
  }
  else
  {
    
  }

  for (aux = table[pos]; aux != 0; aux = aux->next)
  {
    if (!strcmp(str, aux->id))
    {
      return aux->item;
    }
    else
    {
      
    }

  }

  return 0;
}

void *hashRemove(char *str)
{
  unsigned int pos = hashCode(str);
  item returnItem;
  hash aux;
  hash prev = 0;
  for (aux = games[pos]; (aux != 0) && strcmp(aux->id, str); aux = aux->next)
    prev = aux;

  if (aux != 0)
  {
    if (prev != 0)
    {
      prev->next = aux->next;
    }
    else
    {
      games[pos] = aux->next;
    }

    returnItem = aux->item;
    free(aux);
    return returnItem;
  }
  else
  {
    
  }

  return 0;
}

void particularHashClean(hash *head, void (*freeItem)(void *item))
{
  hash aux;
  hash prev;
  int i;
  for (i = 0; i < 1009; i++)
  {
    for (aux = head[i]; aux != 0; aux = prev)
    {
      prev = aux->next;
      freeItem(aux->item);
      free(aux);
    }

  }

}

void hashClean()
{
  particularHashClean(games, freeGame);
  particularHashClean(teams, freeTeam);
  free(games);
  free(teams);
}

char **getBestTeams(int *length, unsigned int *wins)
{
  int i;
  int amount = 0;
  int high = 0;
  char **out = (char **) malloc(sizeof(char *));
  hash aux;
  for (i = 0; i < 1009; i++)
  {
    for (aux = teams[i]; aux != 0; aux = aux->next)
      if (amountOfWins(aux->item) == high)
    {
      amount++;
      out = (char **) realloc(out, (sizeof(char *)) * amount);
      out[amount - 1] = nameOfTeam(aux->item);
    }
    else
    {
      if (amountOfWins(aux->item) > high)
      {
        amount = 1;
        out = (char **) realloc(out, sizeof(char *));
        out[0] = nameOfTeam(aux->item);
        high = amountOfWins(aux->item);
      }
      else
      {
        
      }

    }


  }

  *length = amount;
  *wins = high;
  return out;
}
