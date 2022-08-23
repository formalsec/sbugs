/*File generated by PreProcessor.py*/


#include "main.h"


unsigned int hash(char *key, int size)
{
  unsigned int value = 0;
  unsigned int counter;
  value = 5381;
  while (counter = *(key++))
  {
    value = ((counter + (value << 6)) + (value << 16)) - value;
  }

  value = value % size;
  return value;
}

Hash_Array *hashtable_init(int size)
{
  Hash_Array *hashtable;
  int counter;
  hashtable = malloc(sizeof(Hash_Array));
  hashtable->entries = malloc((sizeof(Bucket *)) * size);
  for (counter = 0; counter < size; counter++)
  {
    hashtable->entries[counter] = 0;
  }

  hashtable->size = size;
  return hashtable;
}

Bucket *create_bucket(char *key, Game *value)
{
  Bucket *bucket;
  bucket = malloc(sizeof(Bucket));
  bucket->key = key;
  bucket->data = value;
  bucket->next = 0;
  return bucket;
}

void hashtable_insert(Hash_Array *hashtable, char *key, Game *value)
{
  unsigned int slot;
  Bucket *entry;
  Bucket *prev;
  slot = hash(key, hashtable->size);
  entry = hashtable->entries[slot];
  if (entry == 0)
  {
    {
      hashtable->entries[slot] = create_bucket(key, value);
    }
  }
  else
  {
    {
      while (entry != 0)
      {
        if (strcmp(entry->key, key) == 0)
        {
          {
            free_data(entry->data);
            entry->data = value;
            return;
          }
        }
        else
        {
          
        }

        prev = entry;
        entry = prev->next;
      }

      prev->next = create_bucket(key, value);
    }
  }

  return;
}

Game *hashtable_get(Hash_Array *hashtable, char *key)
{
  unsigned int slot;
  Bucket *entry;
  slot = hash(key, hashtable->size);
  entry = hashtable->entries[slot];
  while (entry != 0)
  {
    if (strcmp(entry->key, key) == 0)
    {
      {
        return entry->data;
      }
    }
    else
    {
      
    }

    entry = entry->next;
  }

  return 0;
}

void hashtable_print_all(Hash_Array *hashtable)
{
  int counter;
  int aux_counter;
  Bucket *entry;
  for (counter = 0; counter < hashtable->size; counter++)
  {
    entry = hashtable->entries[counter];
    if (entry == 0)
    {
      {
        continue;
      }
    }
    else
    {
      
    }

    printf("%4d:  ", counter);
    for (aux_counter = 0;; aux_counter++)
    {
      if (entry->data->team_flag == 0)
      {
        {
          printf(" (%s:%s) ->", entry->key, entry->data->team1);
        }
      }
      else
      {
        
      }

      if (entry->data->team_flag == 1)
      {
        {
          printf(" (%s:%d) ->", entry->key, entry->data->score1);
        }
      }
      else
      {
        
      }

      if (entry->next == 0)
      {
        {
          printf(" NULL");
          break;
        }
      }
      else
      {
        
      }

      entry = entry->next;
    }

  }

}

void hashtable_visualize(Hash_Array *hashtable)
{
  int counter;
  int aux_counter;
  Bucket *entry;
  for (counter = 0; counter < hashtable->size; counter++)
  {
    entry = hashtable->entries[counter];
    if (entry == 0)
    {
      {
        continue;
      }
    }
    else
    {
      
    }

    printf("%4d:  ", counter);
    for (aux_counter = 0;; aux_counter++)
    {
      if (entry->data->team_flag == 0)
      {
        {
          printf(" (%s:%s:%d) ->", entry->key, entry->data->team1, *entry->data->index);
        }
      }
      else
      {
        
      }

      if (entry->data->team_flag == 1)
      {
        {
          printf(" (%s:%d:%d) ->", entry->key, entry->data->score1, *entry->data->index);
        }
      }
      else
      {
        
      }

      if (entry->next == 0)
      {
        {
          printf(" NULL");
          break;
        }
      }
      else
      {
        
      }

      entry = entry->next;
    }

    putchar('\n');
  }

}

