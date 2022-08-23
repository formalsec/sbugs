#include <string.h>
#include <stdlib.h>
#include "Game.h"

/* Function allocates space for new game, makes attributions and returns pointer to game */
Game* newGame(char* name, Team* team1, Team* team2, int score1, int score2){
    Game* pnew_game = (Game*)malloc(sizeof(Game)); /* Allocate space for Game structure */

    pnew_game -> pname = (char*)malloc(sizeof(char)*(strlen(name)+1)); /* Allocate space for name of game */
    
    /* Initialize game with all information */
    strcpy(pnew_game->pname, name);
    pnew_game -> pteam1 = team1;
    pnew_game -> pteam2 = team2;
    pnew_game -> score1 = score1;
    pnew_game -> score2 = score2;

    return pnew_game;
}


/* Function deletes game pointed by game */
void delGame(Game* game){
    free(game -> pname);
    free(game);
}


/* Returns pointer to team who won game pointed by ptr_g (NULL if draw) */
Team* who_won(Game* ptr_g){
    if((ptr_g -> score1) > (ptr_g -> score2)) return ptr_g -> pteam1;
    else if((ptr_g -> score1) < (ptr_g -> score2)) return ptr_g -> pteam2;
    else return NULL;   /* Return in case of draw */
}