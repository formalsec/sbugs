/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "_features.h"


void new_match(int nl, int id, hashM *hashMt, hash *hashT, link head)
{
  char buffer[1024];
  char **pbuffer;
  int score1;
  int score2;
  int index = 0;
  pbuffer = (char **) malloc((sizeof(char *)) * 3);
  getchar();
  while (index != 3)
  {
    for (int buffer_index = 0; buffer_index < 10; buffer_index++)
    {
      buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
    }

    buffer[10 - 1] = '\0';
    pbuffer[index] = (char *) malloc(((sizeof(char)) * strlen(buffer)) + 1);
    strcpy(pbuffer[index], buffer);
    ++index;
  }

  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (searchM(hashMt, pbuffer[0]) != 0)
  {
    printf("%d Jogo existente.\n", nl);
  }
  else
  {
    if ((searchT(hashT, pbuffer[1]) == 0) || (searchT(hashT, pbuffer[2]) == 0))
    {
      printf("%d Equipa inexistente.\n", nl);
    }
    else
    {
      head = insert(pbuffer, score1, score2, id, head);
      insertM(hashMt, head);
    }

  }

  for (--index; index >= 0; index--)
    free(pbuffer[index]);

  free(pbuffer);
}

void add_team(int nl, hash *hashT)
{
  char buffer[1024];
  char *name;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  name = (char *) malloc(((sizeof(char)) * strlen(buffer)) + 1);
  strcpy(name, buffer);
  if (searchT(hashT, name) == 0)
  {
    insertT(hashT, name);
  }
  else
  {
    printf("%d Equipa existente.\n", nl);
    free(name);
  }

}

void list_all_matches(int nl, hashM *hashMt)
{
  char *auxC[3];
  int index = 0;
  link *aux = malloc((sizeof(link)) * hashMt->size);
  for (; index < hashMt->size; index++)
  {
    if (hashMt->array[index] != 0)
    {
      auxC[0] = hashMt->array[index]->name;
      auxC[1] = hashMt->array[index]->team1;
      auxC[2] = hashMt->array[index]->team2;
      aux[index] = create(auxC, hashMt->array[index]->score1, hashMt->array[index]->score2, hashMt->array[index]->id);
    }
    else
    {
      aux[index] = 0;
    }

  }

  qsort(aux, hashMt->size, sizeof(link), compare_id);
  for (index = 0; index < hashMt->size; index++)
  {
    if (aux[index] != 0)
    {
      print(nl, aux[index]);
    }
    else
    {
      
    }

  }

  for (index = 0; index < hashMt->size; index++)
  {
    if (aux[index] != 0)
    {
      free(aux[index]->name);
      free(aux[index]->team1);
      free(aux[index]->team2);
      free(aux[index]);
      aux[index] = 0;
    }
    else
    {
      
    }

  }

  free(aux);
}

int compare_id(const void *match1, const void *match2)
{
  link left = (link) match1;
  link right = (link) match2;
  return left->id - right->id;
}

void search_match(int nl, hashM *hashMt)
{
  char buffer[1024];
  link match;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  match = searchM(hashMt, buffer);
  if (match == 0)
  {
    printf("%d Jogo inexistente.\n", nl);
  }
  else
  {
    print(nl, match);
  }

}

void search_team(int nl, hashM *hashMt, hash *hashT)
{
  char buffer[1024];
  char *team;
  int index = 0;
  int matchesWon = 0;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  team = searchT(hashT, buffer);
  if (team == 0)
  {
    printf("%d Equipa inexistente.\n", nl);
  }
  else
  {
    for (; index < hashMt->size; index++)
    {
      if (hashMt->array[index] != 0)
      {
        if (((strcmp(hashMt->array[index]->team1, team) == 0) && (hashMt->array[index]->score1 > hashMt->array[index]->score2)) || ((strcmp(hashMt->array[index]->team2, team) == 0) && (hashMt->array[index]->score1 < hashMt->array[index]->score2)))
        {
          ++matchesWon;
        }
        else
        {
          
        }

      }
      else
      {
        
      }

    }

    printf("%d %s %d\n", nl, team, matchesWon);
  }

}

void delete_match(int nl, hashM *hashMt)
{
  char buffer[1024];
  int hashval;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  if (searchM(hashMt, buffer) != 0)
  {
    hashval = hash_position(hashMt, buffer);
    free(hashMt->array[hashval]->name);
    free(hashMt->array[hashval]->team1);
    free(hashMt->array[hashval]->team2);
    free(hashMt->array[hashval]);
    hashMt->array[hashval] = 0;
  }
  else
  {
    printf("%d Jogo inexistente.\n", nl);
  }

}

void change_score(int nl, hashM *hashMt)
{
  char buffer[1024];
  int score1;
  int score2;
  int hashval;
  for (int buffer_index = 0; buffer_index < 10; buffer_index++)
  {
    buffer[buffer_index] = new_sym_var(sizeof(char) * 8);
  }

  buffer[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (searchM(hashMt, buffer) != 0)
  {
    hashval = hash_position(hashMt, buffer);
    hashMt->array[hashval]->score1 = score1;
    hashMt->array[hashval]->score2 = score2;
  }
  else
  {
    printf("%d Jogo inexistente.\n", nl);
  }

}

int hash_position(hashM *hashtable, char *name)
{
  int hashval = hashvalM(hashtable, name);
  while (hashtable->array[hashval] != 0)
  {
    if (strcmp(name, hashtable->array[hashval]->name) == 0)
    {
      return hashval;
    }
    else
    {
      hashval = (hashval + 1) % hashtable->size;
    }

  }

  return -1;
}

