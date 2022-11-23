#include "teams.h"

/******************************************************
*----------------------STRUCTURES---------------------*
******************************************************/

typedef struct L_G{
	struct L_G *next;
	char *name, *team1, *team2;
	int score1, score2;
} list_games;

typedef struct HT_G{
	int size;
	list_games **table; 
} hash_table_games;

typedef struct OL_G{
	list_games *game;
	struct OL_G *next, *prev;
}*ordered_list_g;

typedef struct L{
	struct OL_G *head, *tail; /*head is the first game
	of the list and tail is the last*/
} h_t_ordered_list;

/******************************************************
*-------------------AUXILIAR FUNCTIONS----------------*
*-------------------------games-----------------------*
*-----------------------PROTOTYPES--------------------*
******************************************************/

h_t_ordered_list *init_list();
hash_table_games *create_ht_game(int size); 
int hash_games(hash_table_games *game_ht, char *v);
void insertEnd_list(h_t_ordered_list *lst, list_games *g);
void remove_list(h_t_ordered_list *lst, char *token);
void print_list(h_t_ordered_list *lst, int NL);
list_games *insertBegin_games(hash_table_games *game_ht, char *name, char *team1, char *team2, int score1, int score2);
list_games *search_game_aux(hash_table_games *game_ht, char *v);
void delete_game_aux(hash_table_games *game_ht, char *v);
void change_score_aux(list_games *g, hash_table_teams *team_ht, int score1, int score2);