#ifndef GAME_H
#define GAME_H

/* Library. */
#include "TEAM.h"


/* The maximum number of caracters of the name of the game and team. */
#define MAXCAR 1023

/* Structure of a game. */
typedef struct game{
    char * name;
    team * A;
    team * B;
    int scoreA;
    int scoreB;
    struct game *next;
    int NL;   /* Reperesents the number of command line where the game was inserted. */
}Game;


/* Auxiliar functions of games. */

Game ** init_game(Game ** game);

Game * create_game(char * name_game, team * teamA, team * teamB, int scoreA, int scoreB);

Game * push_game(char * name_game, team * A, team * B, int sA, int sB, Game * last); 

Game * pop_game(Game * head);

Game * destroy_game(Game * game_hash);

Game ** destroy_full_game(Game ** game_hash);

Game * add_order_game(Game * order_team, char * name, team * A, team *B,int sA, int sB, int NL);

#endif