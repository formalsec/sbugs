#ifndef __TEAM__
#define __TEAM__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*Estrutura Team presenta na hash table de equipas */


typedef struct team{
	char *name_team;
	int numero_wins;
} Team;


void free_team(Team *t);

Team *cria_team(char team_name[]);


#endif


