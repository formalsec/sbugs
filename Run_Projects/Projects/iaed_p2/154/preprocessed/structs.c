/*File generated by PreProcessor.py*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "structs.h"
#include "comandos.h"


unsigned int hash_function(char *nome)
{
  int comprimento = strlen(nome);
  unsigned int valor = 0;
  int i;
  for (i = 0; i < comprimento; i++)
  {
    valor = valor + nome[i];
    valor = (valor * nome[i]) % 10000;
  }

  return valor;
}

void iniciar_hash_table(game_n **hash_table)
{
  int i;
  for (i = 0; i < 10000; i++)
  {
    hash_table[i] = 0;
  }

}

void inserir_hash_table(game_n **hash_table, game_n *novo)
{
  int id = 0;
  if (novo == 0)
  {
    return;
  }
  else
  {
    
  }

  id = hash_function(novo->nome);
  novo->next = hash_table[id];
  hash_table[id] = novo;
}

void free_hash_table(game_n **hash_table)
{
  int i = 0;
  game_n *t = 0;
  game_n *anterior = 0;
  for (i = 0; i < 10000; i++)
  {
    if (hash_table[i] != 0)
    {
      t = hash_table[i];
      while (t != 0)
      {
        anterior = t;
        free(anterior->nome);
        free(anterior->equipa1);
        free(anterior->equipa2);
        t = anterior->next;
        free(anterior);
      }

    }
    else
    {
      
    }

  }

}

void iniciar_hash_teams(team_n **hash_teams)
{
  int i;
  for (i = 0; i < 10000; i++)
  {
    hash_teams[i] = 0;
  }

}

void inserir_hash_teams(team_n **hash_teams, team_n *novo)
{
  int id = 0;
  if (novo == 0)
  {
    return;
  }
  else
  {
    
  }

  id = hash_function(novo->name);
  novo->next = hash_teams[id];
  hash_teams[id] = novo;
}

void free_hash_teams(team_n **hash_teams)
{
  int i = 0;
  team_n *t = 0;
  team_n *anterior = 0;
  for (i = 0; i < 10000; i++)
  {
    if (hash_teams[i] != 0)
    {
      t = hash_teams[i];
      while (t != 0)
      {
        anterior = t;
        free(anterior->name);
        t = anterior->next;
        free(anterior);
      }

    }
    else
    {
      
    }

  }

}

game_n *inserir_na_head(game_n *head, game_n *novo)
{
  novo->lista = head;
  return novo;
}

team_n *inserir_na_head_teams(team_n *head, team_n *novo)
{
  novo->lista = head;
  return novo;
}

void free_jogo(game_n *t)
{
  free(t->nome);
  free(t->equipa1);
  free(t->equipa2);
  free(t);
}

void free_equipa(team_n *t)
{
  free(t->name);
  free(t);
}
