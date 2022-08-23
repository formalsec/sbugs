#ifndef _HASHTEAM_H
#define _HASHTEAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "itemTeam.h"

/* Number of linked lists in an hash table. */
#define MH 1009
/* Constant for hash function. */
#define CH 127

typedef struct nodeTeam* LinkTeam;

typedef struct nodeTeam{
	ItemTeam item;
	LinkTeam next;
}NodeTeam;

LinkTeam push_team(LinkTeam head, ItemTeam item);
ItemTeam search_list_team(LinkTeam head, char* name);
void destroy_list_team(LinkTeam head);

LinkTeam* HASHinit_team();
int hash_team(char *v);
LinkTeam new_node_team(ItemTeam item, LinkTeam head);
void delete_node_team(LinkTeam nodeTeam);
void insert_team(LinkTeam* heads, ItemTeam item);
ItemTeam search_team(LinkTeam* heads, char* name);
void destroy_hash_team(LinkTeam* heads);
#endif
