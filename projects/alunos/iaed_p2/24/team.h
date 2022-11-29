#include "auxiliar.h"

typedef struct team
{
    char *name;
    int victories;
} * Team;

Team newTeam(char *name);

void printTeam(Team team);

void freeTeam(Team team);