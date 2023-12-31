#include "/home/fmarques/sbugs/projects/alunos/lib/stubs.h"
/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eq.h"
#include "j.h"


unsigned int hash(const char *key, unsigned int size)
{
  unsigned int hash;
  unsigned int i;
  hash = 0;
  i = 0;
  while (key && key[i])
  {
    hash = (hash + key[i]) % size;
    ++i;
  }

  return hash;
}

HashTable2 *ht_create_eq()
{
  HashTable2 *ht = malloc(sizeof(HashTable2));
  ht->size = 1013;
  ht->array = calloc(ht->size, sizeof(equipa *));
  return ht;
}

int vit_handler_aux(HashTable2 *hashtable, char *nome)
{
  unsigned int i = hash(nome, hashtable->size);
  equipa *tmp = hashtable->array[i];
  while (tmp != 0)
  {
    if (strcmp(tmp->nome, nome) == 0)
    {
      break;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  tmp->vitoria = tmp->vitoria - 1;
  return 0;
}

int vit_handler(HashTable2 *hashtable, char *nome)
{
  unsigned int i = hash(nome, hashtable->size);
  equipa *tmp = hashtable->array[i];
  while (tmp != 0)
  {
    if (strcmp(tmp->nome, nome) == 0)
    {
      break;
    }
    else
    {
      
    }

    tmp = tmp->next;
  }

  tmp->vitoria = tmp->vitoria + 1;
  return 0;
}

equipa *ht_lookup_eq(HashTable2 *hashtable, const char *key)
{
  unsigned int i = hash(key, hashtable->size);
  equipa *tmp = hashtable->array[i];
  while ((tmp != 0) && (strcmp(tmp->nome, key) != 0))
  {
    tmp = tmp->next;
  }

  return tmp;
}

int ht_insert_eq(HashTable2 *hashtable, equipa *eq)
{
  unsigned int i;
  i = hash(eq->nome, hashtable->size);
  if (eq == 0)
  {
    return 1;
  }
  else
  {
    
  }

  eq->next = hashtable->array[i];
  hashtable->array[i] = eq;
  return 0;
}

int check_eq(HashTable2 *hashtable, const char *nome)
{
  int i = hash(nome, hashtable->size);
  equipa *m;
  for (m = hashtable->array[i]; m != 0; m = m->next)
  {
    if (strcmp(m->nome, nome) == 0)
    {
      return 0;
    }
    else
    {
      
    }

  }

  return 1;
}

void free_eq(equipa *eq)
{
  free(eq->nome);
  free(eq);
}

void free_hash_table_e(HashTable2 *ht)
{
  equipa *a;
  size_t i;
  for (i = 0; i < ht->size; i++)
  {
    while (ht->array[i])
    {
      a = ht->array[i]->next;
      free(ht->array[i]);
      ht->array[i] = a;
    }

  }

  free(ht->array);
  free(ht);
}

void A(int NL, HashTable2 *hashtable)
{
  char nome[1024];
  equipa *eq = malloc(sizeof(equipa));
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (check_eq(hashtable, nome) == 0)
  {
    printf("%d Equipa existente.\n", NL);
  }
  else
  {
    eq->nome = malloc((sizeof(char)) * (strlen(nome) + 1));
    strcpy(eq->nome, nome);
    eq->vitoria = 0;
    ht_insert_eq(hashtable, eq);
  }

}

void P(int NL, HashTable2 *hashtable)
{
  char nome[1024];
  equipa *eq;
  getchar();
  for (int nome_index = 0; nome_index < 10; nome_index++)
  {
    nome[nome_index] = new_sym_var(sizeof(char) * 8);
  }

  nome[10 - 1] = '\0';
  if (check_eq(hashtable, nome) == 1)
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    eq = ht_lookup_eq(hashtable, nome);
    printf("%d %s %d\n", NL, eq->nome, eq->vitoria);
  }

}

void g(int NL, HashTable2 *hashtable)
{
  equipa *m;
  size_t i;
  char **tab;
  char *tmp;
  int x;
  int y;
  int cont;
  int j = -1;
  int k = 0;
  for (i = 0; i < hashtable->size; i++)
  {
    for (m = hashtable->array[i]; m != 0; m = m->next)
    {
      if (m->vitoria > j)
      {
        j = m->vitoria;
        cont = 1;
      }
      else
      {
        if (m->vitoria == j)
        {
          cont++;
        }
        else
        {
          
        }

      }

    }

  }

  if (j == (-1))
  {
    return;
  }
  else
  {
    
  }

  tab = malloc((sizeof(char *)) * (cont + 1));
  for (i = 0; i < hashtable->size; i++)
  {
    for (m = hashtable->array[i]; m != 0; m = m->next)
    {
      if (m->vitoria == j)
      {
        tab[k] = malloc((sizeof(char)) * (strlen(m->nome) + 1));
        strcpy(tab[k], m->nome);
        k++;
      }
      else
      {
        
      }

    }

  }

  for (x = 0; x <= (cont - 1); x++)
  {
    for (y = x + 1; y <= (cont - 1); y++)
    {
      if (strcmp(tab[x], tab[y]) > 0)
      {
        tmp = malloc((sizeof(char)) * (strlen(tab[x]) + 1));
        strcpy(tmp, tab[x]);
        tab[x] = realloc(tab[x], strlen(tab[y]) + 1);
        strcpy(tab[x], tab[y]);
        tab[y] = realloc(tab[y], strlen(tmp) + 1);
        strcpy(tab[y], tmp);
        free(tmp);
      }
      else
      {
        
      }

    }

  }

  printf("%d Melhores %d\n", NL, j);
  for (x = 0; x < cont; x++)
    printf("%d * %s\n", NL, tab[x]);

  for (x = 0; x < cont; x++)
    free(tab[x]);

  free(tab);
}

