#ifndef TEAM_H
#define TEAM_H
/*
 * Struct of the adt team
 */
typedef struct team {
    char *name; /*Team's name*/
    int victories; /*Victories counter*/
} Team;

Team *createTeam(char *name);

void deleteTeam(void *team);

void updateVictories(Team *team, int newVictories);

int compareTeamFunction(char *key, void *b);

void printTeam(void *team, int *cmdCounter);

void bestTeamsFunction(void *team, int *cmdCounter);

#endif
