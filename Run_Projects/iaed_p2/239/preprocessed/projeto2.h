#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_STRING 1023
#define hash_size 2000

typedef struct team
{
  char name[MAX_STRING];
  int score;
  struct team* link;
}TEAM;

typedef struct game
{
  char name[MAX_STRING];
  TEAM* team1;
  TEAM* team2;
  int score1;
  int score2;
  struct game* link;
}GAME;

void start_hashT(TEAM* hashT);
void start_hashG(GAME* hashG);
int hash_function(char string[]);
void hash_initializer(TEAM* hashT[], GAME* hashG[]);
void a(GAME* hashG[] ,TEAM* hashT[], int row);
void A(TEAM* hashT[], int row);
void p(GAME* hashG[], int row);
void r(GAME* hashG[], int row);
void s(GAME* hashG[], int row);
void P(TEAM* hashT[], int row);
void x(TEAM* hashT[], GAME* hashG[]);
