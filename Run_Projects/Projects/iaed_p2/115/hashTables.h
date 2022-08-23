#ifndef _HASH_
#define _HASH_

#include "newTeam.h"
#include "newGame.h"

/* Struct lista caracterizada por uma uma cabeca e uma cauda que sao ponteiros para nos de jogos
(Inicializada em gamesList.c mas definida aqui por ser necesseraria para funcoes deste ficheiro) */
typedef struct list {
    gameNodeP head, last;
} List;

/* Ponteiro para uma lista de ponteiros para nos de jogos */
typedef struct list* gameListP;

/*------------------------------------------------------------------------------------
Funcoes que criam uma nova Hash Tables com o dobro do tamanho da anterior quando o
load factor iguala 1. Inicializam a nova Hash e copiam para ela os elementos da antiga
-------------------------------------------------------------------------------------*/
TeamsHash* expandT (TeamsHash *HashT);

GamesHash* expandG (GamesHash *HashG);

void copy_elementsT (TeamsHash *new_Hash, TeamsHash *old_Hash);

void copy_elementsG (GamesHash *new_Hash, GamesHash *old_Hash);

/*------------------------------------------------------------------------------------
Funcoes que inicializam Hash Tables de tamanho M de ponteiros para equipas e jogos
-------------------------------------------------------------------------------------*/
TeamsHash* initTeamsHash(int M);

GamesHash* initGamesHash(int M);

/*-----------------------------------------------------------------------------------
Funcoes que verificam se uma equipa ou um jogo ja esta na Hash Table
------------------------------------------------------------------------------------*/
int verifyExistentTeam (TeamsHash *HashT, char * name);

int verifyExistentGame (GamesHash *HashG, char * name);

/*----------------------------------------------------------------------------------
Funcoes que adicionam uma equipa ou um jogo a Hash Table e respetivas auxiliares
------------------------------------------------------------------------------------*/
TeamsHash* addTeam(TeamsHash *HashT, int i, TeamNode * eq);

GamesHash* addGameHash (GamesHash *HashG, int i, gameNodeP game);

teamNodeP insertBeginT(teamNodeP head, teamNodeP eq);

gameNodeP insertBeginG (gameNodeP head, gameNodeP game);

/*----------------------------------------------------------------------------------
Funcoes que devolvem uma equipa ou um jogo guardados na Hash Table
------------------------------------------------------------------------------------*/
Team* searchTeam (TeamsHash *HashT, char *name);

Game* searchGame (GamesHash *HashG, char* name);

Team* searchListT (teamNodeP head, char* name);

Game* searchListG (gameNodeP head, char* name);

/*----------------------------------------------------------------------------------
Funcoes que apagam jogos da Hash Table e da lista
------------------------------------------------------------------------------------*/
void deleteGame(gameListP gamesList, GamesHash *HashG, char *name);

void deleteGameList(gameListP gameList, char* name);

/*----------------------------------------------------------------------------------
Funcao que altera o score de um jogo e ajusta as vitorias das equipas participantes
------------------------------------------------------------------------------------*/
void changeScores(GamesHash *HashG, char* name, int s1, int s2);

/*------------------------------------------------------------------------------------
Funcao que procura as equipas com mais vitorias em cada entrada da Hash Table,
determina as vencedoras e ordena-as por ordem lexicografica
--------------------------------------------------------------------------------------*/
Team** winners(TeamsHash *HashT, Team **winnersTable, int max, int cont);

Team** searchWinners(teamNodeP *headsT, int *maxP, int i, int *lenP, Team **winnersTable, int* max);

Team** addWinnerTable(Team* x, int* lenP, Team **winnersTable, int* max);

/* Bubble sort */
Team** sortWinners(Team **winnersTable, int* len);

/*-------------------------------------------------------------------------------
Funcoes que libertam a memoria
---------------------------------------------------------------------------------*/
void destroyTeamsHash(TeamsHash *HashT);

void destroyGamesHash(GamesHash *HashG);

#endif