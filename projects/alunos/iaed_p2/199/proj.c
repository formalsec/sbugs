#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#define SIZEGAME 160 /*Tamanho da lista de jogos*/
#define SIZETEAM 160 /*Tamanho da lista de equipas*/
#define MAX_SIZE 1023 /*Numero maximo de caracteres para descrever uma team ou game*/


/*Prototipos de funcoes*/
void a(pGame* g, pTeam* t, int *id, char *name, char *team1, char *team2, int score1, int score2, int line);
void A(pTeam* t, char *name, int *numTeams, int line);
void l(pGame* heads, int gameId, int line);
void p(pGame* g, char* name, int line);
void P(pTeam* t, char* name, int line);
void r(pGame* g, pTeam* t, char* name, int line);
void s(pGame* g, pTeam* t, char* name, int score1, int score2, int line);
void g(pTeam* t, int numTeams, int line);
int compare(const void * p1, const void* p2);

/*Funcao main do programa que chama as funcoes associadas a cada comando*/
int main() {
	char game[MAX_SIZE];
	char team1[MAX_SIZE];
	char team2[MAX_SIZE];
	int score1, score2;
	char team[MAX_SIZE];
	int gameId = 0;
	int line = 1;
	int numTeams = 0;
	char command;

	pGame* hashGame = initG(SIZEGAME);
	pTeam* hashTeam = initT(SIZETEAM);
	
	while(1){
		command = getchar();
			switch(command){
				case 'a':
					getchar();
					scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d", game, team1, team2, &score1, &score2);
					a(hashGame, hashTeam, &gameId, game, team1, team2, score1, score2, line);
					break;
				case 'A':
					getchar();
					scanf("%[^:\n]", team);
					A(hashTeam, team, &numTeams, line);
					break;
				case 'l':
					getchar();
					l(hashGame, gameId, line);
					break;
				case 'p':
					getchar();
					scanf("%[^:\n]", game);
					p(hashGame, game, line);
					break;
				case 'P':
					getchar();
					scanf("%[^:\n]", team);
					P(hashTeam, team, line);
					break;
				case 'r':
					getchar();
					scanf("%[^:\n]", game);
					r(hashGame, hashTeam, game, line);
					break;
				case 's':
					getchar();
					scanf("%[^:\n]:%d:%d", game, &score1, &score2);
					s(hashGame, hashTeam, game, score1, score2, line);
					break;
				case 'g':
					getchar();
					g(hashTeam, numTeams, line);
					break;
				case 'x':
					freeG(hashGame, SIZEGAME);
					freeT(hashTeam, SIZETEAM);
				return EXIT_SUCCESS;
			}
			if(command != '\n'){
				line++;
			}
		}
		freeG(hashGame, SIZEGAME);
		freeT(hashTeam, SIZETEAM);
	return EXIT_FAILURE;
}

/*Comando a - Adiciona um novo jogo.*/
void a(pGame* g, pTeam* t, int *id, char *name, char *team1, char *team2, int score1, int score2, int line){
	Game* game;
	Team* team;

	if(searchG(g, name, SIZEGAME)!=NULL){
		printf("%d Jogo existente.\n", line);
		return;
	}
	if(searchT(t, team1, SIZETEAM)==NULL || searchT(t, team2, SIZETEAM)==NULL){
		printf("%d Equipa inexistente.\n", line);
		return;
	}

	game = newG(*id, name, team1, team2, score1, score2);
	insertG(g, game, SIZEGAME);	
	(*id)++;

	if(score1==score2){				
		return;
	}
	if(score1 > score2){
		team=searchT(t, team1, SIZETEAM);
	}else{
		team=searchT(t, team2, SIZETEAM);
	}
	team->cont++;
}

/*Comando A - Adicona um nova equipa.*/
void A(pTeam* t, char *name, int *numTeams, int line){
	Team* team;
	if(searchT(t, name, SIZETEAM)!=NULL){
		printf("%d Equipa existente.\n", line);
		return;
	} 
	team = newT(name);
	insertT(t, team, SIZETEAM);
	(*numTeams)++;
}


/*Comando l - Lista todos os jogos introduzidos.*/
void l(pGame* heads, int gameId, int line){
	int i;
	Game** table = can_fail_malloc(sizeof(Game*)*gameId);

	for (i = 0; i < gameId; i++){
		table[i] = NULL;
	}
	
	for (i = 0; i < SIZEGAME; i++){
		pGame temp = heads[i];
		while(temp != NULL){
			table[temp->game->id] = temp->game;
			temp = temp->next;
		}
	}

	for (i = 0; i < gameId; i++){
		if(table[i]==NULL){
			continue;
		}
		printf("%d %s %s %s %d %d\n", line, table[i]->name, table[i]->team1, table[i]->team2, table[i]->score1, table[i]->score2);	
	}
	free(table);
}


