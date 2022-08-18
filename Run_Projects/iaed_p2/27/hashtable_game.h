#include <string.h>
#include <stdlib.h>
#define MAX_INPUT 3080

typedef struct game{
    char *name;
    struct team* team1;
    struct team* team2;
    int score[2];
    struct game* pnext;
} GAME;

typedef struct nodegame{
    GAME* game;
    struct nodegame *next;
} entry_game;

typedef struct {
    entry_game **entries;
} ht_game;



ht_game *ht_create_hgame(void);
entry_game *ht_pair_game(GAME *game);
void ht_set_game(int line, ht_game *hashtable, GAME* game);
GAME *ht_get_game(ht_game *hashtable, char *game);
unsigned int hash_game(char *game);
GAME* ht_remove_game(ht_game *hashtable, ht_team *hashtable_team, GAME* game, GAME* linkedlist);
GAME* addGame(int line, ht_game *hashtable, ht_team *hashtable_team, GAME* linkedlist);
GAME* addGameToLinkedList(GAME* linkedlist, GAME* game);
GAME* removeGameFromLinkedList(GAME* linkedlist, GAME* game);
void ht_dump_game(ht_game *hashtable);

