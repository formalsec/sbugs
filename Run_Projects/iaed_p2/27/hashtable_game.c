#include <stdio.h>
#include "hashtable_team.h"
#include "hashtable_game.h"


#define TABLE_SIZE 20000

/* creates a hashtable to store the games */

ht_game *ht_create_hgame(void){

    int i = 0;
    /* allocate table */
    ht_game *hashtable = malloc(sizeof(ht_game) * 1);

    /* allocate table entries */
    hashtable->entries = malloc(sizeof(entry_game) * TABLE_SIZE);

    /* set each entry to null */
    for(; i < TABLE_SIZE; ++i){
        hashtable->entries[i] = NULL;
    }

    return hashtable;
}


/* allocs the hashtable entry */

entry_game *ht_pair_game(GAME *game){

    /* allocate the entry */
    entry_game *entry = malloc(sizeof(entry_game));

    /* assign the team */
    entry->game = game;

    /* next starts out null */
    entry->next = NULL;

    return entry;
}

/* hash function that returns the key to a slot in the hashtable */

unsigned int hash_game(char *game){
    unsigned int value = 0;
    unsigned int i = 0;
    unsigned int len = strlen(game);


    for(; i < len; ++i) {
        value = value * 37 + game[i];
    }

    /* make sure value < TABLE_SIZE */
    value = value % TABLE_SIZE;

    return value;
}

/* function that inserts a game in the hashtable */

void ht_set_game(int line, ht_game *hashtable, GAME* game){
    entry_game *prev = NULL;
    unsigned int slot = hash_game(game->name);

    /* try to look up an entry set */
    entry_game *entry = hashtable->entries[slot];

    /* no entry means slot empty, insert if it is */
    if (entry == NULL){
        hashtable->entries[slot] = ht_pair_game(game);
        return;
    }

    /* walk through each entry until either the end is reached or a matching key is found */
    while(entry != NULL){
        /* check key */
        if (strcmp(entry->game->name, game->name) == 0) {
            /* match found, replace value */
            printf("%d Jogo existente.\n", line);
            free(game->name);
            free(game);
            return;
        }

        /* go to next */
        prev = entry;
        entry = prev->next;
    }

    /* if reached the end without a match, add new */
    prev->next = ht_pair_game(game);
}

/* function removes a game from the hashtable */

GAME* ht_remove_game(ht_game *hashtable, ht_team *hashtable_team, GAME* game, GAME* linkedlist){
    entry_game *prev = NULL;
    TEAM *aux = NULL;
    unsigned int slot = hash_game(game->name);
    int idx = 0;

    /* try to look up an entry set */
    entry_game *entry = hashtable->entries[slot];

    if(entry == NULL){
        return NULL;
    }

    /* walk through each entry until either the end is reached or a matching key is found */
    while(entry != NULL){
        /* check key */
        if (strcmp(entry->game->name, game->name) == 0) {
            if(game->score[0] > game->score[1]){
                aux = ht_get_team(hashtable_team, game->team1->name);
                aux->gameswon--;
            }
            else if (game->score[0] < game->score[1]){
                aux = ht_get_team(hashtable_team, game->team2->name);
                aux->gameswon--;
            }
            if(entry->next == NULL && idx == 0){
                hashtable->entries[slot] = NULL;

            }

            if(entry->next != NULL && idx == 0){
                hashtable->entries[slot] = entry->next;
            }

            if(entry->next == NULL && idx != 0){
                prev->next = NULL;
            }

            if(entry->next != NULL && idx != 0){
                prev->next = entry->next;
            }
            linkedlist = removeGameFromLinkedList(linkedlist, game);

            return linkedlist;
        }

        /* go to next */
        prev = entry;
        entry = prev->next;

        ++idx;
    }
    return linkedlist;
}

/* function returns a game from the hashtable given the game's name */

GAME *ht_get_game(ht_game *hashtable, char *game){
    unsigned int slot = hash_game(game);

    /* tries to find a valid slot */
    entry_game *entry = hashtable->entries[slot];

    /* no slot means no entry */
    if (entry == NULL){
        return NULL;
    }

    /* walk through each entry in the slot if there is more than one */
    while (entry!= NULL){
        /* return game if found */
        if (strcmp(entry->game->name, game) == 0){
            return entry->game;
        }

        /* walk to next key if available */
        entry = entry->next;
    }

    /* reaching here means there was one or more entries but no matches */
    return NULL;
}