/*Comando p - Procura um jogo com um nome dado.*/
void p(pGame* g, char* name, int line){
	Game* game = searchG(g, name, SIZEGAME);
	
	if(game == NULL){
		printf("%d Jogo inexistente.\n", line);
	}else{
		printf("%d %s %s %s %d %d\n", line, game->name, game->team1, game->team2, game->score1, game->score2);
	}
}


/*Comando P - Procura uma equipa dado um nome.*/
void P(pTeam* t, char* name, int line){
	Team* team = searchT(t, name, SIZEGAME);
	
	if(team == NULL){
		printf("%d Equipa inexistente.\n", line);
	}else{
		printf("%d %s %d\n", line, team->name, team->cont);
	}
}


/*Comando r - Apaga um jogo dado um nome*/
void r(pGame* g, pTeam* t, char* name, int line){
	Game* game = searchG(g, name, SIZEGAME);
	Team* team;
	char* prevWinner;

	if(game == NULL){
		printf("%d Jogo inexistente.\n", line);
		return;
	}

	/*Atualizar cont da equipa caso jogo seja apagado*/
	if(game->score1 != game->score2){
		if(game->score1 > game->score2){
			prevWinner = game->team1;
		}else{
			prevWinner = game->team2;
		}
		team = searchT(t, prevWinner, SIZETEAM);
		team->cont--;
	}
	deleteG(g, name, SIZEGAME);
}


/*Comando s - Altera o score de um jogo dado o nome.*/
void s(pGame* g, pTeam* t, char* name, int score1, int score2, int line){
	char* prevWinner;
	char* newWinner;
	Team* team1, *team2;
	Game* game = searchG(g, name, SIZEGAME);

	if(game == NULL){
		printf("%d Jogo inexistente.\n", line);
		return;
	}

	
	if(score1==score2){
		if(game->score1 != game->score2){ 
			if(game->score1 > game->score2){ 
				prevWinner = game->team1;
			}else{							
				prevWinner = game->team2; 
			}
			team2 = searchT(t, prevWinner, SIZETEAM); 
			team2->cont--;							  	
		}
	
	}else{
		if(game->score1 == game->score2){
			if(score1 > score2){ 
				newWinner = game->team1;
			}else{				
				newWinner = game->team2;
			}
			team1 = searchT(t, newWinner, SIZETEAM); 
			team1->cont++;							
		}else{							
			if(game->score1 > game->score2){ 
				prevWinner = game->team1;
			}else{							
				prevWinner = game->team2;
			}
			if(score1 > score2){
				newWinner = game->team1;
			}else{
				newWinner = game->team2;
			}

			if(newWinner!=prevWinner){
				team1 = searchT(t, newWinner, SIZETEAM);
				team1->cont++;
				team2 = searchT(t, prevWinner, SIZETEAM);
				team2->cont--;
			}
		}
	}
	game->score1 = score1;
	game->score2 = score2;
}


int compare(const void * p1, const void* p2){
	return strcmp(* (char * const *) p1, * (char * const *) p2);
} 

/*Comando g - Encontra as equipas que ganharam mais jogos e lista por ordem lexicografica(do nome da equipa).*/
void g(pTeam* t, int numTeams, int line){
	int i;
	int c = 0;
	int j = 0;
	int max = 0;
	char** table;

	if(numTeams == 0){
		return;
	}
	for (i = 0; i < SIZETEAM; i++){
		pTeam temp = t[i];
		while(temp != NULL){
			if(max == temp->team->cont){
				c++;
			}
			if(max < temp->team->cont){
				max = temp->team->cont;
				c = 1;
			}
			temp = temp->next;
		}
	}	

	table = can_fail_malloc(sizeof(char*)*c);
	for (i = 0; i < SIZETEAM; i++){
		pTeam temp = t[i];
		while(temp != NULL){
			if(max == temp->team->cont){
				table[j] = temp->team->name;
				j++;
			}
			temp = temp->next;
		}
	}	

	qsort(table, c, sizeof(char*), compare);
	printf("%d Melhores %d\n", line, max);
	for (i = 0; i < c; i++){
		printf("%d * %s\n",line, table[i]);
	}
	free(table);
}