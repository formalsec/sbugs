#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "hashTable.h"
#include <stdlib.h>

/*
 * Allocs the needed memory to the new Hash Table and creates the list for each bucket.
 * The buckets need to be bigger that one.
 * Requires: the number of buckets to the new hash table.
 * Returns: the hash table pointer created.
 */
HashTable *createHashTable(int buckets) {
    int i;

    HashTable *hashTable;
    if (buckets < 1) {
        return NULL;
    }
    hashTable = (HashTable *) can_fail_malloc(sizeof(HashTable));
    hashTable->lists = (List **) can_fail_malloc(sizeof(List *) * buckets);
    for (i = 0; i < buckets; i++) {
        hashTable->lists[i] = creatList();
    }
    hashTable->buckets = buckets;
    return hashTable;
}

/*
 * Deletes the list in every bucket using the free function and the 'deleteList' function.
 * After that frees the list array and the hash table.
 * The Hash Table cannot be NULL.
 * The free function can be NULL if its desired the data to not be deleted.
 * Requires: Hash Table pointer and the free function.
 */
void deleteHashTable(HashTable *hashTable, void(*freeFunction)(void *)) {
    int i;
    if (hashTable == NULL) {
        return;
    }
    for (i = 0; i < hashTable->buckets; i++) {
        deleteList(hashTable->lists[i], freeFunction);
    }
    free(hashTable->lists);
    free(hashTable);
}

/*
 * Hash function for strings used in the by the hash tables.
 * The char array cannot be NULL.
 * Requires: char array with the key and hashtable's buckets.
 * Returns: the index for that key.
 */
int hash(char *v, int buckets) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++, a = a * b % (buckets - 1))
        h = (a * h + *v) % buckets;
    return h;
}

/*
 * Used the hash function to determine the index and inserts in the list that is on that bucket.
 * The Hash Table, the key and the data pointer cannot be NULL.
 * Requires: Hash Table pointer, char array with the key and the data pointer.
 */
void hashTableInsert(HashTable *hashTable, char *key, void *dataPointer) {
    int index;
    if (hashTable == NULL || key == NULL || dataPointer == NULL) {
        return;
    }
    index = hash(key, hashTable->buckets);
    listInsertEnd(hashTable->lists[index], dataPointer);
}

/*
 * Used the hash function to determine the index and removes the element in the list that is on that bucket.
 * The hash table, key and compare function cannot be NULL.
 * The free function can be NULL.
 * Requires: Hash Table pointer, char array with the key and the data pointer.
 */
void hashTableRemove(HashTable *hashTable, char *key, int(*compareFunction)(char *, void *),
                     void(*freeFunction)(void *)) {
    int index;
    if (hashTable == NULL || key == NULL || compareFunction == NULL) {
        return;
    }
    index = hash(key, hashTable->buckets);
    listRemoveElement(hashTable->lists[index], key, compareFunction, freeFunction);
}

/*
 * Searches throw the Hash Table for the node with the given key using the 'hash' function and the 'listSearch' function.
 * The HashTable, key and compareFunction cannot be NULL.
 * Requires: HashTable pointer, char array with the key and the compare function pointer.
 * Returns: NULL if any of the arguments is NULL or if there is no node with the given key otherwise returns the node
 * pointer.
 */
link *hashTableSearch(HashTable *hashTable, char *key, int(*compareFunction)(char *, void *)) {
    int index;
    if (hashTable == NULL || key == NULL || compareFunction == NULL) {
        return NULL;
    }
    index = hash(key, hashTable->buckets);
    return listSearch(hashTable->lists[index], key, compareFunction);
}
