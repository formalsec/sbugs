#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include "Hashtable.h"

unsigned int hash(Key value, int M) {
  int h = 0, a = 127;
  for (; *value != '\0'; value++)
  h = (a*h + *value) % M;
  return h;
}

hash_table* hash_table_init(int size) {
  int i;
  hash_table* ht = can_fail_malloc(sizeof(hash_table));
  ht->table = can_fail_malloc(size*sizeof(hash_item*));
  ht->size = size;
  ht->num_items = 0;
  for(i = 0; i < size; i++) {
    ht->table[i] = NULL;
  }
  return ht;
}

Item hash_table_insert(hash_table* ht, Item item) {
  int i = hash(key(item), ht->size);
  hash_item* hi = ht->table[i];
  while(hi != NULL)
	{
		if(!strcmp(key(hi->item), item->name)) {
      Item temp = hi->item;
			hi->item = item;
			return temp;
		}
		hi = hi->next;
	}

  hi = can_fail_malloc(sizeof(hash_item));
  hi->item = item;
  hi->next = ht->table[i];
  ht->table[i] = hi;
  ht->num_items++;

  return NULL;
}

Item hash_table_search(hash_table* ht, Key value) {
  int i = hash(value, ht->size);
  hash_item* hi = ht->table[i];
  while(hi != NULL) {
    if(!strcmp(key(hi->item), value)) {
      return hi->item;
    }
    hi = hi->next;
  }
  return NULL;
}

Item hash_table_remove(hash_table* ht, Key value) {
  int i = hash(value, ht->size);
  hash_item* hi = ht->table[i];
  hash_item* hi2 = NULL;
  while(hi != NULL) {
    if(!strcmp(key(hi->item), value)) {
      Item temp = hi->item;
      if(hi2 != NULL) {
        hi2->next = hi->next;
      }
      else {
        ht->table[i] = hi->next;
      }
      free(hi);
      hi = NULL;
      ht->num_items--;
      return temp;
    }
    hi2 = hi;
    hi = hi->next;
  }
  return NULL;
}

void hash_table_clear(hash_table* ht) {
  int i;
  Item item;
  hash_item* hi_temp;
  for(i = 0; i < ht->size; i++) {
    hash_item* hi = ht->table[i];
    while(hi != NULL) {
      hi_temp = hi->next;
      item = hi->item;
      hash_table_remove(ht, key(item));
      freeItem(item);
      hi = hi_temp;
    }
  }
}

void hash_table_free(hash_table* ht) {
  hash_table_clear(ht);
  free(ht->table);
  free(ht);
}
