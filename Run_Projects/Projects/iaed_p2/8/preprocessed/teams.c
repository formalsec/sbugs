/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "myLib.h"
#include "competition.h"
#include "game.h"
#include "teams.h"
#include "team.h"


unsigned long hashCode(char *str)
{
  unsigned long i = 0;
  int j;
  for (j = 0; str[j]; j++)
    i += str[j];

  return i % 100;
}

TeamsDataItem *teams_create_item(Team *t)
{
  extern char *strdup(const char *);
  TeamsDataItem *item = (TeamsDataItem *) malloc(sizeof(TeamsDataItem));
  if (errno > 0)
  {
    perror("teams_create_item: malloc");
    exit(errno);
  }
  else
  {
    
  }

  ;
  item->key = strdup(t->name);
  item->team = t;
  return item;
}

Teams *teams_new()
{
  Teams *tt = (Teams *) malloc(sizeof(Teams));
  if (errno > 0)
  {
    perror("teams_new: malloc 1");
    exit(errno);
  }
  else
  {
    
  }

  ;
  tt->count = 0;
  tt->items = (TeamsDataItem **) calloc(100, sizeof(TeamsDataItem *));
  if (errno > 0)
  {
    perror("teams_new: malloc 2");
    exit(errno);
  }
  else
  {
    
  }

  ;
  return tt;
}

void teams_free_item(TeamsDataItem *item)
{
  free(item->key);
  team_free(item->team);
  free(item);
}

void teams_free(Teams *tt)
{
  int i;
  if (tt == 0)
  {
    printf("%s: null pointer\n", "teams_free");
    exit(1);
  }
  else
  {
    
  }

  ;
  for (i = 0; i < 100; i++)
  {
    if (tt->items[i] != 0)
    {
      teams_free_item(tt->items[i]);
    }
    else
    {
      
    }

  }

  free(tt->items);
  free(tt);
}

void teams_add(Teams *tt, Team *t)
{
  int hashIndex;
  TeamsDataItem *di;
  if (tt == 0)
  {
    printf("%s: null pointer\n", "teams_add");
    exit(1);
  }
  else
  {
    
  }

  ;
  if (tt->count == 100)
  {
    printf("Hash table is full");
    exit(1);
  }
  else
  {
    
  }

  hashIndex = hashCode(t->name);
  di = teams_create_item(t);
  while (tt->items[hashIndex] != 0)
  {
    ++hashIndex;
    hashIndex = hashIndex % 100;
  }

  tt->items[hashIndex] = di;
  tt->count++;
}

Team *teams_get_team(Teams *tt, char *team_name)
{
  int hashIndex;
  int steps;
  TeamsDataItem *di;
  if (tt == 0)
  {
    printf("%s: null pointer\n", "teams_get_team");
    exit(1);
  }
  else
  {
    
  }

  ;
  hashIndex = hashCode(team_name);
  di = tt->items[hashIndex];
  steps = 1;
  while (((steps != 100) && (di != 0)) && (strcmp(team_name, di->key) != 0))
  {
    hashIndex++;
    steps++;
    di = tt->items[hashIndex];
  }

  if (di == 0)
  {
    return 0;
  }
  else
  {
    return di->team;
  }

}

