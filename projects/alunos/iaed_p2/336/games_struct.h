#ifndef GAMES_STRUCT
#define GAMES_STRUCT
#include "teams_struct.h"
/* game_node e uma strutura duplamente ligada */
typedef struct struct_game{
		struct struct_game *next;
		struct struct_game *previous;
		char *game_name; 
		t_node *team_one, *team_two;	
		int score_one, score_two;
} game_node;

/* Estrutura que identifica o primeiro e ultimo jogo da lista de jogos */
typedef struct game_list{
	game_node *head, *last;
} l_game;

/* Estrutura de cada bloco da hash table */
typedef struct game_link{
	game_node *link;
	struct game_link *next;
} game_link;

/* Inicializa uma estrutura l_game */
l_game* init_game_list();

/* Liberta espaco alocado para a lista duplamente ligada dos jogos */
void destroy_game_list(l_game *game_list);

/* Inicializa uma hash table de jogos */
game_link** init_hash_games();

/* Numa certa key da hash table coloca um link na cabeca e liga-o ao antigo */
game_link* insert_beguin_hash_game(game_link *head, game_node *game);

/* Coloca um jogo na hash table */
void insert_hash_game(game_link **hash_games, game_node *game);

/* Retorna o ponteiro que aponta para o nome do jogo de input (retorna NULL se a equipa nao existir) */
game_node* search_game(game_link **hash_games, char *name);

/* Liberta memoria alocada para o jogo na lista de jogos e na propria hash_table */
void delete_game_hash(game_link **hash_games, l_game *game_list, char *name);

/* Liberta memoria alocada para a hash table */
void destroy_hash_game(game_link **hash_games);

/* Adiciona um jogo no final da lista duplamente ligada */
game_node* insert_game(l_game *game_list, char *name, t_node *first_team, t_node *second_team, int first_score, int second_score);

/* Regista a vitoria (se houver) na estrutura da equipa vencedora */
void record_update(t_node *team_one, t_node *team_two, int score_one, int score_two);

/* Remove vitoria(se houver) na estrutura da equipa vencedora (usar quando se anula ou altera-se resultado de um jogo)*/
void remove_win(t_node *team_one, t_node *team_two, int score_one, int score_two);

/* Libertada memoria alocada o jogo de input */
void free_game(game_node *game);

/* Liberta memoria alocada para o jogo de input */
void delete_game(game_node *game, l_game *game_list);

#endif