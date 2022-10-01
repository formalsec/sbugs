/*File generated by PreProcessor.py*/


#include <stdlib.h>
#include <string.h>
#include "Hashtable.h"


unsigned int hash(Key value, int M)
{
  int h = 0;
  int a = 127;
  for (; (*value) != '\0'; value++)
    h = ((a * h) + (*value)) % M;

  return h;
}

hash_table *hash_table_init(int size)
{
  int i;
  hash_table *ht = malloc(sizeof(hash_table));
  ht->table = malloc(size * (sizeof(hash_item *)));
  ht->size = size;
  ht->num_items = 0;
  for (i = 0; i < size; i++)
  {
    ht->table[i] = 0;
  }

  return ht;
}

Item hash_table_insert(hash_table *ht, Item item)
{
  int i = hash(item->name, ht->size);
  hash_item *hi = ht->table[i];
  while (hi != 0)
  {
    if (!strcmp(hi->item->name, item->name))
    {
      Item temp = hi->item;
      hi->item = item;
      return temp;
    }
    else
    {
      
    }

    hi = hi->next;
  }

  hi = malloc(sizeof(hash_item));
  hi->item = item;
  hi->next = ht->table[i];
  ht->table[i] = hi;
  ht->num_items++;
  return 0;
}

Item hash_table_search(hash_table *ht, Key value)
{
  int i = hash(value, ht->size);
  hash_item *hi = ht->table[i];
  while (hi != 0)
  {
    if (!strcmp(hi->item->name, value))
    {
      return hi->item;
    }
    else
    {
      
    }

    hi = hi->next;
  }

  return 0;
}

Item hash_table_remove(hash_table *ht, Key value)
{
  int i = hash(value, ht->size);
  hash_item *hi = ht->table[i];
  hash_item *hi2 = 0;
  while (hi != 0)
  {
    if (!strcmp(hi->item->name, value))
    {
      Item temp = hi->item;
      if (hi2 != 0)
      {
        hi2->next = hi->next;
      }
      else
      {
        ht->table[i] = hi->next;
      }

      free(hi);
      hi = 0;
      ht->num_items--;
      return temp;
    }
    else
    {
      
    }

    hi2 = hi;
    hi = hi->next;
  }

  return 0;
}

void hash_table_clear(hash_table *ht)
{
  int i;
  Item item;
  hash_item *hi_temp;
  for (i = 0; i < ht->size; i++)
  {
    hash_item *hi = ht->table[i];
    while (hi != 0)
    {
      hi_temp = hi->next;
      item = hi->item;
      hash_table_remove(ht, item->name);
      freeItem(item);
      hi = hi_temp;
    }

  }

}

void hash_table_free(hash_table *ht)
{
  hash_table_clear(ht);
  free(ht->table);
  free(ht);
}
