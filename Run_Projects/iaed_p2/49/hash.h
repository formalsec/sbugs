#ifndef HASH_H_
#define HASH_H_

#include "list.h"

/* The initial size of the hashtable */
#define HASHSIZE 3

/* Structure for the hashtable */
typedef struct structHashM {
	int size;
	int numberMatches;
	link *array;
} hashM;

hashM *initM(int size);
int hashvalM(hashM *hashtable, char *name);
void insertM(hashM *hashtable, link match);
void expandM(hashM *hashtable);
void eraseM(hashM *hashtable);
link searchM(hashM *hashtable, char *name);
int next_sizeM(int size);

#endif