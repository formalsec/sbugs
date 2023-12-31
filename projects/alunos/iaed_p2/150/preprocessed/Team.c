#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Team.h"


Team *newTeam(char *str)
{
  Team *new = 0;
  char *name = 0;
  int length = strlen(str) + 1;
  new = malloc(sizeof(Team));
  name = malloc((sizeof(char)) * length), strcpy(name, str);
  new->name = name;
  new->wins = 0;
  return new;
}

void printTeam(Team *team)
{
  printf("%s", team->name);
}

void destroyTeam(Team *team)
{
  free(team->name);
  free(team);
}

