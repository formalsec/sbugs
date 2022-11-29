#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "hashTeam.h"




teamlink push_team(teamlink head, TEAM i) {
	teamlink aux = NEWNode_team(i, head);
	return aux;
}

teamlink remove_TEAM(teamlink head, teamKey k) {
	teamlink current, prev;
	for (current = head, prev = NULL; current; prev = current, current = current->next) {
		if (eqteam(k, keyteam(current->TEAM))) {
			if (current == head) head = current->next;
			else prev->next = current->next;
			DELETENode_team(current);
			return head;
		}
	}
	return head;
}

TEAM search_list_team(teamlink head, teamKey key) {
	teamlink current;
	for (current = head; current; current = current->next) {
		if (eqteam(keyteam(current->TEAM), key)) return current->TEAM;
	}
	return NULL;
}



void destroy_list_team(teamlink head) {
	teamlink current, aux;
	if (!head) return;
	for (current = head, aux = head->next; current; aux = current->next, DELETENode_team(current), current = aux)
	{}
	}


teamlink* HASHinit_team() {
	int i;
	teamlink* heads = (teamlink*) can_fail_malloc(M*sizeof(teamlink));
	for(i = 0; i < M; i++) {
		heads[i] = NULL;
	}
	return heads;
}

int hash_team(char *v)
{
int h, a = 31415, b = 27183;
for (h = 0; *v != '\0'; v++, a = a*b % (M-1))
h = (a*h + *v) % M;
return h;
}

teamlink NEWNode_team(TEAM TEAM, teamlink next) {
	teamlink x = can_fail_malloc(sizeof(struct node));

	x -> TEAM = TEAM;
	x -> next = next;
	return x;
}

void DELETENode_team(teamlink node) {
	deleteTeam(node->TEAM);
	free(node);
}


void insert_team(teamlink* heads, TEAM TEAM) {
	int i = hash_team(keyteam(TEAM));
	heads[i] = push_team(heads[i], TEAM);
}



TEAM search_team(teamlink* heads, teamKey k) {
	int i = hash_team(k);
	return search_list_team(heads[i], k);
}

void destroy_hash_team(teamlink* heads) {		
	int i;
	for (i = 0; i < M; i++) {
		destroy_list_team(heads[i]);
	}
	free(heads);
}

