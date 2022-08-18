#ifndef HASH_H
#define HASH_H
#include "structs.h"

/* hash(): function that generates the hash key by the ascii code of the team/game name */
unsigned int hash(const char * key);

/* hash_init(): initiate the hashtables entries as NULL */
ht * hash_init();

/* ht_pair_team*(): find the entrie in the hashtable via the hash key given in the function and pairs the team struct in the hashtable */
entry * ht_pair_team(unsigned int key, char * buffer);

/* ht_pair_game(): find the entrie in the hashtable via the hash key given in the function and pairs the game struct in the hashtable*/
entry * ht_pair_game(unsigned int key, char * buffer, Team * t1, Team * t2, int score1, int score2, int * maxWins);

/* addTeam(): receive the hashtable that the team will be paired into and checks the requirements */
Team * addTeam(ht * hashtable, int cmd_count);

/* teamSearch: search a specific team via the name in the team hashtable */
Team * teamSearch(ht * hashtable, char * name);

/* getTeam(): search a team in the hashtable and prints the team name and number of wins */
void getTeam(ht * hashtable, int cmd_count);

/* searchGame(): search a game in a specific entry and returns 1 if found, returns 0 otherwise */
int searchGame(entry * entrie, char * buffer);

/* getGame(): search a specific game in the game hashtable and returns all the game info (if the game exists) */
void getGame(ht * game_ht, int cmd_count);

/* addGame(): add a game in the hashtable if it goes through the requirements and puts the game in the ordered games list
   Returns a game to be pushed in the ordered games list                                                               */
Game * addGame(ht * hashtable, ht * game_ht, int cmd_count, int * game_count, int * maxWins);

/* changeScore(): changes the score of a specific game if the game exists */
void changeScore(ht * game_ht, int cmd_count);

/* destroyTeamEntry(): free all the memory allocated in the Team hashtable */
entry * destroyTeamEntry(entry * head);

/* destroyGameEntry(): free all the memory allocated in the Game hashtable */
entry * destroyGameEntry(entry * head);

/* destroyTeam(): free all the memory allocated by a team struct */
void destroyTeam(ht * hashtable);

/* destroyGame(): free all the memory allocated by a game struct */
void destroyGame(ht * hashtable);

#endif
