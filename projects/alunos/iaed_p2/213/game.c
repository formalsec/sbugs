#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"


/* Elimina jogo, libertando a memoria associada */
void freeGame(Game game) {
	free(game->name);
	free(game);
}


/* Faz print do jogo */
void printGame(Game game, int c) {
	printf("%d %s %s %s %d %d\n", 
		c, 
		game->name, 
		game->team1->name, 
		game->team2->name,
		game->score1,  
		game->score2);
}


/* Cria um novo jogo, alocando o espaco necessario */
Game newGame(char * name, Team team1, Team team2, int score1, int score2) {
	Game new = (Game) can_fail_malloc(sizeof(struct game_node));

	new->name = can_fail_malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(new->name, name);
	new->team1 = team1;
	new->team2 = team2;
	new->score1 = score1;
	new->score2 = score2;
	return new;
}


/* Encontra a equipa que venceu o jogo */
Team winner(Game game) {
	if (game->score1 > game->score2)
		return game->team1;
	else if (game->score2 > game->score1)
		return game->team2;

	/* Foi empate */
	return NULL;
}


/* Muda o resultado do jogo */
void changeScore(Game game, int nScore1, int nScore2) {
	Team win2; 

	/* Equipa que venceu com o resultado anterior */	
	Team win1 = winner(game);

	/* Muda resultado */
	game->score1 = nScore1;
	game->score2 = nScore2;

	/* Equipa que venceu com o novo resultado */
	win2 = winner(game);

	/* Altera numero de vitorias */
	if (win1)
		rm_win(win1);

	if (win2)
		add_win(win2);
}
