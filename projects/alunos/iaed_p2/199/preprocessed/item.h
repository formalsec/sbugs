#ifndef ITEM_H
#define ITEM_H

/*Estrutura de dados de um jogo*/
typedef struct game {
	int id; /*para guardar a ordem em que foram inseridos os jogos*/
	char* name;
	char* team1;
	char* team2;
	int score1;
	int score2;
}Game;


/*Estrutura de dados de uma equipa*/
typedef struct team{
	char* name;
	int cont; /*contador de vitorias acumuladas pela equipa*/
}Team;

/*Prototipos de funcoes*/
Game* newG(int id, char* name, char* team1, char* team2, int score1, int score2);
void freeGame(Game* game);
Team* newT(char* name);
void freeTeam(Team* team);
#endif
