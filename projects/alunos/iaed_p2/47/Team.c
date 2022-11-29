#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Team.h"

TEAM newTeam(char *name) {
	TEAM g =can_fail_malloc(sizeof(struct Team));                  /*aloca memoria para a estrutura da equipa*/
    g->Teamname=can_fail_malloc(sizeof(char)*(strlen(name)+1));    /*aloca memoria para o nome da equipa*/
    strcpy(g->Teamname,name);                            
    g->wongames=0;
    return g;
}

void deleteTeam(TEAM i) {
	if (i)                          /*Se a equipa existir*/
    {
        free(i->Teamname);          /*liberta a memoria alocada para o nome*/
        free(i);                    /*liberta a memoria alocada para a estrutura da equipa*/
    }
      
}

void seeTeam(TEAM i) {
    if (i) printf("%s",i->Teamname);                
} 

