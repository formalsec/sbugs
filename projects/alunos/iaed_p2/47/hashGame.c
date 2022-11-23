#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "hashGame.h"




gamelink push_game(gamelink head, GAME i) {
	gamelink aux = NEWNode_game(i, head);
	return aux;
}
gamelink remove_Game(gamelink head, gameKey k) {
	gamelink current, prev;
	for (current = head, prev = NULL; current; prev = current, current = current->next) {
		if (eqgame(k, keygame(current->GAME))) {
			if (current == head) head = current->next;
			else prev->next = current->next;
			DELETENode_game(current);
			return head;
		}
	}
	return head;
}

GAME search_list_game(gamelink head, gameKey key) {
	gamelink current;
	for (current = head; current; current = current->next) {
		if (eqgame(keygame(current->GAME), key)) return current->GAME;
	}
	return NULL;
}

void destroy_list_game(gamelink head) {
	gamelink current, aux;
	if (!head) return;
	for (current = head, aux = head->next; current; aux = current->next, DELETENode_game(current), current = aux){}}


gamelink* HASHinit_game(int max) {
	int i;
	gamelink* heads = (gamelink*) can_fail_malloc(max*sizeof(gamelink));
	for(i = 0; i < max; i++) {
		heads[i] = NULL;
	}
	return heads;
}

int hash_game(char *v)
{
int h, a = 31415, b = 27183;
for (h = 0; *v !='\0'; v++, a = a*b % (N-1))
h = (a*h + *v) % N;
return h;
}



gamelink NEWNode_game(GAME GAME, gamelink next) {
	gamelink x = (gamelink) can_fail_malloc(sizeof(struct gamenode));

	x -> GAME = GAME;
	x -> next = next;
	return x;
}

void DELETENode_game(gamelink gamenode) {
	deleteGame(gamenode->GAME);
	free(gamenode);
}

void insert_game(gamelink* heads, GAME GAME) {
	int i = hash_game(keygame(GAME));
	heads[i] = push_game(heads[i], GAME);
}

void delete_game(gamelink* heads, gameKey k) {
	int i = hash_game(k);
	heads[i] = remove_Game(heads[i], k);
}

GAME search_game(gamelink* heads, gameKey k) {
	int i = hash_game(k);
	return search_list_game(heads[i], k);
	

	
}
	


void destroy_hash_game(gamelink* heads) {
	int i;
	for (i = 0; i < N; i++) {
		destroy_list_game(heads[i]);
	}
	free(heads);
}