void hashtable_free_all(Hash_Array *hashtable)
{
  int counter;
  int aux_counter;
  Bucket *entry;
  Bucket *aux;
  for (counter = 0; counter < hashtable->size; counter++)
  {
    entry = hashtable->entries[counter];
    if (entry == 0)
    {
      {
        free(entry);
        continue;
      }
    }
    else
    {
      
    }

    for (aux_counter = 0;; aux_counter++)
    {
      aux = entry->next;
      free_data(entry->data);
      free(entry->key);
      free(entry);
      if (aux == 0)
      {
        {
          break;
        }
      }
      else
      {
        
      }

      entry = aux;
    }

  }

  free(hashtable->entries);
  free(hashtable);
  return;
}

void hashtable_del(Hash_Array *hashtable, char *key)
{
  unsigned int slot;
  Bucket *entry;
  Bucket *prev;
  int counter;
  slot = hash(key, hashtable->size);
  entry = hashtable->entries[slot];
  for (counter = 0; entry != 0; counter++)
  {
    if (strcmp(entry->key, key) == 0)
    {
      {
        if ((entry->next == 0) && (counter == 0))
        {
          {
            hashtable->entries[slot] = 0;
          }
        }
        else
        {
          
        }

        if ((entry->next != 0) && (counter == 0))
        {
          {
            hashtable->entries[slot] = entry->next;
          }
        }
        else
        {
          
        }

        if ((entry->next == 0) && (counter != 0))
        {
          {
            prev->next = 0;
          }
        }
        else
        {
          
        }

        if ((entry->next != 0) && (counter != 0))
        {
          {
            prev->next = entry->next;
          }
        }
        else
        {
          
        }

        free(entry->key);
        free_data(entry->data);
        free(entry);
        return;
      }
    }
    else
    {
      
    }

    prev = entry;
    entry = prev->next;
  }

  return;
}

void free_data(Game *data)
{
  if (data->team_flag == 0)
  {
    {
      free(data->team1);
      free(data->team2);
    }
  }
  else
  {
    
  }

  free(data);
  return;
}

void biggest_wins(int line_number, Hash_Array *hashtable)
{
  int counter;
  int aux_counter;
  int size = 0;
  int max_win = -1;
  int list_size = 10;
  char **team_list;
  Bucket *entry;
  Bucket *aux;
  team_list = malloc((sizeof(char *)) * list_size);
  for (counter = 0; counter < hashtable->size; counter++)
  {
    entry = hashtable->entries[counter];
    if (entry == 0)
    {
      {
        continue;
      }
    }
    else
    {
      
    }

    for (aux_counter = 0;; aux_counter++)
    {
      aux = entry->next;
      if (entry->data->score1 == max_win)
      {
        {
          size = size + 1;
          team_list[size] = entry->key;
        }
      }
      else
      {
        if (entry->data->score1 > max_win)
        {
          {
            size = 0;
            team_list[size] = entry->key;
            max_win = entry->data->score1;
          }
        }
        else
        {
          
        }

      }

      if (aux == 0)
      {
        {
          break;
        }
      }
      else
      {
        
      }

      entry = aux;
    }

  }

  if (max_win < 0)
  {
    {
      free(team_list);
      return;
    }
  }
  else
  {
    
  }

  printf("%d Melhores %d\n", line_number, max_win);
  if (size == 0)
  {
    {
      printf("%d * %s\n", line_number, team_list[0]);
      free(team_list);
      return;
    }
  }
  else
  {
    
  }

  size = size + 1;
  qsort(team_list, size, sizeof(team_list[1024]), compare_str);
  for (counter = 0; counter < size; counter++)
  {
    printf("%d * %s\n", line_number, team_list[counter]);
  }

  free(team_list);
  return;
}

int compare_str(const void *a, const void *b)
{
  const char *pa = *((const char **) a);
  const char *pb = *((const char **) b);
  return strcmp(pa, pb);
}