/* function frees all allocated memory inside the hashtable */

void ht_dump_game(ht_game *hashtable){
    entry_game *temp = NULL;
    entry_game *entry = NULL;
    int i;
    for (i = 0; i < TABLE_SIZE; i++) {
        if(hashtable->entries[i] != NULL) {
            entry = hashtable->entries[i];

            while (entry != NULL) {
                temp = entry->next;
                free(entry->game->name);
                free(entry->game);
                free(entry);
                entry = temp;
            }
          /*  temp = entry;
            free(temp); */
        }
    }
}

/* function that is related to command 'a' and is the main function to check if the given game should be added to the hashtable */

GAME* addGame(int line, ht_game *hashtable, ht_team *hashtable_team, GAME* linkedlist) {
    int score1 = 0, score2 = 0;
    char *team1 = NULL;
    char *team2 = NULL;
    char name[1024] = "\0";
    GAME* game = NULL;
    GAME* gameaux = NULL;
    TEAM* team = NULL;
    TEAM* teamaux = NULL;
    team1 = malloc(1024);
    team2 = malloc(1024);
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &score1, &score2);
    game = (GAME*)calloc(1, sizeof(GAME));
    gameaux = ht_get_game(hashtable, name);
    if(gameaux != NULL){
        printf("%d Jogo existente.\n", line);
        free(game);
        free(team1);
        free(team2);
        return linkedlist;
    }
    game->name = malloc(strlen(name)+1);
    strcpy(game->name, name);
    team = ht_get_team(hashtable_team, team1);
    if(team != NULL) {
        game->team1 = team;
    }
    else{
        printf("%d Equipa inexistente.\n", line);
        free(game->name);
        free(game);
        free(team1);
        free(team2);
        return linkedlist;
    }
    teamaux = ht_get_team(hashtable_team, team2);
    if(teamaux != NULL) {
        game->team2 = teamaux;
    }
    else{
        printf("%d Equipa inexistente.\n", line);
        free(game->name);
        free(game);
        free(team1);
        free(team2);
        return linkedlist;
    }
    game->score[0] = score1;
    game->score[1] = score2;

    if(game->score[0] > game->score[1]){
        TEAM* pteam = ht_get_team(hashtable_team, game->team1->name);
        pteam->gameswon++;
    }
    else if (game->score[1] > game->score[0]){
        TEAM* pteam = ht_get_team(hashtable_team, game->team2->name);
        pteam->gameswon++;
    }
    ht_set_game(line,hashtable, game);
    linkedlist = addGameToLinkedList(linkedlist, game);
    free(team1);
    free(team2);

    return linkedlist;
}

/* adds a game to the linked list */

GAME* addGameToLinkedList(GAME* linkedlist, GAME* game){
    if(linkedlist == NULL){
        linkedlist = game;
    }
    else{
        GAME* paux = linkedlist;
        while(paux->pnext!= NULL){
            paux = paux->pnext;
        }
        paux->pnext = game;
    }
    return linkedlist;
}


/* removes a game from the linked list */

GAME* removeGameFromLinkedList(GAME* linkedlist, GAME* game){

    int idx = 0;
    GAME *prev = NULL;
    GAME *paux = linkedlist;

    /* walk through each entry until either the end is reached or a matching key is found */
    while(paux != NULL){
        /* check key */
        if (strcmp(paux->name, game->name) == 0) {
            if(paux->pnext == NULL && idx == 0){
                linkedlist = NULL;

            }

            if(paux->pnext != NULL && idx == 0){
                linkedlist = paux->pnext;
            }

            if(paux->pnext == NULL && idx != 0){
                prev->pnext = NULL;
            }

            if(paux->pnext != NULL && idx != 0){
                prev->pnext = paux->pnext;
            }
            free(paux);
            return linkedlist;
        }
        /* go to next */
        prev = paux;
        paux = prev->pnext;

        ++idx;
    }
    return linkedlist;
}