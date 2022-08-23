#ifndef _GAME_H_
#define _GAME_H_

typedef struct game {
	char *name;
	char *team1, *team2;
	int score1, score2;
} *Game;


/*
Criacao de um jogo. Recebe os parametros referentes a 'game'. e 
Retorno: ponteiro para um jogo.
*/
Game create_game(char *name, char *team1, char *team2, int score1, int score2);

#endif