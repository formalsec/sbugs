#ifndef _MAIN_
#define _MAIN_
#include "game.h"
#include "team.h"

#define INITIAL_HASH_SIZE 11 /*Initial hashtable size*/
#define SIZE "1023"          /*Used to limit scanf's width*/
#define DecrementWins(team) (team->wins--)
#define IncrementWins(team) (team->wins++)

/*Command a*/
void AddGame(GameHash_ptr *game_hash, Game_link *game_list, TeamHash_ptr team_hash, int NL);
/*Command A*/
void AddTeam(TeamHash_ptr *team_hash, int NL);
/*Command l*/
void GameList(Game_link game_list, int NL);
/*Command p*/
void SearchGame(GameHash_ptr game_hash, int NL);
/*Command P*/
void SearchTeam(TeamHash_ptr team_hash, int NL);
/*Command r*/
void DeleteGame(GameHash_ptr game_hash, Game_link *game_list, int NL);
/*Command s*/
void ChangeScore(GameHash_ptr game_hash, int NL);
/*Command g*/
void SearchBestTeams(TeamHash_ptr team_hash, int NL);
void FreeAll(GameHash_ptr game_hash, Game_link game_list, TeamHash_ptr team_hash);

#endif