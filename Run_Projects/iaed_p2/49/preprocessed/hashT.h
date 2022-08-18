#ifndef HASHT_H_
#define HASHT_H_

/* The initial size of the hashtable */
#define HASHSIZE 3

/* Structure for the hashtable of team names*/
typedef struct structHash {
	int size;
	int numberTeams;
	char **array;
} hash;

/* Prototypes for creating and managing hastable */
hash *initT(int size);
int hashvalT(hash *hashtable, char *name);
void insertT(hash *hashtable, char *name);
void expandT(hash *hashtable);
char *searchT(hash *hashtable, char *name);
void eraseT(hash *hashtable);
int next_size(int size);

#endif