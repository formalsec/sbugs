#ifndef _HASHTEAM_
#define _HASHTEAM_
/* Constants defined */
#define HASHTABLE_SIZE 1087
#define MAX_LENGTH 1024
#define G 31

/* Struct defined for a team */
struct nodeTeam{
    char *teamName;
    int teamWins;
    struct nodeTeam *next;
};

typedef struct nodeTeam *linkTeam;

/* All functions defined in hashTeam.c */
void NewNodeTeam(linkTeam *head, char *teamName);

linkTeam *CreateTableTeams();

linkTeam getTeam(linkTeam list, char *teamName);

int teamInTable(linkTeam list, char *teamName);

void FreeNodeTeam(linkTeam toDelete);

void DestroyHashTeam(linkTeam *HashTableTeam);

int getMaxWins(linkTeam *HashTableTeam);

#endif