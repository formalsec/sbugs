#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define HASH_SIZE 100000

typedef struct team{
    char * name;
    int wins;
    struct team * next;
}team;

typedef struct tent{
    team ** entries;
}tent;

int teamsSize;
team ** bestTeams;

int hash(char * sub);
void swap(int i, int j);
int part(int low, int high);
void quicksortWins(int low, int high);
void removebestTeam(team * t);
void addbestTeam(team * t);
team * alloct(char * name);
tent * htTeam_create();
team * htTeam_search(tent * ht_t, char * name);
int htTeam_insert(tent * ht_t, char * name);
team * htTeam_search(tent * ht_t, char * name);
void presentOrdered(int debug);