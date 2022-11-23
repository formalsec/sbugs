#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "team.h"
#include "messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Allocs the memory to the team structure.
 * Allocs the memory for the name and copies it.
 * Initiates the victories with 0.
 * Requires: char array with the name.
 * Return: the pointer to the team.
 */
Team *createTeam(char *name) {
    Team *team = (Team *) can_fail_malloc(sizeof(Team));
    int length = strlen(name);
    team->name = (char *) can_fail_malloc(sizeof(char) * (length + 1));
    strcpy(team->name, name);
    team->victories = 0;
    return team;
}

/*
 * Frees the team and all its attributes.
 * The team pointer cannot be NULL.
 * Requires: void pointer to the team.
 */
void deleteTeam(void *team) {
    if (team != NULL) {
        free(((Team *) team)->name);
        free(team);
    }
}

/*
 * Updates the victories counter of the team.
 * The team pointer cannot be NULL.
 * Requires: Team pointer and the int with the amount to add/subtract.
 */
void updateVictories(Team *team, int newVictories) {
    if (team != NULL) {
        team->victories += newVictories;
    }
}

/*
 * Function used to compare the team with the given name using the string compare function.
 * The name and the team cannot be NULL.
 * Requires: char array with the name and void pointer to the team.
 * Returns: 1 if the team's name is equals with the name 0 otherwise.
 */
int compareTeamFunction(char *name, void *team) {
    if (team != NULL && name != NULL) {
        if (strcmp(name, ((Team *) team)->name) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * Function used to print all the team's information.
 * The team pointer cannot be NULL.
 * Requires: void pointer to the team and int pointer to the command counter.
 */
void printTeam(void *team, int *cmdCounter) {
    if (team != NULL) {
        printf(TEAM_INFO_MESSAGE, *cmdCounter, ((Team *) team)->name, ((Team *) team)->victories);
    }
}

/*
 * Function used to print the best Team message.
 * The team pointer cannot be NULL.
 * Requires: void pointer to the team and int pointer to the command counter.
 */
void bestTeamsFunction(void *team, int *cmdCounter) {
    printf(BEAST_TEAMS_MESSAGE, *cmdCounter, ((Team *) team)->name);
}
