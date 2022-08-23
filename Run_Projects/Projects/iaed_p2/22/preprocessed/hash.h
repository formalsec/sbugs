#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUT 1023
#define HASHSIZE 43100


struct team{
  struct team* nextHash;
  struct team* previousHash;
  char* name;
  int wins;
};

struct game{
  struct game* nextGeral; /*Aponta para o proximo jogo inserido no sistema*/
  struct game* previousGeral; /*Aponta para o jogo inserido exatamente antes*/
  struct game* nextHash;
  struct game* previousHash;
  struct team* team1;
  struct team* team2;
  char* name;
  int score1;
  int score2;
};

unsigned long hash(char *s);
void init_hash_games(struct game** hash_games);
void init_hash_teams(struct team** hash_teams);
struct game* createGame(char* name, struct team* team1, struct team* team2, int score1, int score2);
struct team* createTeam(char* name);
void freeGame(struct game* game);
void freeTeam(struct team* team);
void addTeam(char* name,struct team** hash_teams, struct team* last);
void addGame(char* name, char* team1, char* team2, int s1, int s2,struct game** hash_games,struct team** hash_teams,struct game** lastGame,struct game** firstGame);
int gameExists(char* name,struct game** hash_games);
int teamExists(char* name,struct team** hash_teams);
void changeScore(struct game* g, int s1,int s2);
int findMaxWins(struct team** hash_teams);
void sortAlphabetic(char** array, int max);
void removeGame(struct game* g,struct game** hash_games,struct game** lastGame,struct game** firstGame);
void deleteHashTeams(struct team** hash_teams);
struct team* getTeam(char* name,struct team** hash_teams);

#endif
