#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "teams_struct.h"
#include "games_struct.h"

#define MAX_STR 1024  /* Tamanho maximo de cada string */
#define T_HASH 10000  /* Tamanho da hash table */


/* Inicializa uma estrutura l_game */
l_game* init_game_list(){
	l_game *game_list;
	game_list = can_fail_malloc(sizeof(l_game));
	game_list->head = NULL;
	game_list->last = NULL;
	return game_list;
}

/* Liberta espaco alocado para a lista duplamente ligada dos jogos */
void destroy_game_list(l_game *game_list){
	while(game_list->head){
		delete_game(game_list->head, game_list);
	}
	free(game_list);
}

/* Inicializa uma hash table de jogos */
game_link** init_hash_games(){
	int i;
	game_link** hash_games;
	hash_games = can_fail_malloc(sizeof(game_link) * T_HASH);
	for(i = 0; i < T_HASH; i++)
		hash_games[i] = NULL;
	return hash_games;
}

/* Numa certa key da hash table coloca um link na cabeca e liga-o ao antigo */
game_link* insert_beguin_hash_game(game_link *head, game_node *game){
	game_link *new_head = can_fail_malloc(sizeof(link_t));
	new_head->link = game;
	new_head->next = head;
	return new_head;
}

/* Coloca um jogo na hash table */
void insert_hash_game(game_link **hash_games, game_node *game){
	int key = hashU(game->game_name, T_HASH);
	game_link *new_head = insert_beguin_hash_game(hash_games[key], game);
	hash_games[key] = new_head; /* Ponteiro fica a apontar para a nova cabeca */
}

/* Retorna o ponteiro que aponta para o nome do jogo de input (retorna NULL se a equipa nao existir) */
game_node* search_game(game_link **hash_games, char *name){
	int key = hashU(name, T_HASH);
	game_node *game = NULL; /* Ponteiro correspondente a name */
	game_link *head = hash_games[key];
	while(hash_games[key]){
		if(!strcmp(hash_games[key]->link->game_name, name)){
			game = hash_games[key]->link;
			break;
		}
		else 
			hash_games[key] = hash_games[key]->next;
	}
	hash_games[key] = head; /* Reapontar para a cabeca original */
	return game;
}

/* Liberta memoria alocada para o jogo na lista de jogos e na propria hash_table */
void delete_game_hash(game_link **hash_games, l_game *game_list, char *name){
	int key = hashU(name, T_HASH);
	game_link *previous = NULL, *head = hash_games[key];
	while(hash_games[key]){
		if(!strcmp(hash_games[key]->link->game_name, name)){ /* Jogo encontrado */
			if(previous)               /* Caso em que o elemento a ser apagado nao e a cabeca */
				previous->next = hash_games[key]->next;
			else
				head = hash_games[key]->next;
			delete_game(hash_games[key]->link, game_list);
			free(hash_games[key]);
			hash_games[key] = head; /* Reapontar para a cabeca */
			break;
		}
		else{
			previous = hash_games[key];
			hash_games[key] = hash_games[key]->next;		
		}
	}
}

/* Liberta memoria alocada para a hash table */
void destroy_hash_game(game_link **hash_games){
	int i;
	game_link *next;
	for (i = 0; i < T_HASH; i++){
		while(hash_games[i]){
			next = hash_games[i]->next;
			free(hash_games[i]);
			hash_games[i] = next;
		}
	}
	free(hash_games);
}


/* Adiciona um jogo no final da lista duplamente ligada */
game_node* insert_game(l_game *game_list, char *name, t_node *first_team, t_node *second_team, int first_score, int second_score){
	game_node *new_game = can_fail_malloc(sizeof(game_node));
	new_game->game_name = can_fail_malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(new_game->game_name, name);
	new_game->team_one = first_team;
	new_game->team_two = second_team;
	new_game->score_one = first_score;
	new_game->score_two = second_score;
	record_update(first_team, second_team, first_score, second_score); /* Determinar vitoria e regista-la */
	new_game->previous = game_list->last;
	if(game_list->last)     /* Se a cauda da lista nao for NULL reaponta o ponteiro para a nova cabeca */ 
		game_list->last->next = new_game;
	else{                   /* Caso contrario quer dizer que a lista esta vazia */
		game_list->head = new_game;
	}
	game_list->last = new_game;
	new_game->next = NULL;
	return new_game;
}

/* Regista a vitoria (se houver) na estrutura da equipa vencedora */
void record_update(t_node *team_one, t_node *team_two, int score_one, int score_two){
	if(score_one > score_two)
		team_one->wins += 1;
	if (score_one < score_two)
		team_two->wins += 1;
}

/* Remove vitoria(se houver) na estrutura da equipa vencedora (usar quando se anula ou altera-se resultado de um jogo)*/
void remove_win(t_node *team_one, t_node *team_two, int score_one, int score_two){
	if(score_one > score_two)
		team_one->wins -= 1;
	if (score_one < score_two)
		team_two->wins -= 1;
}

/* Libertada memoria alocada o jogo de input */
void free_game(game_node *game){
	free(game->game_name);
	free(game);
}

/* Liberta memoria alocada para o jogo de input */
void delete_game(game_node *game, l_game *game_list){
	if(game->previous)
		game->previous->next = game->next;
	else
		game_list->head = game->next;
	if(game->next)
		game->next->previous = game->previous;
	else
		game_list->last = game->previous;
	free_game(game);
}