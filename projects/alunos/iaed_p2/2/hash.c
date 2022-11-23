#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

/* initialize hash table */
HashTable HTinit(int max, void* (*keyfunc)(void*)) {	/* max nr of elements */
	
	HashTable ht;
	ht.M = 2*max;							/* M should be >= 2*max */
	ht.N = 0;								/* no elements in the beginning */
	ht.keyfunc = keyfunc;
	ht.t = can_fail_calloc(ht.M, sizeof(void*));		/* alloc mem and initialize to NULL */
	return ht;
}


/* insert item. The item is already created */
void HTinsert(void* pItem, HashTable* ht) {
	
	int i = hashItem((Itemkey)ht->keyfunc(pItem), ht->M);
	while(ht->t[i] != NULL)						/* find free position */
		i = (i+1)%ht->M;
	ht->t[i] = pItem;
	if(ht->N++ > ht->M/2) {
		
		int i;									/* expand */
		void** tmp = ht->t;
		*ht = HTinit(ht->M, ht->keyfunc);		/* duplicate table size */
		for (i = 0; i < ht->M/2; i++)
			if (tmp[i] != NULL)
				HTinsert(tmp[i], ht);			/* re-insert items */
		free(tmp);
	}
}


/* search item given the key k */
void* HTsearch(Itemkey k, HashTable* ht) {
	
	int i = hashItem(k, ht->M);
	while(ht->t[i] != NULL && notEqual((Itemkey)ht->keyfunc(ht->t[i]), k))
		i = (i+1)%ht->M;
	return ht->t[i];	/* returns NULL if not in table, otherwise, returns item */
}


/* remove item given the key k. Does not free item. */
void HTremove(Itemkey k, HashTable* ht) {
	
	int i = hashItem(k, ht->M);
	while(ht->t[i] != NULL && notEqual((Itemkey)ht->keyfunc(ht->t[i]), k))	/* search */
		i = (i+1)%ht->M;
	if(ht->t[i] == NULL) return;				/* element not found */
	ht->t[i] = NULL;
	while(ht->t[i = (i+1)%ht->M] != NULL) {		/* reinsert affected collisions */
		void* v = ht->t[i];
		ht->t[i] = NULL;
		ht->N--;
		HTinsert(v, ht);
	}
	ht->N--;
}


/* destroy hash table, excluding its elements */
void HTdestroy(HashTable* ht) {
	
	free(ht->t);
}


/* destroy hash table, including its elements and keys */
void HTdestroy_with_item_free(HashTable* ht) {
	
	int i;
	for(i = 0; i < ht->M; i++)	
		if (ht->t[i] != NULL) {
			free((Itemkey)ht->keyfunc(ht->t[i]));
			free(ht->t[i]);
		}
	free(ht->t);
}
