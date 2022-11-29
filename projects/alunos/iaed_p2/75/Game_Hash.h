#ifndef GAME_HASH_H
#define GAME_HASH_H

#include "Game.h"

/* ================================== STRUCTURES ===================================== */

typedef struct node_game{    /* Node for lists of Hash Table */
    Game* pgame;
    struct node_game* next;
}*link_game;

typedef struct db_listnode{  /* Node for double linked list */
    Game* pgame;   
    struct db_listnode* next;
    struct db_listnode* previous;
}*lnk_dblist;


/* ================================= PROTOTYPES ======================================= */

/* Prototypes for Hash Table of Games */

link_game* initGame_Hash(int size);
void insertGame_Hash(int size, link_game* h, Game* g);
void deleteGame_Hash(int size, link_game* h, char* g_name);
Game* searchGame_Hash(int size, link_game* h, char* name);
void destroyGame_Hash(int size, link_game* head);


/* Prototypes auxiliary double linked list that works in tandem with Hash Table */

lnk_dblist initGHash_auxList();
lnk_dblist insrtGHash_auxList(lnk_dblist head, Game* game);
lnk_dblist removGHash_auxList(lnk_dblist head, Game* game);
void destroyAux_List(lnk_dblist head);

#endif