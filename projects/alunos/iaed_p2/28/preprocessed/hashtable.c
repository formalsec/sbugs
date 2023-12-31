#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include "hashtable.h"


unsigned int hash(const char *key)
{
  unsigned long int value = 0;
  unsigned int i = 0;
  unsigned int key_len = strlen(key);
  for (i = 0; i < key_len; i++)
  {
    value = (value * 37) + key[i];
  }

  value = value % 451;
  return value;
}

entry *entryCreate(char *key, void *data)
{
  entry *entry_ = malloc((sizeof(entry)) * 1);
  entry_->key = malloc((strlen(key) + 1) * (sizeof(char)));
  strcpy(entry_->key, key);
  entry_->data = data;
  entry_->next = 0;
  return entry_;
}

hashtable *hashtableCreate()
{
  hashtable *hashtable = malloc(sizeof(hashtable));
  int i = 0;
  hashtable->entries = malloc((sizeof(entry *)) * 451);
  for (i = 0; i < 451; i++)
  {
    hashtable->entries[i] = 0;
  }

  return hashtable;
}

void freeEntry(entry *head)
{
  if (!head)
  {
    return;
  }
  else
  {
    
  }

  freeEntry(head->next);
  free(head->key);
  free(head);
}

void freeHashtable(hashtable *hashtable)
{
  int i = 0;
  for (i = 0; i < 451; i++)
  {
    freeEntry(hashtable->entries[i]);
  }

  free(hashtable->entries);
  free(hashtable);
}

void hashtableAdd(hashtable *hashtable, char *key, void *data)
{
  unsigned int position = hash(key);
  entry *prev;
  entry *entry = hashtable->entries[position];
  if (entry == 0)
  {
    hashtable->entries[position] = entryCreate(key, data);
    return;
  }
  else
  {
    
  }

  while (entry != 0)
  {
    if (strcmp(entry->key, key) == 0)
    {
      return;
    }
    else
    {
      
    }

    prev = entry;
    entry = prev->next;
  }

  prev->next = entryCreate(key, data);
}

void *hashtableGet(hashtable *hashtable, char *key)
{
  unsigned int position = hash(key);
  entry *entry = hashtable->entries[position];
  if (entry == 0)
  {
    return 0;
  }
  else
  {
    
  }

  while (entry != 0)
  {
    if (strcmp(entry->key, key) == 0)
    {
      return entry->data;
    }
    else
    {
      
    }

    entry = entry->next;
  }

  return 0;
}

void hashtableDel(hashtable *hashtable, char *key)
{
  unsigned int position = hash(key);
  entry *prev;
  entry *temp;
  entry *entry = hashtable->entries[position];
  temp = entry;
  if (temp == 0)
  {
    return;
  }
  else
  {
    
  }

  if (strcmp(temp->key, key) == 0)
  {
    hashtable->entries[position] = temp->next;
    free(temp->key);
    free(temp);
    return;
  }
  else
  {
    
  }

  while (temp != 0)
  {
    if (strcmp(temp->key, key) == 0)
    {
      prev->next = temp->next;
      free(temp->key);
      free(temp);
      return;
    }
    else
    {
      
    }

    prev = temp;
    temp = prev->next;
  }

}

