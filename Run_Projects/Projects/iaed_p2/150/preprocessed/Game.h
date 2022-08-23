#ifndef _GAME_
#define _GAME_


/******** structure ********/

typedef struct Game {
    char *name;
    char *team1, *team2;
    int score1, score2, index;
} Game;


/***************** prototypes ****************/

/* Prints a game */
void printGame(Game * game);

/* Frees all memory attached to a game. */
void destroyGame(Game * game);

/* Creates a new game */
Game * newGame(char * strName, char * nameTeam1, 
               char * nameTeam2, int score1, 
               int score2, int * index);


#endif
