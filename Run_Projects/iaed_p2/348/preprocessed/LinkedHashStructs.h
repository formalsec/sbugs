#ifndef LINKEDHASHSTRUCTS_H
#define LINKEDHASHSTRUCTS_H

typedef struct list_node_match {
	Match *match; 
	struct list_node_match *next, *prev;
} List_Node_Match;

typedef struct linkedlist_match {
	List_Node_Match *head, *tail;
} LinkedList_Match;

typedef struct hash_node_match {
	Match *match; 
	struct hash_node_match *next, *prev;
	List_Node_Match *lNM;
} Hash_Node_Match;

typedef struct hash_table_match {
	Hash_Node_Match ** table;
	int capacity;
} Hash_Table_Match;


#endif