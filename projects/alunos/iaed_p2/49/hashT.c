#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hashT.h"

/* Initialize hashtable for storage of team names */
hash *initT(int size) {
	hash *hashtable = can_fail_malloc(sizeof(hash));
	int index = 0;
	
	hashtable->size = size;
	hashtable->numberTeams = 0;
	hashtable->array = (char **) can_fail_malloc(sizeof(char *) * hashtable->size);

	for(; index < hashtable->size; index++)
		hashtable->array[index] = NULL;

	return hashtable;
}

/* Form hash value for team name */
int hashvalT(hash *hashtable, char *name) {
	int hashval = 0;
	int prime = 31;

	for (; *name != '\0'; name++)
		hashval = (*name + prime * hashval) % hashtable->size;
	return hashval;
}

/* Insert the team name into the hashtable */
void insertT(hash *hashtable, char *name) {
	int hashval = hashvalT(hashtable, name);

	while(hashtable->array[hashval] != NULL)
		hashval = (hashval+1) % hashtable->size;

	hashtable->array[hashval] = name;

	hashtable->numberTeams++;

	if (hashtable->numberTeams > hashtable->size / 2)
		expandT(hashtable);
}

/* Duplicate hashtable size rounding up to next prime */
void expandT(hash *hashtable) {
	int index;
	int newHashval;
	char **auxT;
	int oldSize = hashtable->size;
	int newSize = next_size(hashtable->size);
	char **newArray = can_fail_malloc(sizeof(char *) * newSize);

	hashtable->size = newSize;

	for(index = 0; index < newSize; index++)
		newArray[index] = NULL;

	for(index = 0; index < oldSize; index++) {
		if(hashtable->array[index] != NULL) {
			newHashval = hashvalT(hashtable, hashtable->array[index]);
			while (newArray[newHashval] != NULL)
				newHashval = (newHashval+1) % newSize;
			newArray[newHashval] = hashtable->array[index];
		hashtable->array[index] = NULL;
		}
	}

	auxT = hashtable->array;

	hashtable->array = newArray;

	free(auxT);
	newArray = NULL;
}

/* Search for team name in the hashtable */
char *searchT(hash *hashtable, char *name) {
	int hashval = hashvalT(hashtable, name);

	while(hashtable->array[hashval] != NULL) {
		if (strcmp(name, hashtable->array[hashval]) == 0)
			return hashtable->array[hashval];
		else
			hashval = (hashval+1) % hashtable->size;
	}
	return NULL;
}

/* Free all memory allocated for hashtable */
void eraseT(hash *hashtable) {
	int index = 0;

	for(; index < hashtable->size; index++) {
		if (hashtable->array[index] != NULL) {
			free(hashtable->array[index]);
			hashtable->array[index] = NULL;
		}
	}
	free(hashtable->array);
	free(hashtable);
}

/* Define the next size value for hashtable */
int next_size(int size) {
	int counter = 1;

	size *= 2;

	while(counter != size) {
		if (size % counter == 0) {
			++size;
		}
		++counter;
	}
	return size;
}