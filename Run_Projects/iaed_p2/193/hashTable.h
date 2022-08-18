#include "list.h"

#ifndef PROJECT2_HASHTABLE_H
#define PROJECT2_HASHTABLE_H

/*
 * The Hash Table structure that has the array of lists and the number of buckets.
 */
typedef struct hashTable {
    List **lists; /*Array of lists.*/
    int buckets; /*Number of buckets that the Hash Table have.*/
} HashTable;

HashTable *createHashTable(int buckets);

void deleteHashTable(HashTable *hashMap, void(*freeFunction)(void *));

void hashTableInsert(HashTable *hashMap, char *key, void *dataPointer);

void hashTableRemove(HashTable *hashMap, char *key, int(*compareFunction)(char *, void *), void(*freeFunction)(void *));

link *hashTableSearch(HashTable *hashMap, char *key, int(*compareFunction)(char *, void *));

#endif
