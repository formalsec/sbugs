#ifndef _TEAM_
#define _TEAM_

/* Structure representing a team */
typedef struct Team
{
    char *name;
    int nWon;
    int isDeleted;
    unsigned int id;
} Team;

/* Creates a new team */
Team *newTeam(unsigned int id, char *name);

/* Frees the allocated memory of the team */
void freeTeam(Team *team);

#endif