/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq.h"
#include "j.h"


list2 *list2_create()
{
  list2 *l = malloc(sizeof(list2));
  l->head = (l->last = 0);
  return l;
}

void free_node(List *n)
{
  free(n->eq2);
  free(n->eq1);
  free(n->key);
  free(n);
}

void free_list2(list2 *l)
{
  while (l->head)
  {
    List *tmp = l->head->next;
    free_node(l->head);
    l->head = tmp;
  }

  free(l);
}

void add_list2(list2 *l, List *n)
{
  List *tmp = malloc(sizeof(List));
  tmp->previous = l->last;
  tmp->next = 0;
  tmp->key = malloc((sizeof(char)) * (strlen(n->key) + 1));
  strcpy(tmp->key, n->key);
  tmp->eq1 = malloc((sizeof(char)) * (strlen(n->eq1) + 1));
  strcpy(tmp->eq1, n->eq1);
  tmp->eq2 = malloc((sizeof(char)) * (strlen(n->eq2) + 1));
  strcpy(tmp->eq2, n->eq2);
  tmp->score1 = n->score1;
  tmp->score2 = n->score2;
  if (l->last)
  {
    l->last->next = tmp;
  }
  else
  {
    l->head = tmp;
  }

  l->last = tmp;
}

void list2_handler(list2 *ls, char *nome, int score1, int score2)
{
  List *n;
  for (n = ls->head; n; n = n->next)
  {
    if (strcmp(n->key, nome) == 0)
    {
      break;
    }
    else
    {
      
    }

  }

  n->score1 = score1;
  n->score2 = score2;
}

HashTable *ht_create()
{
  HashTable *ht = malloc(sizeof(HashTable));
  ht->size = 1013;
  ht->array = calloc(ht->size, sizeof(List *));
  return ht;
}

