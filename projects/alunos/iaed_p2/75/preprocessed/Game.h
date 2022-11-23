#ifndef GAME_H
#define GAME_H

#include "Team.h"

/* =========================== STRUCTURE FOR GAME ============================== */

typedef struct game {
    char* pname;
    Team* pteam1;
    Team* pteam2;
    int score1, score2;
}Game;

/* =========================== PROTOTYPES FOR GAME ============================== */

Game* newGame(char* name, Team* team1, Team* team2, int score1, int score2);
void delGame(Game* game);
Team* who_won(Game* ptr_ng);

#endif