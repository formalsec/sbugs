#ifndef __GAMES__
#define __GAMES__
#include "teams.h"

/*struct that models a game*/
typedef struct game{
    char *name;
    char *team1;
    char *team2;
    int score_team1;
    int score_team2;    
} game;

/*node of a list of games*/
typedef struct game_node{
    struct game_node *next, *previous;
    game *gameptr;
} game_node;

/*list of games*/
typedef struct list_games{
    struct game_node *head, *last;
} list_games;

list_games* makeListGames();
list_games** makeHashGames();
void freeAllMemoryGames(list_games*, list_games**);
void addGame(list_games*, list_games**, team_node**, int);
void listGames(list_games*, int);
void searchGame(list_games**, int);
void deleteGame(list_games*, list_games**, team_node**, int);
void changeScore(list_games**, team_node**, int);

#endif
