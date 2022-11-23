#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doublinklist.h"


/* insert at the end of the list */
void DLinsertEnd(ItemDL v) {
	
	link p = can_fail_malloc(sizeof(struct node));
	
	p->v = v;
	p->next = NULL;
	if(head == NULL) {
		
		head = p;				/* head was empty list */
	}
	else {
		
		head->prev->next = p;	/* insert at the end */
		p->prev = head->prev;
	}
	head->prev = p;				/* update tail */
}


/* search element */
link DLsearch(ItemkeyDL k) {
	
	link p = head;
	
	while(p && notEqual(keyDL(p->v), k))
		p = p->next;
	return p;
}


/* remove element with item free */
void DLremove_with_item_free(link p) {
	
	if(!p) return;						/* return if NULL */
	if(p == head) {						/* element in the head */
		
		if(p->next)						/* element has a next */
			p->next->prev = p->prev;	/* copy ref to tail */
		head = p->next;
	}
	else {
		
		p->prev->next = p->next;
		if(p->next)						/* element in the middle */
			p->next->prev = p->prev;
		else							/* element in the tail */
			head->prev = p->prev;		/* update tail */
	}
	freeItemDL(p->v);
	free(p);
}


/* frees all mem of the list */
void DLdestroy_with_item_free() {

	link p;
	
	while(head) {
		
		p = head;
		head = head->next;
		freeItemDL(p->v);
		free(p);
	}
}
