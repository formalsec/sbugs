#ifndef _HASHTABLEH_
#define _HASHTABLEH_

#include "Item.h"

typedef struct hash_item {
  struct hash_item* next;
  Item item;
} hash_item;

typedef struct hash_table {
  int size;
  int num_items;
  hash_item** table;
} hash_table;

unsigned int hash(Key value, int M);
hash_table* hash_table_init(int size);
Item hash_table_insert(hash_table* ht, Item item);
Item hash_table_search(hash_table* ht, Key value);
Item hash_table_remove(hash_table* ht, Key value);
void hash_table_clear(hash_table* ht);
void hash_table_free(hash_table* ht);

#endif
