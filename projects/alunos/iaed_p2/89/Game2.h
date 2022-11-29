#ifndef _G_
#define _G_

#include "Game_b2.h"
#include "Binary_G2.h"

#include "Team2.h"

/* Adds a game to the system. Returns the team winner */
Team addGame(char *name, char *nteam1, char *nteam2, int s1, int s2, 
    BGlink *BGhead, BTlink BThead, int *Elem, int NL);

/* Lists all games in the system */
void listAllGames(BGlink BGhead, int Elem, int NL);

/* Changes the score of the game */
void change_scores(char *name, int s1, int s2, BGlink BGhead, int NL);

/* Searches for a game in the system */
void searchGame( char *name, BGlink BGhead, int NL);

/* Deletes a game from the system */
Team deleteGame(char *name, BGlink *BGhead, int *ELem, int NL);

/* Frees all memory allocations regarding games */
void freeAllGames(BGlink *BGhead);
#endif