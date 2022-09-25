/*File generated by PreProcessor.py*/


#include "equipas.h"
#include "jogos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int checkins_j(char *jogo, hashtable_jogos *h_jogos, int hash)
{
  hash_node_jogos *checker;
  for (checker = h_jogos->tb[hash]; checker != 0; checker = checker->next)
    if (strcmp(checker->pointer->jogo, jogo) == 0)
  {
    return 0;
  }
  else
  {
    
  }


  return 1;
}

void altera_v(hashtable_equipas *h_equipas, char *equipa, int hash)
{
  hash_node_equipas *checker;
  for (checker = h_equipas->tb[hash]; checker != 0; checker = checker->next)
    if (strcmp(checker->pointer->equipa, equipa) == 0)
  {
    checker->pointer->pontos++;
  }
  else
  {
    
  }


}

void altera_v2(hashtable_equipas *h_equipas, char *equipa, int hash)
{
  hash_node_equipas *checker;
  for (checker = h_equipas->tb[hash]; checker != 0; checker = checker->next)
    if (strcmp(checker->pointer->equipa, equipa) == 0)
  {
    checker->pointer->pontos--;
  }
  else
  {
    
  }


}

hashtable_jogos *mk_hash_table_j()
{
  hashtable_jogos *hash_jogos = malloc(sizeof(hashtable_jogos));
  hash_jogos->capacity = 1031;
  hash_jogos->tb = calloc(hash_jogos->capacity, sizeof(hash_node_jogos *));
  return hash_jogos;
}

hash_node_jogos *make_hashnode_j(hash_node_jogos *head, node_jogos *node)
{
  hash_node_jogos *hashnode_jogos = malloc(sizeof(hash_node_jogos));
  hashnode_jogos->next = head;
  hashnode_jogos->pointer = node;
  head = hashnode_jogos;
  return head;
}

lista_jogos *mk_list()
{
  lista_jogos *jogos = malloc(sizeof(lista_jogos));
  jogos->head = (jogos->last = 0);
  return jogos;
}

void make_node_j(char *jogo, char *equipa1, char *equipa2, int sc1, int sc2, lista_jogos *jogos)
{
  node_jogos *new_node = malloc(sizeof(node_jogos));
  new_node->previous = jogos->last;
  new_node->next = 0;
  new_node->equipa1 = malloc((sizeof(char)) * (strlen(equipa1) + 1));
  strcpy(new_node->equipa1, equipa1);
  new_node->equipa2 = malloc((sizeof(char)) * (strlen(equipa2) + 1));
  strcpy(new_node->equipa2, equipa2);
  new_node->jogo = malloc((sizeof(char)) * (strlen(jogo) + 1));
  strcpy(new_node->jogo, jogo);
  new_node->sc1 = sc1;
  new_node->sc2 = sc2;
  if (jogos->last)
  {
    jogos->last->next = new_node;
  }
  else
  {
    jogos->head = new_node;
  }

  jogos->last = new_node;
}

void free_node(node_jogos *n)
{
  free(n->jogo);
  free(n->equipa1);
  free(n->equipa2);
  free(n);
}

void free_list(lista_jogos *l)
{
  while (l->head)
  {
    node_jogos *tmp = l->head->next;
    free_node(l->head);
    l->head = tmp;
  }

  free(l);
}

void lib_espaco_jogos(hashtable_jogos *h_jogos)
{
  hash_node_jogos *tmp2;
  size_t i;
  for (i = 0; i < h_jogos->capacity; i++)
  {
    while (h_jogos->tb[i])
    {
      tmp2 = h_jogos->tb[i]->next;
      free(h_jogos->tb[i]);
      h_jogos->tb[i] = tmp2;
    }

  }

  free(h_jogos->tb);
  free(h_jogos);
}

