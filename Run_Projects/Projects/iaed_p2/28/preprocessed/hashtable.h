#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdlib.h>
#include <string.h>

#define HASHTABLE_SIZE  451

typedef struct entry{
  char * key;
  void * data;
  struct entry * next;
} entry;

typedef struct hashtable{
    entry ** entries;
} hashtable;

hashtable * hashtableCreate();
void hashtableAdd(hashtable * hashtable, char * key, void * data);
void * hashtableGet(hashtable * hashtable, char * key);
void hashtableDel(hashtable * hashtable, char * key);
void freeHashtable(hashtable * hashtable);

#endif /* HASHTABLE_H */
