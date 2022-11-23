#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/* Creates a match node */
link create(char *pbuffer[], int score1, int score2, int id) {
	link match = (link) can_fail_malloc(sizeof(struct node));

	match->name = (char *) can_fail_malloc(sizeof(char) * strlen(pbuffer[0])+1);
	strcpy(match->name, pbuffer[0]);
	match->team1 = (char *) can_fail_malloc(sizeof(char) * strlen(pbuffer[1])+1);
	strcpy(match->team1, pbuffer[1]);
	match->team2 = (char *) can_fail_malloc(sizeof(char) * strlen(pbuffer[2])+1);
	strcpy(match->team2, pbuffer[2]);
	match->score1 = score1;
	match->score2 = score2;

	match->id = id;

	match->next = NULL;

	return match;
}

/* Inserts in the list a match node*/
link insert(char *pbuffer[], int score1, int score2, int id, link head) {
	link match;

	if (head == NULL)
		return create(pbuffer, score1, score2, id);

	for(match = head; match->next != NULL; match = match->next);
	match->next = create(pbuffer, score1, score2, id);

	return head;
}

void print(int nl, link head) {
	link new_head;

	for(new_head = head; new_head != NULL; new_head = head->next)
		printf("%d %s %s %s %d %d\n", nl, new_head->name, new_head->team1, 
			new_head->team2, new_head->score1, new_head->score2);
}