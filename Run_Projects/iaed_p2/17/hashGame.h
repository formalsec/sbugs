#ifndef _HASHGAME_H
#define _HASHGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itemGame.h"

/* Number of linked lists in an hash table. */
#define MH 1009
/* Constant for hash function. */
#define CH 127

typedef struct nodeGame* LinkGame;

typedef struct nodeGame{
	ItemGame item;
	LinkGame next;
}NodeGame;

LinkGame push_game(LinkGame head, ItemGame item);
LinkGame remove_elem_game(LinkGame head, char* name);
ItemGame search_list_game(LinkGame head, char* name);
void destroy_list_game(LinkGame head);

LinkGame* HASHinit_game();
int hash_game(char *v);
LinkGame new_node_game(ItemGame item, LinkGame head);
void insert_game(LinkGame* heads, ItemGame item);
void delete_game(LinkGame* heads, char* name);
ItemGame search_game(LinkGame* heads, char* name);
void destroy_hash_game(LinkGame* heads);

#endif
