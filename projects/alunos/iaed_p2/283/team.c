#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "team.h"

/*Liberta a equipa em causa*/

void free_team(Team *t){
	free(t->name_team);
	free(t);
}


/*Cria a equipa em causa incializando as suas wins a 0*/


Team *cria_team(char team_name[]){
	Team *new_team = can_fail_malloc(sizeof(Team));
	new_team -> numero_wins = 0;
	new_team->name_team= can_fail_malloc(sizeof(char)*(strlen(team_name)+1));
	strcpy(new_team->name_team,team_name);
	return new_team;


}
