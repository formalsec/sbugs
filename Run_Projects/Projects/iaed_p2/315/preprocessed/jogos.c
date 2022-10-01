/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogos.h"


jogo cria_jogo(char *nome1, char *nome_equipa1, char *nome_equipa2, int score_jogo[2])
{
  jogo new;
  new.nome = malloc((sizeof(char)) * (strlen(nome1) + 1));
  strcpy(new.nome, nome1);
  new.equipa1 = malloc((sizeof(char)) * (strlen(nome_equipa1) + 1));
  strcpy(new.equipa1, nome_equipa1);
  new.equipa2 = malloc((sizeof(char)) * (strlen(nome_equipa2) + 1));
  strcpy(new.equipa2, nome_equipa2);
  new.score0 = score_jogo[0];
  new.score1 = score_jogo[1];
  return new;
}

no_jogo cria_no_jogo(jogo novo_jogo)
{
  no_jogo novo = malloc(sizeof(struct stru_no_jogo));
  novo->next = 0;
  novo->prev = 0;
  novo->game = novo_jogo;
  return novo;
}

node_jogo cria_node_jogo()
{
  node_jogo novo = malloc(sizeof(struct node_jogos));
  novo->next = 0;
  novo->prev = 0;
  return novo;
}

void insert_end_list_jogos(lista_jogos *jogos, jogo novo_jogo)
{
  no_jogo node;
  if (jogos->head == 0)
  {
    node = cria_no_jogo(novo_jogo);
    node->prev = 0;
    jogos->head = node;
    jogos->last = node;
  }
  else
  {
    node = cria_no_jogo(novo_jogo);
    jogos->last->next = node;
    node->prev = jogos->last;
    jogos->last = node;
  }

}

node_jogo insert_inicio_jogos(node_jogo head)
{
  node_jogo novo = cria_node_jogo();
  if (head != 0)
  {
    head->prev = novo;
  }
  else
  {
    
  }

  novo->next = head;
  return novo;
}

void remove_jogo(no_jogo no)
{
  libertar_jogo(no->game);
  if (no->prev == 0)
  {
    no->game.nome = 0;
  }
  else
  {
    if (no->next == 0)
    {
      no->prev->next = 0;
      free(no);
    }
    else
    {
      no->prev->next = no->next;
      no->next->prev = no->prev;
      free(no);
    }

  }

}

node_jogo search_list_jogos(node_jogo head, char *nome_jogo)
{
  node_jogo aux;
  for (aux = head; aux != 0; aux = aux->next)
    if (strcmp(aux->no_j->game.nome, nome_jogo) == 0)
  {
    return aux;
  }
  else
  {
    
  }


  return 0;
}

hash_table_jogos init_hash_table_jogos(int lim)
{
  int i;
  hash_table_jogos hash_table = malloc(sizeof(struct stru_hash_jogos));
  hash_table->cap = lim;
  hash_table->table = malloc(lim * (sizeof(node_jogo)));
  for (i = 0; i < lim; i++)
    hash_table->table[i] = 0;

  return hash_table;
}

void hash_insert_jogos(hash_table_jogos hash_table, char *nome)
{
  int h;
  h = hash(nome, hash_table->cap);
  if (hash_table->table[h] == 0)
  {
    hash_table->table[h] = cria_node_jogo();
  }
  else
  {
    hash_table->table[h] = insert_inicio_jogos(hash_table->table[h]);
  }

}

node_jogo hash_search_jogos(hash_table_jogos hash_table, char *nome)
{
  int h;
  h = hash(nome, hash_table->cap);
  return search_list_jogos(hash_table->table[h], nome);
}

void remove_jogos(hash_table_jogos table_jogo, node_jogo node)
{
  int h;
  h = hash(node->no_j->game.nome, table_jogo->cap);
  remove_jogo(node->no_j);
  if (node->prev == 0)
  {
    if (node->next == 0)
    {
      table_jogo->table[h] = 0;
    }
    else
    {
      table_jogo->table[h] = node->next;
      table_jogo->table[h]->prev = 0;
    }

  }
  else
  {
    if (node->next == 0)
    {
      node->prev->next = 0;
    }
    else
    {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }

  }

  free(node);
}

void libertar_jogo(jogo game)
{
  free(game.nome);
  free(game.equipa1);
  free(game.equipa2);
}

void libertar_lista_hash(node_jogo head)
{
  node_jogo aux;
  while (head != 0)
  {
    aux = head;
    head = head->next;
    remove_jogo(aux->no_j);
    free(aux);
  }

}

void libertar_hash_jogos(hash_table_jogos hash_table)
{
  int i;
  for (i = 0; i < hash_table->cap; i++)
    if (hash_table->table[i] != 0)
  {
    libertar_lista_hash(hash_table->table[i]);
  }
  else
  {
    
  }


  free(hash_table->table);
  free(hash_table);
}
