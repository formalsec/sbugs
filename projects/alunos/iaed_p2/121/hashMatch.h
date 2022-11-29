#ifndef _HASHMATCH_
#define _HASHMATCH_
/* Contants defined */
#define HASHTABLE_SIZE 1087
#define MAX_LENGTH 1024
#define G 31

/* Struct defined for the matches */
struct nodeMatch {
    char *matchName;
    char *team1;
    char *team2;
    unsigned int score1;
    unsigned int score2;
    struct nodeMatch *next;
};

typedef struct nodeMatch *linkMatch;

/* All functions defined in hashMatch.c */
int CharAt(char *text, int pos);

int hashFunction(char *text);

void NewNodeMatch(linkMatch *head, char *matchName, char *team1, 
                  char *team2, unsigned int score1, unsigned int score2);

linkMatch getMatch(linkMatch list, char *matchName);

void FreeNodeMatch(linkMatch match);

linkMatch *CreateTableMatches();

void DestroyHashMatch(linkMatch *HashTableMatch);

int whoWonTheGame(int score1, int score2);

#endif