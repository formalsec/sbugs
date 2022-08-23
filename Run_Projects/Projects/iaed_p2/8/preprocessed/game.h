#ifndef GAME_H_
#define GAME_H_

#include "team.h"

/* Max size of a game name*/
#define GAME_MAX_NAME 1023

typedef struct score {
    int t1;
    int t2;
} Score;


typedef struct game {
    const char *name;
    const Team * t1;
    const Team * t2;
    Score      score;
} Game;


Game * new_game(char *name, Team *t1, Team *t2, Score score);
void   game_free(Game *g);

char * game_get_name(Game * g);
Team * game_get_team1(Game * g);
Team * game_get_team2(Game * g);
int    game_get_score1(Game * g);
int    game_get_score2(Game * g);

Team * game_get_team  (Game * g, char * team_name);
Team * game_get_winner(Game * g);

void game_set_score(Game * g, int s1, int s2);

char * game_to_string(Game *g, char *buf);
void   game_print(Game *g);

#endif