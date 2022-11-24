#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "cmds.h"


/* Comando 'a': adiciona um novo jogo */
void cmd_a(int c, System system) {
	char name[SIZE_STR], t1[SIZE_STR], t2[SIZE_STR];
	int score1, score2;
	Team team1, team2;

	scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d",
		name, t1, t2, &score1, &score2);

	/* Ja existe esse jogo */
	if (G_search(system->games, name)) {
		printf("%d Jogo existente.\n", c);
		return;
	}

	/* Encontra equipas */
	team1 = T_search(system->teams, t1);
	team2 = T_search(system->teams, t2);

	/* Cria novo jogo e adiciona a hashtable e a lista */
	if (team1 && team2) {
		Game game = newGame(name, team1, team2, score1, score2);
		G_insert(system->games, game);
		add_last(system->games_dl, game);

		if (score1 != score2)
			add_win(score1 > score2 ? team1 : team2);		/* adiciona vitoria a equipa vencedora */
	}
	else
		printf("%d Equipa inexistente.\n", c);
}	


/* Comando 'l': Lista todos os jogos introduzidos */
void cmd_l(int c, System system) {
	printGames(system->games_dl, c);
	return;
}


/* Comando 'p': Procura um jogo com o nome dado */
void cmd_p(int c, System system) {
	Game game;
	char name[SIZE_STR];

	scanf(" %[^:\n]", name);

	if ((game = G_search(system->games, name)))
		printGame(game, c);

	else 
		printf("%d Jogo inexistente.\n", c);
}


/* Comando 'r': Apaga um jogo dado um nome */
void cmd_r(int c, System system) {
	char name[SIZE_STR];
	Game game;
	Team win;

	scanf(" %[^:\n]", name);

	/* Nao existe o jogo */
	if ((game = G_search(system->games, name)) == NULL) {
		printf("%d Jogo inexistente.\n", c);
		return;
	}

	win = winner(game);

	/* Remove vitoria do vencedor */
	if (win)
		rm_win(win);

	/* Remove jogo da lista duplamente ligada */
	rm_node(system->games_dl, game);

	/* Elimina jogo da hashtable e do sistema */
	G_delete(system->games, name);
}


/* Comando 's': Altera o score de um jogo dado o nome */
void cmd_s(int c, System system) {
	Game game;
	int score1, score2;
	char name[SIZE_STR];

	scanf(" %[^:\n]:%d:%d", name, &score1, &score2);

	/* Encontra jogo */
	game = G_search(system->games, name);

	/* Altera o resultado */
	if (game)
		changeScore(game, score1, score2);

	else
		printf("%d Jogo inexistente.\n", c);

}


/* Comando 'A': Adiciona nova equipa */
void cmd_A(int c, System system) {
	Team team;
	char name[SIZE_STR];

	scanf(" %[^_\n]", name);

	/* Cria nova equipa e insere na hashtable */
	if (T_search(system->teams, name) == NULL) {
		team = newTeam(name);
		T_insert(system->teams, team);
	}
	
	else 
		printf("%d Equipa existente.\n", c);

}


/* Comando 'P': Procura uma equipa dado o nome */
void cmd_P(int c, System system) {
	char name[SIZE_STR];
	Team team;

	scanf(" %[^_\n]", name);

	if ((team = T_search(system->teams, name)))
		printTeamWins(team, c);

	/* Nao existe equipa */
	else
		printf("%d Equipa inexistente.\n", c);
}


/* Comando 'g': Lista por ordem lexicografica equipas que ganharam mais jogos */
void cmd_g(int c, System system) {
	int num, max;

	/* Encontra max de vitorias e num de equipas com essas vitorias */
	max = find_winner(system->teams, &num);

	if (max >= 0) {
		int i;

		/* Tabela com as equipas com mais vitorias */
		Team * winners = can_fail_malloc(sizeof(Team) * num);
		get_winners(system->teams, winners, max);

		/* Ordena lexicograficamente */
		sort(winners, 0, num-1);

		/* Faz print das equipas com mais vitorias */
		printf("%d Melhores %d\n", c, max);
		for (i = 0; i < num; i++) {
			printTeam(winners[i], c);
		}
		
		free(winners);
	}
}