void a(int NL, lista_jogos *jogos, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas)
{
  char equipa1[1024];
  char equipa2[1024];
  char jogo[1024];
  int hash_j;
  int hash_e1;
  int hash_e2;
  int sc1;
  int sc2;
  getchar();
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  for (int equipa1_index = 0; equipa1_index < 10; equipa1_index++)
  {
    equipa1[equipa1_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa1[10 - 1] = '\0';
  for (int equipa2_index = 0; equipa2_index < 10; equipa2_index++)
  {
    equipa2[equipa2_index] = new_sym_var(sizeof(char) * 8);
  }

  equipa2[10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  hash_j = hash(jogo, h_jogos->capacity);
  hash_e1 = hash(equipa1, h_equipas->capacity);
  hash_e2 = hash(equipa2, h_equipas->capacity);
  if (!checkins_j(jogo, h_jogos, hash_j))
  {
    printf("%d Jogo existente.\n", NL);
  }
  else
  {
    if (checkins(equipa1, h_equipas, hash_e1) | checkins(equipa2, h_equipas, hash_e2))
    {
      printf("%d Equipa inexistente.\n", NL);
    }
    else
    {
      make_node_j(jogo, equipa1, equipa2, sc1, sc2, jogos);
      h_jogos->tb[hash_j] = make_hashnode_j(h_jogos->tb[hash_j], jogos->last);
      if (sc1 > sc2)
      {
        altera_v(h_equipas, equipa1, hash_e1);
      }
      else
      {
        
      }

      if (sc2 > sc1)
      {
        altera_v(h_equipas, equipa2, hash_e2);
      }
      else
      {
        
      }

    }

  }

}

void l(int NL, lista_jogos *jogos)
{
  node_jogos *checker;
  for (checker = jogos->head; checker; checker = checker->next)
    printf("%d %s %s %s %d %d\n", NL, checker->jogo, checker->equipa1, checker->equipa2, checker->sc1, checker->sc2);

}

void p(int NL, hashtable_jogos *h_jogos)
{
  char jogo[1024];
  int hash_j;
  hash_node_jogos *checker;
  getchar();
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  hash_j = hash(jogo, h_jogos->capacity);
  if (checkins_j(jogo, h_jogos, hash_j))
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    for (checker = h_jogos->tb[hash_j]; checker != 0; checker = checker->next)
      if (strcmp(checker->pointer->jogo, jogo) == 0)
    {
      printf("%d %s %s %s %d %d\n", NL, checker->pointer->jogo, checker->pointer->equipa1, checker->pointer->equipa2, checker->pointer->sc1, checker->pointer->sc2);
    }
    else
    {
      
    }


  }

}

void s(int NL, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas)
{
  char jogo[1024];
  int hash_j;
  int sc1;
  int sc2;
  int hash_e1;
  int hash_e2;
  hash_node_jogos *checker;
  getchar();
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  sc1 = new_sym_var(sizeof(int) * 8);
  sc2 = new_sym_var(sizeof(int) * 8);
  hash_j = hash(jogo, h_jogos->capacity);
  if (checkins_j(jogo, h_jogos, hash_j))
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    for (checker = h_jogos->tb[hash_j]; checker != 0; checker = checker->next)
      if (strcmp(checker->pointer->jogo, jogo) == 0)
    {
      hash_e1 = hash(checker->pointer->equipa1, h_equipas->capacity);
      hash_e2 = hash(checker->pointer->equipa2, h_equipas->capacity);
      if (checker->pointer->sc1 > checker->pointer->sc2)
      {
        altera_v2(h_equipas, checker->pointer->equipa1, hash_e1);
      }
      else
      {
        
      }

      if (checker->pointer->sc2 > checker->pointer->sc1)
      {
        altera_v2(h_equipas, checker->pointer->equipa2, hash_e2);
      }
      else
      {
        
      }

      checker->pointer->sc1 = sc1;
      checker->pointer->sc2 = sc2;
      if (checker->pointer->sc1 > checker->pointer->sc2)
      {
        altera_v(h_equipas, checker->pointer->equipa1, hash_e1);
      }
      else
      {
        
      }

      if (checker->pointer->sc2 > checker->pointer->sc1)
      {
        altera_v(h_equipas, checker->pointer->equipa2, hash_e2);
      }
      else
      {
        
      }

    }
    else
    {
      
    }


  }

}

void r(int NL, lista_jogos *jogos, hashtable_jogos *h_jogos, hashtable_equipas *h_equipas)
{
  char jogo[1024];
  int hash_j;
  int hash_e1;
  int hash_e2;
  hash_node_jogos *checker;
  hash_node_jogos *previous;
  getchar();
  for (int jogo_index = 0; jogo_index < 10; jogo_index++)
  {
    jogo[jogo_index] = new_sym_var(sizeof(char) * 8);
  }

  jogo[10 - 1] = '\0';
  hash_j = hash(jogo, h_jogos->capacity);
  if (checkins_j(jogo, h_jogos, hash_j))
  {
    printf("%d Jogo inexistente.\n", NL);
  }
  else
  {
    for (checker = h_jogos->tb[hash_j]; checker != 0; checker = checker->next)
    {
      if (strcmp(checker->pointer->jogo, jogo) == 0)
      {
        break;
      }
      else
      {
        
      }

      previous = checker;
    }

    hash_e1 = hash(checker->pointer->equipa1, h_equipas->capacity);
    hash_e2 = hash(checker->pointer->equipa2, h_equipas->capacity);
    if (checker->pointer->sc1 > checker->pointer->sc2)
    {
      altera_v2(h_equipas, checker->pointer->equipa1, hash_e1);
    }
    else
    {
      
    }

    if (checker->pointer->sc2 > checker->pointer->sc1)
    {
      altera_v2(h_equipas, checker->pointer->equipa2, hash_e2);
    }
    else
    {
      
    }

    if (checker->pointer->previous == 0)
    {
      jogos->head = checker->pointer->next;
    }
    else
    {
      checker->pointer->previous->next = checker->pointer->next;
    }

    if (checker->pointer->next == 0)
    {
      jogos->last = checker->pointer->previous;
    }
    else
    {
      checker->pointer->next->previous = checker->pointer->previous;
    }

    free_node(checker->pointer);
    if (checker == h_jogos->tb[hash_j])
    {
      h_jogos->tb[hash_j] = checker->next;
      free(checker);
      return;
    }
    else
    {
      
    }

    previous->next = checker->next;
    free(checker);
  }

}

