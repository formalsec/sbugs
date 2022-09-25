/*File generated by PreProcessor.py*/


#include "equipas.h"
#include "jogos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void alphasort(char **nomes, int count)
{
  int i;
  int j;
  char *temp;
  count--;
  for (i = 0; i <= count; i++)
  {
    for (j = i + 1; j <= count; j++)
    {
      if (strcmp(nomes[i], nomes[j]) > 0)
      {
        temp = malloc((sizeof(char)) * (strlen(nomes[i]) + 1));
        strcpy(temp, nomes[i]);
        nomes[i] = realloc(nomes[i], strlen(nomes[j]) + 1);
        strcpy(nomes[i], nomes[j]);
        nomes[j] = realloc(nomes[j], strlen(temp) + 1);
        strcpy(nomes[j], temp);
        free(temp);
      }
      else
      {
        
      }

    }

  }

}

int hash(char *string, int capacity)
{
  int h = 0;
  int a = 127;
  for (; (*string) != '\0'; string++)
    h = ((a * h) + (*string)) % capacity;

  return h;
}

int checkins(char *equipa, hashtable_equipas *h_equipas, int hash)
{
  hash_node_equipas *checker;
  for (checker = h_equipas->tb[hash]; checker != 0; checker = checker->next)
    if (strcmp(checker->pointer->equipa, equipa) == 0)
  {
    return 0;
  }
  else
  {
    
  }


  return 1;
}

hashtable_equipas *mk_hash_table_e()
{
  hashtable_equipas *hash_equipas = malloc(sizeof(hashtable_equipas));
  hash_equipas->capacity = 1031;
  hash_equipas->tb = calloc(hash_equipas->capacity, sizeof(hash_node_equipas *));
  return hash_equipas;
}

hash_node_equipas *make_hashnode_e(hash_node_equipas *head, node_equipas *node)
{
  hash_node_equipas *hashnode_equipas = malloc(sizeof(hash_node_equipas));
  hashnode_equipas->next = head;
  hashnode_equipas->pointer = node;
  head = hashnode_equipas;
  return head;
}

node_equipas *make_node_e(char *equipa, node_equipas *n_equipas)
{
  node_equipas *new_node = malloc(sizeof(node_equipas));
  new_node->next = n_equipas;
  new_node->equipa = malloc((sizeof(char)) * (strlen(equipa) + 1));
  strcpy(new_node->equipa, equipa);
  new_node->pontos = 0;
  n_equipas = new_node;
  return n_equipas;
}

void lib_espaco_equipas(node_equipas *n_equipas, hashtable_equipas *h_equipas)
{
  hash_node_equipas *tmp2;
  size_t i;
  node_equipas *tmp;
  while (n_equipas != 0)
  {
    tmp = n_equipas;
    n_equipas = n_equipas->next;
    free(tmp->equipa);
    free(tmp);
  }

  for (i = 0; i < h_equipas->capacity; i++)
  {
    while (h_equipas->tb[i])
    {
      tmp2 = h_equipas->tb[i]->next;
      free(h_equipas->tb[i]);
      h_equipas->tb[i] = tmp2;
    }

  }

  free(h_equipas->tb);
  free(h_equipas);
}

node_equipas *A(int NL, node_equipas *n_equipas, hashtable_equipas *h_equipas)
{
  char equipa[1024];
  int hash_e;
  getchar();
  for (int equipa_index = 0; equipa_index < 10; equipa_index++)
  {
    equipa[equipa_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa[10 - 1] = '\0';
  hash_e = hash(equipa, h_equipas->capacity);
  if (checkins(equipa, h_equipas, hash_e))
  {
    n_equipas = make_node_e(equipa, n_equipas);
    h_equipas->tb[hash_e] = make_hashnode_e(h_equipas->tb[hash_e], n_equipas);
  }
  else
  {
    printf("%d Equipa existente.\n", NL);
  }

  return n_equipas;
}

void P(int NL, hashtable_equipas *h_equipas)
{
  char equipa[1024];
  int hash_e;
  hash_node_equipas *checker;
  getchar();
  for (int equipa_index = 0; equipa_index < 10; equipa_index++)
  {
    equipa[equipa_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa[10 - 1] = '\0';
  hash_e = hash(equipa, h_equipas->capacity);
  if (checkins(equipa, h_equipas, hash_e))
  {
    printf("%d Equipa inexistente.\n", NL);
  }
  else
  {
    for (checker = h_equipas->tb[hash_e]; checker != 0; checker = checker->next)
      if (strcmp(checker->pointer->equipa, equipa) == 0)
    {
      printf("%d %s %d\n", NL, checker->pointer->equipa, checker->pointer->pontos);
    }
    else
    {
      
    }


  }

}

void g(int NL, hashtable_equipas *h_equipas)
{
  size_t i;
  char **equipas;
  hash_node_equipas *checker;
  int MAX = -1;
  int contador = 0;
  int x = 0;
  int y;
  for (i = 0; i < h_equipas->capacity; i++)
  {
    for (checker = h_equipas->tb[i]; checker != 0; checker = checker->next)
    {
      if (checker->pointer->pontos > MAX)
      {
        MAX = checker->pointer->pontos;
        contador = 1;
      }
      else
      {
        if (checker->pointer->pontos == MAX)
        {
          contador++;
        }
        else
        {
          
        }

      }

    }

  }

  if (MAX != (-1))
  {
    equipas = malloc((sizeof(char *)) * (contador + 1));
    for (i = 0; i < h_equipas->capacity; i++)
    {
      for (checker = h_equipas->tb[i]; checker != 0; checker = checker->next)
      {
        if (checker->pointer->pontos == MAX)
        {
          *(equipas + x) = malloc((sizeof(char)) * (strlen(checker->pointer->equipa) + 1));
          strcpy(*(equipas + x), checker->pointer->equipa);
          x++;
        }
        else
        {
          
        }

      }

    }

    *(equipas + x) = '\0';
    printf("%d Melhores %d\n", NL, MAX);
    alphasort(equipas, contador);
    for (y = 0; y < contador; y++)
    {
      printf("%d * %s\n", NL, equipas[y]);
      free(equipas[y]);
    }

    free(equipas);
  }
  else
  {
    
  }

}

