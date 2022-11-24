#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "newTeam.h"

/*------------------------------------------------------------------------------------------------*/
teamNodeP newTeam (char* name) {
    
    /* Ponteiro para uma equipa */
    Team *equipa;

    /* Aloca memoria para uma equipa */
    equipa= (Team*) can_fail_malloc (sizeof(Team)); /*Aloco memoria para a estrutura Equipa*/

    /* Aloca memoria para o nome da equipa */
    equipa->name = (char*) can_fail_malloc (sizeof(char)*(strlen(name)+1));
    strcpy(equipa->name, name);

    equipa->wins = 0;

    return newTeamNode(equipa);

}

/*------------------------------------------------------------------------------------------------*/
teamNodeP newTeamNode (Team * eq) {

    /* Aloca memoria para um no de uma equipa */
    TeamNode *newTeam = (TeamNode*) can_fail_malloc (sizeof(TeamNode));

    newTeam->team = eq;
    newTeam->next = NULL;
    newTeam->prev = NULL;

    return newTeam;

}