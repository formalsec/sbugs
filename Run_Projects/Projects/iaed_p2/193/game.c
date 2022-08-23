#include "game.h"
#include "messages.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Allocs the memory to the game structure.
 * Allocs the memory for the name and copies it.
 * Allocs the memory to the Teams array.
 * Allocs the memory to the scores.
 * Requires: char array with the name, Teams pointers array and int array with the scores.
 * Return: the pointer to the game.
 */
Game *createGame(char *name, Team **teams, int *scores) {
    Game *game = (Game *) malloc(sizeof(Game));
    int length = strlen(name);
    game->name = (char *) malloc(sizeof(char) * (length + 1));
    strcpy(game->name, name);
    game->teams = (Team **) malloc(sizeof(Team *) * 2);
    game->teams[0] = teams[0];
    game->teams[1] = teams[1];
    game->scores = (int *) malloc(sizeof(int) * 2);
    game->scores[0] = scores[0];
    game->scores[1] = scores[1];
    return game;
}

/*
 * Frees the game and all its attributes.
 * The game pointer cannot be NULL.
 * Requires: void pointer to the game.
 */
void deleteGame(void *game) {
    if (game != NULL) {
        free(((Game *) game)->name);
        free(((Game *) game)->teams);
        free(((Game *) game)->scores);
        free(game);
    }
}

/*
 * Function used to compare the game with the given name using the string compare function.
 * The name and the game cannot be NULL.
 * Requires: char array with the name and void pointer to the game.
 * Returns: 1 if the game's name is equals with the name 0 otherwise.
 */
int compareGameFunction(char *name, void *game) {
    if (game != NULL && name != NULL) {
        if (strcmp(name, ((Team *) game)->name) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
 * Function used to print all the game's information.
 * The game pointer cannot be NULL.
 * Requires: void pointer to the game and int pointer to the command counter.
 */
void printGame(void *game, int *cmdCounter) {
    if (game != NULL) {
        printf(GAME_INFO_MESSAGES, *cmdCounter, ((Game *) game)->name, ((Game *) game)->teams[0]->name,
               ((Game *) game)->teams[1]->name, ((Game *) game)->scores[0], ((Game *) game)->scores[1]);
    }
}
