#ifndef TEAM_H
#define TEAM_H

#include <stdlib.h>

#define NULLteam (NULL)

/* Structure for a team */
struct team{
    char *name;
    /* Number of games won */
    unsigned int won;
};

/* Definition for a pointer for the type "team" */
typedef struct team* Team;

/* Prototypes */

/* Creates a new team */
Team newTeam(char *name, int n);
/* Frees the memory associated with the team given */
void freeTeam(Team team);

#endif
