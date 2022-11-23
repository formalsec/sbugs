#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "Team.h"



/* Function creates new team of name name and returns pointer to it */
Team* newTeam(char* name){
    Team* ptr_team = (Team*)can_fail_malloc(sizeof(Team));    /* Allocate space for Team structure */

    ptr_team -> name = (char*)can_fail_malloc(sizeof(char)*(strlen(name)+1));  /* Allocate and point to space for name of Team */
    
    /* Initialize team with necessary information */
    strcpy(ptr_team -> name, name);
    ptr_team ->victories = 0;

    return ptr_team;
}


/* Function deletes team pointed by tm freeing all allocated space */
void deleteTeam(Team* tm){
    free(tm->name);
    free(tm);
}


/* Function changes victories component of team pointed by pteam */
void change_victory(Team* pteam, int change){
    if(change == WIN) pteam->victories++;
    if(change == LOSS) pteam->victories--;
}