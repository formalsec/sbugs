/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "Team.h"


Team *newTeam(unsigned int id, char *name)
{
  Team *new;
  char *n;
  new = (Team *) malloc(sizeof(Team));
  new->id = id;
  new->nWon = 0;
  new->isDeleted = 0;
  n = (char *) malloc((sizeof(char)) * (strlen(name) + 1));
  strcpy(n, name);
  new->name = n;
  return new;
}

void freeTeam(Team *team)
{
  free(team->name);
  free(team);
}

