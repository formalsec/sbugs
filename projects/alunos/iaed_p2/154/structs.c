#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* inclusao dos header files necessarios */
#include "structs.h"
#include "comandos.h"


/*------------------------------------------------------------------------------
1 - hash function - escolhe aleatoriamente um indice dado um nome
------------------------------------------------------------------------------*/

unsigned int hash_function(char *nome){
  int comprimento = strlen(nome);
  unsigned int valor = 0;
  int i;
  for (i = 0; i < comprimento; i++){
    valor = valor + nome[i];
    valor = (valor * nome[i]) % TABLE_SIZE;
  }
  /* o valor retornado esta sempre entre 0 e a TABLE_SIZE - congruencia */
  return valor;
} 




/*------------------------------------------------------------------------------
2 - funcoes relacionadas com a hash table dos jogos
------------------------------------------------------------------------------*/

/* inicializacao da hash_table */
void iniciar_hash_table(game_n **hash_table){
  int i;
  for (i = 0; i < TABLE_SIZE; i++){
    /* inicializa todas as entradas da hash table a NULL */
    hash_table[i] = NULL;
  }
}

/* insere na hash table consoante o indice da hash_function */
void inserir_hash_table(game_n **hash_table, game_n *novo){
  int id = 0;
  if (novo == NULL){
    return;
  }
  /* calculo do indice onde vai ser introduzido */
  id = hash_function(novo->nome);
  novo->next = hash_table[id];
  hash_table[id] = novo;
}

/* free na hash_table no fim do programa */
void free_hash_table(game_n **hash_table){
  int i = 0;
  game_n *t = NULL;
  game_n *anterior = NULL;
  for (i = 0; i < TABLE_SIZE; i++){
    if (hash_table[i] != NULL){
      t = hash_table[i];
      while (t != NULL){
        anterior = t;
        free(anterior->nome);
        free(anterior->equipa1);
        free(anterior->equipa2);
        t = anterior->next;
        free(anterior);
      }
    }
  }
}




/*------------------------------------------------------------------------------
3 - funcoes relacionadas com a hash table das equipas
------------------------------------------------------------------------------*/

/* iniciaizacao da hash table */
void iniciar_hash_teams(team_n **hash_teams){
  int i;
  for (i = 0; i < TABLE_SIZE; i++){
    /* inicializacao de todas as entradas da hash table das equipas a NULL */
    hash_teams[i] = NULL;
  }
}

/* insere na hash table consoante o valor do indice da hash_function */
void inserir_hash_teams(team_n **hash_teams, team_n *novo){
  int id = 0;
  if (novo == NULL){
    return;
  }
  /* calculo o indice da hash table e colocacao */
  id = hash_function(novo->name);
  novo->next = hash_teams[id];
  hash_teams[id] = novo;
}

/* free na hash table das equipas no fim do programa */
void free_hash_teams(team_n **hash_teams){
  int i = 0;
  team_n *t = NULL;
  team_n *anterior = NULL;
  for (i = 0; i < TABLE_SIZE; i++){
    if (hash_teams[i] != NULL){
      t = hash_teams[i];
      while (t != NULL){
        anterior = t;
        free(anterior->name);
        t = anterior->next;
        free(anterior);
      }
    }
  }
}




/*------------------------------------------------------------------------------
4 - funcoes relacionadas com a linked list dos jogos
------------------------------------------------------------------------------*/

/* insere na cabeca da linked list um novo jogo */
game_n *inserir_na_head(game_n *head, game_n *novo){
  novo->lista = head;
  return novo;
}




/*------------------------------------------------------------------------------
5 - funcoes relacionadas com a linked list das equipas
------------------------------------------------------------------------------*/

/* insere na cabeca da linked list das equipas uma nova equipa */
team_n *inserir_na_head_teams(team_n *head, team_n *novo){
  novo->lista = head;
  return novo;
}



/*------------------------------------------------------------------------------
6 - funcoes de free de um no
------------------------------------------------------------------------------*/

/* free a um jogo */
void free_jogo(game_n *t){
  free(t->nome);
  free(t->equipa1);
  free(t->equipa2);
  free(t);
}

/* free a um no equipa quando nao necessario */
void free_equipa(team_n *t){
  free(t->name);
  free(t);
}
