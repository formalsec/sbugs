#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "team.h"

typedef struct game{
    char * name;
    struct team * team[2];
    int score[2];
    struct game * next;
}game;



typedef struct ent{
    game ** entries;
}ent;


game * dummy;

/* Lista ordenada por entrada */
game * ordGameList;
int ordListsize;


ent * htGame_create();
void printGames(int num);
game * htGame_search(ent * ht_g, char * name);
game * alloc(char * name, team * team1, team * team2, int score[2]);
void ordListadd(game g);
void ordListremove(game g);
void htGame_change(game * g, int score1, int score2);
int htGame_insert(ent * ht_g, tent * ht_t, char * name, char * team1, char * team2, int score[2]);
void htGame_delete(ent * ht_g, char * name);