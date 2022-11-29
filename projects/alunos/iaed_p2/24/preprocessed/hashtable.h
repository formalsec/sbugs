#include "linkedlist.h"

#define HASHSIZE 503

typedef Link *Hash;

int hashkey(char *key);

Hash initHash();

void insertHash(Hash hashtable, char *key, Link new);

Link searchHash(Hash hashtable, char *key);

void removeHash(Hash hashtable, char *key);