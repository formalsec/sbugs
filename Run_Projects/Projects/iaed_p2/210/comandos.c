#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comandos.h"

/*_________________Comand_Functions____________________*/ 

/* Initializes both hashtables and both lists */
void init() {
	tableJInit(INITIAL_SIZE_HTABLES);
	initArrayJ(INITIAL_SIZE_LISTS);
	tableEInit(INITIAL_SIZE_HTABLES);
	initArrayE(INITIAL_SIZE_LISTS);
}

/* Adds a game to the list of games and to the hash table of games.
   Case 'a' */
void add_game(char *name, int linha, char *nameE1, char *nameE2, int score1, int score2) {
	equipa e1, e2;
	jogo toAdd;
	if (tableJSearch(name) == NULL) {
		e1 = tableESearch(nameE1);
		e2 = tableESearch(nameE2);
		if (e2 != NULL && e1 != NULL) {
			toAdd = newJogo(name, e1, e2, score1, score2);
			tableJInsert(toAdd, insertArrayJ(toAdd));
			if (score1 > score2) {
				e1->victorys++;
			}
			if (score2 > score1) {
				e2->victorys++;
			}
		} else {
			printf("%d Equipa inexistente.\n", linha);
		}
	} else {
		printf("%d Jogo existente.\n", linha);
	}
}

/* Adds a team to the list of teams and to the hash table of teams.
   Case 'A' */
void add_team(char *name, int linha) {
	equipa e;
	if (tableESearch(name) == NULL) {
		e = newEquipa(name);
		insertArrayE(e);
		tableEInsert(e);
	} else {
		printf("%d Equipa existente.\n", linha);
	}
}

/* Searches the game in the hash table of games
   Prints the searched game.
   Case 'p' */
void search_game(char *name) {
	element searched = tableJSearch(name);
	if (searched != NULL) {
		printJogo(searched->game);
	} else {
		printf("Jogo inexistente.\n");
	}
}

/* Searches the team in the hash table of teams
   Prints the searched team.
   Case 'P' */
void search_team(char *name) {
	equipa searched = tableESearch(name);
	if (searched != NULL) {
		printEquipa(searched);
	} else {
		printf("Equipa inexistente.\n");
	}
}

/* Deletes a game from the hash table and list of games.
   Case 'r' */
void delete_game(char *name, int linha) {
	element searched = tableJSearch(name);
	if (searched == NULL) {
		printf("%d Jogo inexistente.\n", linha);
	} else {
		tableJDelete(searched->game);
		freeJogo(searched->game);
		searched->game = NULL;
	}
}

/* Changes the score of a game and updates the number of victorys of
   the teams in that game
   Case 's' */
void change_score(char *name, int score1, int score2, int linha) {
	element searched = tableJSearch(name);
	if (searched != NULL) {
		if (searched->game->r1 > searched->game->r2) {
			if (score1 == score2) {
				removeVictory(searched->game->equipa1);
			}
			if (score1 < score2) {
				removeVictory(searched->game->equipa1);
				addVictory(searched->game->equipa2);
			}
		}
		if (searched->game->r1 < searched->game->r2) {
			if (score1 == score2) {
				removeVictory(searched->game->equipa2);
			}
			if (score1 > score2) {
				removeVictory(searched->game->equipa2);
				addVictory(searched->game->equipa1);
			}
		}
		if (searched->game->r1 == searched->game->r2) {
			if (score1 > score2) {
				addVictory(searched->game->equipa1);
			}
			if (score1 < score2) {
				addVictory(searched->game->equipa2);
			}
		}
		changeScore(searched->game, score1, score2);
	} else {
		printf("%d Jogo inexistente.\n", linha);
	}
}

/* Prints all the games in the order of insertion
   Case 'l' */
void print_games(int linha) {
	printJogos(linha);
}

/* Prints the teams with the most victorys by alphabetical order
   Case 'g' */
void print_teams(int linha) {
	if (getNequipas() > ZERO) {
		int n = putBiggerOnTop();
		heapsort(n);
		printEquipas(linha, n);
	}
}

/* Before exiting the program frees all allocated memory
   Frees the lists first and then the hash tables
   Case 'x' */
void free_all() {
	freeArrayJ();
	freeArrayE();
	freeTableE();
	freeTableJ();
}