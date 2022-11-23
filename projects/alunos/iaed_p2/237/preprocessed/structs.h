#ifndef STRUCTS_H
#define STRUCTS_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAX_CHAR 1023
#define TABLE_SIZE 5000

/* team struct with a pointer to the name and number of victories */
typedef struct team {
  char * nome;
  int wins;
} Team;

/* game struct with a pointer to the game name, and both teams, and the game score */
typedef struct game {
  char * gameName;
  Team * t1;
  Team * t2;
  int score1, score2;
} Game;

/* hashtable game entrie, having pointers to game and team, so there's no need to create two entry struct for different hashtables */
typedef struct entry {
  Team * t;
  Game * game;
  int key;
  struct entry *next;
} entry;


/* hashtable struct with the entries */
typedef struct ht {
  entry **entries;
} ht;

/* ordered games linked list with pointers to the games */
typedef struct orderedGames {
  Game * game;
  struct orderedGames *next;
} orderedGames;

/* ordered teams linked list with pointers to the teams */
typedef struct orderedTeams {
  Team * team;
  struct orderedTeams *next;
} orderedTeams;

#endif
