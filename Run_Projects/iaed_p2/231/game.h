#ifndef GAME_H_
#define GAME_H_

#define MG 199 
#include "team.h"


typedef struct gameNode{
    char *name;
    TeamNode *team1,*team2;
    int score1,score2,id;
    struct gameNode *next;
}GameNode;

/*hash function from the subject's slides*/
int hashGame(char *name);

/*adds a team to a certain linked list and puts it in the beggining of the list*/
GameNode* addGame(GameNode *head,char *n,TeamNode *t1,TeamNode *t2,int s1,int s2,int gameNumber);

GameNode* searchGame(GameNode *head,char *n);

GameNode* deleteGame(GameNode *head,GameNode *game);

void changeScore(GameNode *game,int s1, int s2);
#endif