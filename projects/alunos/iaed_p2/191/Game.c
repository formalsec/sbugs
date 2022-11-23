#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "Game.h"

/* isDeleted property starts as false */
#define INIT_DELETED 0

/* Creates a new game.
*  @params: id - unique game identifier;
*           score - array of 2 representing the score of the game;
*           team1 - home team;
*           team2 - away team;
*           name - name of the game.
*  @returns: pointer to a new game.
*/
Game *newGame(unsigned int id, unsigned int score[], Team *team1,
                Team *team2, char *name)
{
    Game *new;
    char *n;

    /* Allocates memory and sets the team's properties */
    new = (Game*) can_fail_malloc(sizeof(Game));
    new->id = id;
    new->score[0] = score[0];
    new->score[1] = score[1];
    new->team1 = team1;
    new->team2 = team2;
    new->isDeleted = INIT_DELETED;

    n = (char*) can_fail_malloc(sizeof(char)*(strlen(name)+1));
    strcpy(n, name);
    new->name = n;

    /* Updates the respective teams winning tally */
    if(score[0] > score[1])
    {
        new->team1->nWon++;
    }
    else if(score[0] < score[1])
    {
        new->team2->nWon++;
    }

    return new;
}

/* Frees the allocated memory of a game.
*  @params: game - pointer to a game.
*  @returns: void.
*/
void freeGame(Game *game)
{
    free(game->name);
    free(game);
}