#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "team.h"


/* Cria uma nova equipa, alocando o espaco necessario */
Team newTeam(char *name) {
	Team new = (Team) can_fail_malloc(sizeof(struct team_node));

	new->wins = 0;
	new->name = can_fail_malloc(sizeof(char) * (strlen(name)+1));
	strcpy(new->name, name);

	return new;
}


/* Elimina equipa, libertando a memoria associada */
void freeTeam(Team t) {
	free(t->name);
	free(t);
}


/* Faz print da equipa */
void printTeam(Team t, int c) {
	printf("%d * %s\n", c, t->name);
}


/* Faz print da equipa e das suas vitorias */
void printTeamWins(Team t, int c) {
	printf("%d %s %d\n", c, t->name, t->wins);
}


/* Adiciona uma vitoria e devolve o numero de vitorias */
int add_win(Team t) {
	return ++t->wins;
}


/* Remove uma vitoria e devolve o numero de vitorias */
int rm_win(Team t) {
	return --t->wins;
}
