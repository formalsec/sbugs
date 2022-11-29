#ifndef GAMES_H
#define GAMES_H

/* estrutura de um jogo */
typedef struct stru_game{
	char * g_name;	/* nome do jogo */
	char * name_t1;	/* nome da equipa 1 */
	char * name_t2;	/* nome da equipa 2 */
	int score1;		/* score da equipa 1 */
	int score2;		/* score da equipa 2 */
} game;

/* estrutura de um node de uma lista de jogos duplamente ligada */
typedef struct stru_node_games{
	game * p_g;										/* ponteiro para um jogo */
	struct stru_node_games * next, * prev, * other;	/* ponteiros para o node anterior e seguinte */
} node_dlist_games;									/* other tem o valor NULL na lista de jogos */
													/* e na hashtable aponta para o node na */
/* estrutura de uma lista duplamente ligada de jogos   lista de jogos ordenada correspondente */
typedef struct{
	node_dlist_games * head, * last;	/* ponteiros para o primeiro e ultimo node */
} dlist_games;

/* delcaracao das funcoes da gestao das estruturas de jogos */
game * new_game(char * g_name, char * name_t1, char * name_t2, int score1, int score2);
void free_game(game * p_g);
dlist_games * mk_dlist_games();
void free_node_dlist_games(node_dlist_games * n_dl);
void free_dlist_games(dlist_games * dl);
void rm_node_dlist_games(dlist_games * dl, node_dlist_games * n_dl);
node_dlist_games * addlast_dlist_games(dlist_games * dl, game * p_g);
dlist_games ** init_hasht_games();
dlist_games * init_dlist_games();
void insert_hasht_g(dlist_games ** hasht_g, game * p_g, node_dlist_games * other);
node_dlist_games * search_hasht_g(dlist_games ** hasht_g, char * g_name);
void free_games(dlist_games ** hasht_g, dlist_games * dl_g);

#endif