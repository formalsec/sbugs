/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"


int hash(char *v)
{
  int h;
  int a = 31415;
  int b = 27183;
  for (h = 0; (*v) != '\0'; v++, a = (a * b) % (607 - 1))
    h = ((a * h) + (*v)) % 607;

  return h;
}

node_htable_equipas **init_hash_equipas()
{
  int i;
  node_htable_equipas **hashtable_equipas;
  hashtable_equipas = malloc((sizeof(node_htable_equipas)) * 607);
  for (i = 0; i < 607; i++)
    hashtable_equipas[i] = 0;

  return hashtable_equipas;
}

lista_ligada_equipas *init_lista_ligada_e()
{
  lista_ligada_equipas *lista_ligada;
  lista_ligada = malloc(sizeof(lista_ligada_equipas));
  lista_ligada->equipa = malloc(sizeof(equipa *));
  lista_ligada = 0;
  return lista_ligada;
}

equipa *cria_equipa(char *nome_equipa)
{
  equipa *equipa_new = malloc(sizeof(equipa));
  equipa_new->nome_equipa = malloc((sizeof(char *)) * (strlen(nome_equipa) + 1));
  equipa_new->jogos_ganhos = 0;
  strcpy(equipa_new->nome_equipa, nome_equipa);
  return equipa_new;
}

node_htable_equipas *adiciona_a_lista_equipas(node_htable_equipas *pt_lista, equipa *equipa)
{
  node_htable_equipas *new = malloc(sizeof(node_htable_equipas));
  new->equipa = equipa;
  new->next = pt_lista;
  return new;
}

lista_ligada_equipas **adiciona_a_lista_ligada_e(equipa *equipa_new, lista_ligada_equipas **lista_ligada)
{
  lista_ligada_equipas *new_node;
  lista_ligada_equipas *node_aux;
  lista_ligada_equipas *ultimo = *lista_ligada;
  new_node = malloc(sizeof(lista_ligada_equipas));
  new_node->equipa = equipa_new;
  new_node->next = 0;
  if ((*lista_ligada) == 0)
  {
    *lista_ligada = new_node;
    return lista_ligada;
  }
  else
  {
    
  }

  if (strcmp(ultimo->equipa->nome_equipa, equipa_new->nome_equipa) > 0)
  {
    new_node->next = ultimo;
    *lista_ligada = new_node;
    return lista_ligada;
  }
  else
  {
    
  }

  if (ultimo->next == 0)
  {
    ultimo->next = new_node;
    return lista_ligada;
  }
  else
  {
    
  }

  while ((ultimo->next != 0) && (strcmp(ultimo->next->equipa->nome_equipa, equipa_new->nome_equipa) < 0))
  {
    ultimo = ultimo->next;
  }

  node_aux = ultimo->next;
  ultimo->next = new_node;
  new_node->next = node_aux;
  return lista_ligada;
}

equipa *procura_equipa_aux(char *nome_equipa, node_htable_equipas **entrada_hash)
{
  long hash_index;
  node_htable_equipas *lista_equipas;
  hash_index = hash(nome_equipa);
  lista_equipas = entrada_hash[hash_index];
  while ((lista_equipas != 0) && (strcmp(lista_equipas->equipa->nome_equipa, nome_equipa) != 0))
  {
    lista_equipas = lista_equipas->next;
  }

  if (lista_equipas == 0)
  {
    return 0;
  }
  else
  {
    
  }

  return lista_equipas->equipa;
}

