#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"



/* Creates a new game */
Game * newGame(char * strName, char * strTeam1, char * strTeam2, 
               int score1, int score2, int * index) {
    Game *new = NULL;
    char *name, *team1, *team2;
    int lengthName = strlen(strName) + 1;
    int lengthTeam1 = strlen(strTeam1) + 1;
    int lengthTeam2 = strlen(strTeam2) + 1;
    
    new = malloc(sizeof(Game));
    name = malloc(sizeof(char) * lengthName);
    strcpy(name, strName);
    team1 = malloc(sizeof(char) * lengthTeam1);
    strcpy(team1, strTeam1);
    team2 = malloc(sizeof(char) * lengthTeam2);
    strcpy(team2, strTeam2);

    new->name = name;
    new->team1 = team1;
    new->team2 = team2;
    new->score1 = score1;
    new->score2 = score2;
    new->index = *index;

    return new;
}


/* Prints a game. */
void printGame(Game * game) {
    printf("%s %s %s %d %d\n", game->name, game->team1, 
                               game->team2, game->score1, 
                               game->score2);
}


/* Frees all memory attached to a game. */
void destroyGame(Game * game) {
    free(game->name);
    free(game->team1);
    free(game->team2);
    free(game);
}
