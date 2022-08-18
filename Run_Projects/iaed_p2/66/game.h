#ifndef _GAME_
#define _GAME_
#include "common_code.h"
#include "team.h"

/*A struct Score contains two int's. One for each team's score*/
typedef struct Score
{
    int score1, score2;
} Score;

/*A struct Game has one array of chars coitaining the name of the game, two Team_ptr's one for each team
in the game and one struct Score with the score of the game*/
typedef struct Game
{
    char *name;
    Team_ptr team1;
    Team_ptr team2;
    Score score;
} * Game_ptr;

/*A struct GameNode has one Game_ptr containing the game and two pointers, one next and one prev (used in lists of games)*/
typedef struct GameNode
{
    Game_ptr game;
    struct GameNode *next;
    struct GameNode *prev;
} * Game_link;

/*A struct GameHash has one Game_ptr * containing the hashtable of games and two int's, one for the size of the hashtable
and one for the number of games inside the hashtable*/
typedef struct GameHash
{
    int N, M;
    Game_ptr *hash_table;
} * GameHash_ptr;

#define score1(game) (game->score.score1)
#define score2(game) (game->score.score2)
#define team1(game) (game->team1->name)
#define team2(game) (game->team2->name)

/*Game functions*/
Game_ptr NewGame(char *name, Team_ptr team1, Team_ptr team2, int score1, int score2);
void PrintGame(Game_ptr game);
Team_ptr game_winner(Game_ptr game);

/*List functions*/
Game_link InsertGameBeginList(Game_link head, Game_ptr Game_ptr);
Game_link RemoveGameList(Game_link head, char *name);
void FreeGameNode(Game_link game_link);

/*Hashtable functions*/
GameHash_ptr GameHashInit(int max);
GameHash_ptr GameHashInsert(GameHash_ptr game_hash, Game_ptr game);
Game_ptr GameHashSearch(GameHash_ptr game_hash, char *name);
GameHash_ptr GameHashExpand(GameHash_ptr game_hash);
void GameHashRemove(GameHash_ptr game_hash, char *name);

/*FREE's*/
void DeleteGameHash(GameHash_ptr game_hash);
void DeleteGameList(Game_link head);

#endif
