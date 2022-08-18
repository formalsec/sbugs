#ifndef TEAM_HASHTABLE_H
#define TEAM_HASHTABLE_H

#include "Structs.h"

typedef struct hash_node_team {
	Team *team; 
	struct hash_node_team *next;
} Hash_Node_Team;

typedef struct hash_table_team {
	Hash_Node_Team ** table;
	int capacity;
} Hash_Table_Team;

int hash_key(char *name, int capacity);
Hash_Table_Team* mk_Team_Hash_Table();
void addToTeamHashList(char *teamName, Hash_Table_Team *t, int index);
void freeTeamHash(Hash_Table_Team *t);

#endif

