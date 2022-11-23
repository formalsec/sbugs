#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "teams.h"


ptrTeam teamInit(char* name){ /*Alocar memoria para team*/
    
    if(strlen(name) < MAXNAME){
        ptrTeam team = can_fail_malloc(sizeof(struct team)); 
              
        team->name = can_fail_malloc(sizeof(char*) * (strlen(name)) + 1); /* Allocate just enough memory for the string */
        strcpy(team->name, name);
        team->wins = 0;

        return team;
    }
    return NULL;
}

int teamEmpty(ptrTeam team){
    return team == NULL;
}

char* teamName(ptrTeam team){
    if(!teamEmpty(team))
        return team->name;
    return NULL;
}

int teamWins(ptrTeam team){
    if(!teamEmpty(team))
        return team->wins;
    return 0;
}

void teamPrint(int NL, ptrTeam team){
    if(!teamEmpty(team)){
        printf("%d %s %d\n", NL, teamName(team), teamWins(team)); /* Print the team's data */
        return;
    }
    printf("%d Equipa inexistente.\n", NL);
}

void teamDestroy(ptrTeam team){
    free(team->name);
    free(team);
}
