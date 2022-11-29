#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "_features.h"

/* Add a new match to the system */
void new_match(int nl, int id, hashM *hashMt, hash *hashT, link head) {
	char buffer[MAXDESC];
	char **pbuffer;
	int score1, score2;
	int index = 0;

	pbuffer = (char **) can_fail_malloc(sizeof(char *) * (MAXINST));

	getchar();
	while (index != MAXINST) {
		scanf("%[^:\n]:", buffer);
		pbuffer[index] = (char *) can_fail_malloc(sizeof(char) * strlen(buffer)+1);
		strcpy(pbuffer[index], buffer);

		++index;
	}
	scanf("%d:%d\n", &score1, &score2);

	if (searchM(hashMt, pbuffer[0]) != NULL)
		printf("%d Jogo existente.\n", nl);
	else if(searchT(hashT, pbuffer[1]) == NULL || searchT(hashT, pbuffer[2]) == NULL)
		printf("%d Equipa inexistente.\n", nl);
	else {
		head = insert(pbuffer, score1, score2, id, head);
		insertM(hashMt, head);
	}

	for (--index; index >= 0; index--)
		free(pbuffer[index]);
	free(pbuffer);
}

/* Add a new team to the system */
void add_team(int nl, hash *hashT) {
	char buffer[MAXDESC];
	char *name;

	scanf(" %[^:\n]\n", buffer);
	name = (char *) can_fail_malloc(sizeof(char) * strlen(buffer)+1);
	strcpy(name, buffer);

	if (searchT(hashT, name) == NULL)
		insertT(hashT, name);
	else {
		printf("%d Equipa existente.\n", nl);
		free(name);
	}
}

/* List all matches following insertion order on the system */
void list_all_matches(int nl, hashM *hashMt) {
	char *auxC[3];
	int index = 0;
	link *aux = can_fail_malloc(sizeof(link) * hashMt->size);

	for(; index < hashMt->size; index++) {
		if (hashMt->array[index] != NULL) {
			auxC[0] = hashMt->array[index]->name;
			auxC[1] = hashMt->array[index]->team1;
			auxC[2] = hashMt->array[index]->team2;
			aux[index] = create(auxC, hashMt->array[index]->score1, 
				hashMt->array[index]->score2, hashMt->array[index]->id);
		}
		else
			aux[index] = NULL;
	}

	qsort(aux, hashMt->size, sizeof(link), compare_id);

	for(index = 0; index < hashMt->size; index++) {
		if(aux[index] != NULL)
			print(nl, aux[index]);
	}

	for(index = 0; index < hashMt->size; index++) {
		if (aux[index] != NULL) {
			free(aux[index]->name);
			free(aux[index]->team1);
			free(aux[index]->team2);
			free(aux[index]);
			aux[index] = NULL;
		}
	}
	free(aux);
}

/* Compare two matches by id */
int compare_id(const void *match1, const void *match2) {
	link left = (link) match1;
	link right = (link) match2;

	return (left->id - right->id);
}

/* Search for a match in the system */
void search_match(int nl, hashM *hashMt) {
	char buffer[MAXDESC];
	link match;

	scanf(" %[^:\n]\n", buffer);

	match = searchM(hashMt, buffer);
	if(match == NULL)
		printf("%d Jogo inexistente.\n", nl);
	else
		print(nl, match);
}

/* Search for a team in the system */
void search_team(int nl, hashM *hashMt, hash *hashT) {
	char buffer[MAXDESC];
	char *team;
	int index = 0;
	int matchesWon = 0;

	scanf(" %[^:\n]\n", buffer);

	team = searchT(hashT, buffer);
	if(team == NULL)
		printf("%d Equipa inexistente.\n", nl);
	else {
		for(; index < hashMt->size; index++) {
			if (hashMt->array[index] != NULL)
				if (((strcmp(hashMt->array[index]->team1, team) == 0) && (hashMt->array[index]->score1 > hashMt->array[index]->score2))
					|| ((strcmp(hashMt->array[index]->team2, team) == 0) && (hashMt->array[index]->score1 < hashMt->array[index]->score2)))
					++matchesWon;
		}
		printf("%d %s %d\n", nl, team, matchesWon);
	}
}

/* Remove a match from the system */
void delete_match(int nl, hashM *hashMt) {
	char buffer[MAXDESC];
	int hashval;
	scanf(" %[^:\n]\n", buffer);

	if (searchM(hashMt, buffer) != NULL) {
		hashval = hash_position(hashMt, buffer);
		free(hashMt->array[hashval]->name);
		free(hashMt->array[hashval]->team1);
		free(hashMt->array[hashval]->team2);
		free(hashMt->array[hashval]);
		hashMt->array[hashval] = NULL;
	}
	else
		printf("%d Jogo inexistente.\n", nl);
}

/* Change the scores of a match */
void change_score(int nl, hashM *hashMt) {
	char buffer[MAXDESC];
	int score1, score2;
	int hashval;	

	scanf(" %[^:\n]:%d:%d\n", buffer, &score1, &score2);

	if (searchM(hashMt, buffer) != NULL) {
		hashval = hash_position(hashMt, buffer);
		hashMt->array[hashval]->score1 = score1;
		hashMt->array[hashval]->score2 = score2;
	}
	else
		printf("%d Jogo inexistente.\n", nl);
}

/* Look for match position in the hashtable */
int hash_position(hashM *hashtable, char *name) {
	int hashval = hashvalM(hashtable, name);

	while(hashtable->array[hashval] != NULL) {
		if (strcmp(name, hashtable->array[hashval]->name) == 0)
			return hashval;
		else
			hashval = (hashval+1) % hashtable->size;
	}
	return -1;
}

