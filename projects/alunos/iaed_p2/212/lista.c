#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "lista.h"

/* Creates new node. */
link NEW(struct jogo game, link y){
	link x = can_fail_malloc(sizeof(struct node));
	x->game = game;
	x->prev = y;
	x->next = NULL;
	return x;
}

/* Inserts a node at the end of list based on slides. */
link insertEnd(link head, link *last, struct jogo game, struct node **new){
	link x;
	if(head == NULL){
		x = NEW(game, NULL);
		x->prev = NULL;
		*last = x;
		*new = x;
		return x;
	}
	(*last) -> next = NEW(game, *last);
	*new = (*last) -> next;

	*last = (*last) -> next;
	
	return head;
}

/* Frees the dynamically allocated memory of a node. */
void freeNode(link x){
	free(x->game.nome);
	free(x->game.equipa1);
	free(x->game.equipa2);
	free(x);
}

/* Removes a node from the double linked list. */
void rmNode(link del, link *head_ref, link *last){
    /* Base case */
    if (*head_ref == NULL || del == NULL) 
        return; 
  
    /* If node to be deleted is head node */
    if (*head_ref == del) 
        *head_ref = del->next; 
  
    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL) 
        del->next->prev = del->prev; 
  	else
    	*last = del->prev;


    /* Change prev only if node to be deleted is NOT the first node */
    if (del->prev != NULL) 
        del->prev->next = del->next;  
  
    /* Finally, free the memory occupied by del*/
    freeNode(del); 
    return; 
}

/* Function to print all nodes in a given doubly linked list. */
void print(link node, int nl){ 	
    while (node != NULL) { 
        printSingle(node, nl);
        node = node->next; 
    } 
}

/* Function to print a single node in a given doubly linked list. */
void printSingle(link node, int nl){
	printf("%d %s %s %s %d %d\n", nl,node->game.nome, node->game.equipa1, node->game.equipa2, node->game.score1, node->game.score2);
}