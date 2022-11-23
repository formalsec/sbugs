#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include "teams_ht.h"


/* Inicializa hashtable de equipas */
Team * T_init() {
	int i;

	/* Aloca espaco para hashtable de equipas */
	Team * teams = can_fail_malloc(SIZE_HT*sizeof(Team));

	/* Inicializa ponteiros para jogos a NULL */
	for (i = 0; i < SIZE_HT; i++)
		teams[i] = NULL;

	return teams;
}


/* Insere team na tabela de equipas */
void T_insert(Team * teams, Team team) {
	int i = hash(teamName(team), SIZE_HT);

	/* Coloca no espaco livre seguinte */
	while (teams[i])
		i = (i+1) % SIZE_HT;

	teams[i] = team;
}


/* Procura team na tabela */
Team T_search(Team * teams, char * name) {
	int i = hash(name, SIZE_HT);

	/* Procura nos espacos seguidos ao valor de hash */
	while (teams[i]) {

		/* Encontrou equipa */
		if (eq(teamName(teams[i]), name))
			return teams[i];

		else
			i = (i+1) % SIZE_HT;
	}

	/* Nao encontrou equipa */
	return NULL;
}


/* Encontra equipas que ganharam mais jogos
Devolve valor de jogos ganho
num fica com o numero de equipas com o maior numero de vitorias */
int find_winner(Team * teams, int * num) {
	int i, max = -1;
	*num = 0;

	for (i = 0; i < SIZE_HT; i++) {
		if (teams[i]) {

			/* Equipa tem mais vitorias */
			if (teamWins(teams[i]) > max) {
				max = teamWins(teams[i]);
				*num = 1;
			}

			/* Equipa tem o mesmo numero de vitorias */
			else if (teamWins(teams[i]) == max)
				(*num)++;		
		}
	}

	return max;
}


/* Forma array com as equipas com max vitorias */
void get_winners(Team * teams, Team * winners, int max) {
	int i, j = 0;

	for (i = 0; i < SIZE_HT; i++)
		if (teams[i] && teamWins(teams[i]) == max)
			winners[j++] = teams[i];
}


/* Destroi tabela e liberta memoria associada */
void T_destroy(Team * teams) {
	int i;
	for (i = 0; i < SIZE_HT; i++)
		if (teams[i])
			freeTeam(teams[i]);

	free(teams);
}
