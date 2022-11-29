#ifndef JOGOS_H
#define JOGOS_H

/*Constantes do programa*/
#define TRUE 1
#define FALSE 0
#define MAX_LEN 1024
#define HASH_NUM_GAMES 5501 /*Tamanho da hash onde os jogos estao guardados*/
#define HASH_NUM_TEAMS 2131 /*Tamanho da hash onde as equipas estao guardados*/

/*Struct da Equipa*/
typedef struct Team {
    char *name;
    struct Team *next;
    int gamesWon;
} *teamLink;

/*Funcoes para implementar listas com a Struct Team*/
teamLink NEWteam(char* buffer);
void insertTeam(teamLink *head, char* buffer);
teamLink searchTeam(teamLink head, char* name);
void FREEteam(teamLink team);

/*Struct do Jogo*/
typedef struct {
    char *name;
    teamLink team1;
    teamLink team2;
    int* score;

} Game;

/*Funcao que cria e aloca uma Struct Game e retorna o seu ponteiro */
Game* createGame(char* name, teamLink team1, teamLink team2, int score1, int score2);

/*Struct do Node do Jogo, usada para poder implementar as listas*/
typedef struct GameNode{
    int deleted;
    Game *game;
    struct GameNode *next;
} *gameLink;

/*Funcoes para implementar listas com a Struct GameNode*/
gameLink NEWgame( Game* game);
void insertGameBegin(gameLink *head, Game* game);
void insertGameEnd(gameLink *head, Game* game, gameLink *tailGame);
gameLink searchGame(gameLink head, char* name);
void deleteGame(gameLink *head, char* name);
void FREEgameNode(gameLink gameLink);
void freeGameList(gameLink head);


/*Funcoes dos comandos*/
void newTeam(int *nrCommand, teamLink *hashTeamTable);
void newGame(int *nrCommand, teamLink *hashTeamTable, gameLink *headGame, gameLink *hashGameTable, gameLink *tailGame);
void listGames(int *nrCommand, gameLink *headGame);
void searchGameByName(int *nrCommand, gameLink* hashGameTable);
void searchTeamByName(int *nrCommand, teamLink* hashTeamTable);
void deleteGameByName(int* nrCommand, gameLink *hashGameTable, gameLink *headGame);
void changeScore(int *nrCommand, gameLink* hashGameTable);
void bestTeams(int *nrCommand, teamLink *hashTeamTable);

/*Funcoes auxiliares para os comandos*/
int compare(const void *a, const void *b);

/*Funcoes do main*/
int scanCommand(int *nrCommand, teamLink *hashTeamTable, gameLink *headGame, gameLink *hashGameTable, gameLink *tailGame);

/*Funcoes para implementar hash tables*/
int hashString(char* text, int M);

    /*Hash para os jogos*/
gameLink* InitGameHash(int size);
gameLink searchGameHash(gameLink* table, char* name);
void insertGameHash(gameLink* table, Game* game);
void deleteGameHash(gameLink* table, char* name);
void freeGameHash(gameLink* table);

    /*Hash para as equipas*/
teamLink* InitTeamHash(int size);
teamLink searchTeamHash(teamLink* table, char* name);
void insertTeamHash(teamLink* table, char* name);
void freeTeamHash(teamLink* table);

#endif