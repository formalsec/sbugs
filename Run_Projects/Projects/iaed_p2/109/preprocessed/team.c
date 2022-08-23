/*File generated by PreProcessor.py*/


#include "team.h"


Team newTeam(char *name)
{
  Team new = (Team) malloc(sizeof(struct team));
  new->name = strDup(name);
  new->wins = 0;
  return new;
}

HashTeam tHashInit(int max)
{
  int i;
  HashTeam table = (HashTeam) malloc(sizeof(struct teamHash));
  table->N = 0;
  table->M = max;
  table->teams = (Team *) malloc(table->M * (sizeof(Team)));
  for (i = 0; i < table->M; i++)
  {
    table->teams[i] = 0;
  }

  return table;
}

HashTeam tHashInsert(HashTeam *table, Team team)
{
  int i = hash(team->name, (*table)->M);
  HashTeam newtable;
  while ((*table)->teams[i])
  {
    i = (i + 1) % (*table)->M;
  }

  (*table)->teams[i] = team;
  (*table)->N++;
  if ((*table)->N >= ((*table)->M / 2))
  {
    {
      newtable = tHashExpand(*table);
      return newtable;
    }
  }
  else
  {
    
  }

  return *table;
}

HashTeam tHashExpand(HashTeam table)
{
  int i;
  HashTeam newtable = tHashInit(table->M * 2);
  for (i = 0; i < table->M; i++)
  {
    if (table->teams[i])
    {
      {
        tHashInsert(&newtable, table->teams[i]);
      }
    }
    else
    {
      
    }

  }

  free(table->teams);
  free(table);
  return newtable;
}

Team tHashSearch(HashTeam table, char *name)
{
  int i = hash(name, table->M);
  while (table->teams[i])
  {
    if (strcmp(name, table->teams[i]->name) == 0)
    {
      {
        return table->teams[i];
      }
    }
    else
    {
      {
        i = (i + 1) % table->M;
      }
    }

  }

  return 0;
}

void printTeam(Team team)
{
  printf("%s %d\n", team->name, team->wins);
}

void freeTeam(Team team)
{
  free(team->name);
  free(team);
}

void tHashFree(HashTeam table)
{
  int i;
  for (i = 0; i < table->M; i++)
  {
    if (table->teams[i])
    {
      {
        freeTeam(table->teams[i]);
      }
    }
    else
    {
      
    }

  }

  free(table->teams);
  free(table);
}

