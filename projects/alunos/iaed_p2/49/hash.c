#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash.h"

/* Initialize the hashtable for storage of match names */
hashM *initM(int size) {
	hashM *hashtable = can_fail_malloc(sizeof(hashM));
	int index = 0;

	hashtable->size = size;
	hashtable->numberMatches = 0;
	hashtable->array = (link *) can_fail_malloc(sizeof(link) * size);

	for(; index < hashtable->size; index++)
		hashtable->array[index] = NULL;

	return hashtable;
}

/* Form hash value for match name */
int hashvalM(hashM *hashtable, char *name) {
	int hashval = 0;
	int prime = 31;

	for (; *name != '\0'; name++)
		hashval = (*name + prime * hashval) % hashtable->size;
	return hashval;
}

/* Insert the match name into the hashtable */
void insertM(hashM *hashtable, link match) {
	int hashval = hashvalM(hashtable, match->name);

	while(hashtable->array[hashval] != NULL)
		hashval = (hashval+1) % hashtable->size;

	hashtable->array[hashval] = match;

	hashtable->numberMatches++;

	if (hashtable->numberMatches > hashtable->size / 2)
		expandM(hashtable);
}

/* Duplicate hashtable size rounding up to next prime */
void expandM(hashM *hashtable) {
	int index;
	int newHashval;

	link *auxT;

	int oldSize = hashtable->size;
	int newSize = next_sizeM(hashtable->size);

	link *newArray = can_fail_malloc(sizeof(link) * newSize);

	hashtable->size = newSize;

	for(index = 0; index < newSize; index++)
		newArray[index] = NULL;

	for(index = 0; index < oldSize; index++) {
		if(hashtable->array[index] != NULL) {
			newHashval = hashvalM(hashtable, hashtable->array[index]->name);
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

/* Search for match name in the hashtable */
link searchM(hashM *hashtable, char *name) {
	int hashval = hashvalM(hashtable, name);

	while(hashtable->array[hashval] != NULL) {
		if (strcmp(name, hashtable->array[hashval]->name) == 0)
			return hashtable->array[hashval];
		else
			hashval = (hashval+1) % hashtable->size;
	}
	return NULL;
}

/* Free all memory allocated for hashtable */
void eraseM(hashM *hashtable) {
	int index = 0;

	for(; index < hashtable->size; index++) {
		if (hashtable->array[index] != NULL) {
			free(hashtable->array[index]->name);
			free(hashtable->array[index]->team1);
			free(hashtable->array[index]->team2);
			free(hashtable->array[index]);
			hashtable->array[index] = NULL;
		}
	}
	free(hashtable->array);
	free(hashtable);
}

/* Define the next size value for hashtable */
int next_sizeM(int size) {
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