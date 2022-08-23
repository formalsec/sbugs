#include "TEAM.h"

/*Elimina a equipa t*/
void freeTeam(Team t){
	free(t->name);
	free(t);
}

/*Cria uma nova equipa de nome name*/
Team newTeam(char* name){
	size_t size = strlen(name) + 1;
	Team new = (Team)malloc(sizeof(struct team));
	new->name = (char*) malloc(sizeof(char) * size);
	strncpy(new->name, name, size);
	new->score = 0;
	return new;
}
