#ifndef JOGOS_H
#define JOGOS_H

typedef struct node{
	char * jogo_nome;
	char * nome_eq1;
	char * nome_eq2;
	int score1;
	int score2;
	struct node * prev;
	struct node * next;
} Game;

typedef struct lst{
	Game * head;
	Game * last;
} List_Games;

/*-----------------------------------------------------------------------------------------*/

/*inicia uma lista duplamente ligada de jogos*/
List_Games * init_list();

/*cria um novo jogo*/
Game * new_game(char * j, char * eq1, char * eq2, int sc1, int sc2);

/*acrescenta um novo jogo a lista de jogos, como elemento final*/
Game * add_end_game(List_Games * l, char * j, char * eq1, char * eq2, int sc1, int sc2);

/*procura um jogo pelo seu nome numa lista de jogos*/
Game * search_game(List_Games * l, char * nome_j);

/*altera o score de um jogo numa lista de jogos*/
void change_score(List_Games * l, char * jogo, int score1_new, int score2_new);

/*elimina um jogo da memoria*/
void free_game(Game * n);

/*elimina um jogo de uma lista de jogos*/
void remove_game(List_Games * l, char * jogo);

/*elimina o primeiro jogo de uma lista de jogos*/
Game * remove_first_game(Game * head);

/*elimina uma lista de jogos*/
void free_all_games(List_Games * l);

/*imprime informacoes relativas a um jogo*/
void print_game(Game * n);

#endif
