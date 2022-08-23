#ifndef HASH_H
#define HASH_H

#include "jogo.h"

/* hash table type */
typedef struct {

	void** t;					/* table pointer */
	int M;						/* table size */
	int N;						/* nr elements */
	void* (*keyfunc)(void*);	/* function that returns the key given the pItem */
} HashTable;

HashTable HTinit(int max, void* (*keyfunc)(void*));

void HTinsert(void* pItem, HashTable* ht);

void* HTsearch(Itemkey k, HashTable* ht);

void HTremove(Itemkey k, HashTable *ht);

void HTdestroy(HashTable* ht);

void HTdestroy_with_item_free(HashTable* ht);

#endif

