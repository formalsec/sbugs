#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "Team.h"

/* Number of victories of a team starts at 0 */
#define INIT_WIN 0

/* isDeleted property starts as false */
#define INIT_DELETED 0

/* Creates a new team.
*  @params: id - unique team identifier;
*           name - name of the team.
*  @returns: pointer to a new team.
*/
Team *newTeam(unsigned int id, char *name)
{
    Team *new;
    char *n;

    /* Allocates memory and sets the team's properties */
    new = (Team*) can_fail_malloc(sizeof(Team));
    new->id = id;
    new->nWon = INIT_WIN;
    new->isDeleted = INIT_DELETED;
    
    n = (char*) can_fail_malloc(sizeof(char)*(strlen(name)+1));
    strcpy(n, name);
    new->name = n;

    return new;
}

/* Frees the allocated memory of a team.
*  @params: team - pointer to a team.
*  @returns: void.
*/
void freeTeam(Team *team)
{
    free(team->name);
    free(team);
}