int ht_get(HashTable *hashtable, const char *key)
{
  unsigned int i;
  List *tmp;
  if (hashtable == 0)
  {
    return 1;
  }
  else
  {
    
  }

  i = hash(key, hashtable->size);
  tmp = hashtable->array[i];
  while (tmp != 0)
  {
    if (strcmp(tmp->key, key) == 0)
    {
      return 0;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  return 1;
}

void ht_insert(HashTable *hashtable, List *jogo)
{
  unsigned int i;
  i = hash(jogo->key, hashtable->size);
  if (hashtable->array[i] != 0)
  {
    hashtable->array[i]->previous = jogo;
  }
  else
  {
    
  }

  jogo->next = hashtable->array[i];
  hashtable->array[i] = jogo;
}

List *ht_lookup(HashTable *hashtable, const char *key)
{
  unsigned int i = hash(key, hashtable->size);
  List *tmp = hashtable->array[i];
  while ((tmp != 0) && (strcmp(tmp->key, key) != 0))
  {
    tmp = tmp->next;
  }

  return tmp;
}

int score_handler(HashTable *hashtable, char *nome, int s1, int s2)
{
  unsigned int i = hash(nome, hashtable->size);
  List *tmp = hashtable->array[i];
  while (tmp != 0)
  {
    if (strcmp(tmp->key, nome) == 0)
    {
      break;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  tmp->score1 = s1;
  tmp->score2 = s2;
  return 0;
}

void free_hash_table_j(HashTable *ht)
{
  free(ht->array);
  free(ht);
}

void a(int NL, HashTable *hashtable, HashTable2 *hash_eq, list2 *ls)
{
  char key[1024];
  char eq1[1024];
  char eq2[1024];
  int score1;
  int score2;
  List *name = malloc(sizeof(List));
  getchar();
  for (int key_index = 0; key_index < 10; key_index++)
  {
    key[key_index] = new_sym_var(sizeof(char) * 8);
  }

  key[10 - 1] = '\0';
  for (int eq1_index = 0; eq1_index < 10; eq1_index++)
  {
    eq1[eq1_index] = new_sym_var(sizeof(char) * 8);
  }

  eq1[10 - 1] = '\0';
  for (int eq2_index = 0; eq2_index < 10; eq2_index++)
  {
    eq2[eq2_index] = new_sym_var(sizeof(char) * 8);
  }

  eq2[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  name->key = malloc((sizeof(char)) * (strlen(key) + 1));
  strcpy(name->key, key);
  name->eq1 = malloc((sizeof(char)) * (strlen(eq1) + 1));
  strcpy(name->eq1, eq1);
  name->eq2 = malloc((sizeof(char)) * (strlen(eq2) + 1));
  strcpy(name->eq2, eq2);
  name->score1 = score1;
  name->score2 = score2;
  if (ht_get(hashtable, key) != 1)
  {
    {
      printf("%d Jogo existente.\n", NL);
    }
  }
  else
  {
    if ((check_eq(hash_eq, eq1) == 1) || (check_eq(hash_eq, eq2) == 1))
    {
      {
        printf("%d Equipa inexistente.\n", NL);
      }
    }
    else
    {
      {
        if (score1 > score2)
        {
          {
            vit_handler(hash_eq, eq1);
          }
        }
        else
        {
          if (score1 < score2)
          {
            {
              vit_handler(hash_eq, eq2);
            }
          }
          else
          {
            
          }

        }

        ht_insert(hashtable, name);
        add_list2(ls, name);
      }
    }

  }

}

void l(int NL, list2 *ls)
{
  List *n;
  if (ls->head != 0)
  {
    {
      for (n = ls->head; n; n = n->next)
        printf("%d %s %s %s %d %d\n", NL, n->key, n->eq1, n->eq2, n->score1, n->score2);

    }
  }
  else
  {
    
  }

}

void p(int NL, HashTable *hashtable)
{
  char nome[1024];
  List *jogo;
  int i;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = hash(nome, hashtable->size);
  if (ht_get(hashtable, nome) == 1)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      for (jogo = hashtable->array[i]; jogo != 0; jogo = jogo->next)
        if (strcmp(jogo->key, nome) == 0)
      {
        break;
      }
      else
      {
        
      }


      printf("%d %s %s %s %d %d\n", NL, jogo->key, jogo->eq1, jogo->eq2, jogo->score1, jogo->score2);
    }
  }

}

void r(int NL, HashTable *hashtable, list2 *ls, HashTable2 *ht_eq)
{
  char nome[1024];
  int i;
  List *tmp;
  List *a;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  i = hash(nome, hashtable->size);
  if (ht_get(hashtable, nome) == 1)
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    {
      for (tmp = ls->head; tmp != 0; tmp = tmp->next)
        if (strcmp(tmp->key, nome) == 0)
      {
        break;
      }
      else
      {
        
      }


      if (tmp->previous == 0)
      {
        ls->head = tmp->next;
      }
      else
      {
        tmp->previous->next = tmp->next;
      }

      if (tmp->next == 0)
      {
        ls->last = tmp->previous;
      }
      else
      {
        tmp->next->previous = tmp->previous;
      }

      free_node(tmp);
      for (a = hashtable->array[i]; a != 0; a = a->next)
        if (strcmp(a->key, nome) == 0)
      {
        break;
      }
      else
      {
        
      }


      if (a->score1 > a->score2)
      {
        vit_handler_aux(ht_eq, a->eq1);
      }
      else
      {
        
      }

      if (a->score1 < a->score2)
      {
        vit_handler_aux(ht_eq, a->eq2);
      }
      else
      {
        
      }

      if (a == hashtable->array[i])
      {
        hashtable->array[i] = a->next;
      }
      else
      {
        a->previous->next = a->next;
      }

      free_node(a);
    }
  }

}

void s(int NL, HashTable *hashtable, HashTable2 *hash_eq, list2 *ls)
{
  char nome[1024];
  int score1;
  int score2;
  List *tmp;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  score1 = new_sym_var(sizeof(int) * 8);
  score2 = new_sym_var(sizeof(int) * 8);
  if (ht_get(hashtable, nome) == 1)
  {
    {
      printf("%d Jogo inexistente.\n", NL);
    }
  }
  else
  {
    {
      tmp = ht_lookup(hashtable, nome);
      if (tmp->score1 == tmp->score2)
      {
        {
          if (score1 > score2)
          {
            vit_handler(hash_eq, tmp->eq1);
          }
          else
          {
            if (score1 < score2)
            {
              vit_handler(hash_eq, tmp->eq2);
            }
            else
            {
              
            }

          }

        }
      }
      else
      {
        if (tmp->score1 > tmp->score2)
        {
          {
            if (score1 < score2)
            {
              {
                vit_handler(hash_eq, tmp->eq2);
                vit_handler_aux(hash_eq, tmp->eq1);
              }
            }
            else
            {
              if (score1 == score2)
              {
                vit_handler_aux(hash_eq, tmp->eq1);
              }
              else
              {
                
              }

            }

          }
        }
        else
        {
          if (tmp->score1 < tmp->score2)
          {
            {
              if (score1 > score2)
              {
                {
                  vit_handler(hash_eq, tmp->eq1);
                  vit_handler_aux(hash_eq, tmp->eq2);
                }
              }
              else
              {
                if (score1 == score2)
                {
                  vit_handler_aux(hash_eq, tmp->eq2);
                }
                else
                {
                  
                }

              }

            }
          }
          else
          {
            
          }

        }

      }

      score_handler(hashtable, nome, score1, score2);
      list2_handler(ls, nome, score1, score2);
    }
  }

}

