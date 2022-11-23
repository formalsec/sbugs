#ifndef GAMES_H
#define GAMES_H
#define MAXCHAR 1024

typedef struct game_node {
	struct game_node * next;
	struct game_node * previous;

	char * name;
	char * t1_name;
	char * t2_name;
	int score_t1;
	int score_t2;
	char * winner;
} game;


typedef struct {
	game * head;
	game * tail;
} Games;


typedef struct {
	game * game_slot;
	int occ;
} Slot;


typedef struct {
	Slot * slots;
	int size;
	int cap;
} HashGames;


Games * init_Glist();
void destroy_Glist(Games * linkedlist);
void free_game_node(game * game_node);

HashGames * init_HGtable(int size);
void destroy_HGtable(HashGames * hashtable);

void new_game(Games * games, HashGames * hashtable_games, HashTeams * hashtable_teams, int NL);
int verify_conditions_to_add_game(int NL, char game_name[MAXCHAR], char t1_name[MAXCHAR],
 char t2_name[MAXCHAR], HashGames * hashtable_games, HashTeams * hashtable_teams);
game * alloc_game(char game_name[MAXCHAR], char t1_name[MAXCHAR], char t2_name[MAXCHAR], int score_t1, int score_t2);
char * choose_winner(int score_t1, int score_t2, char * t1_name, char * t2_name);
void add_last_game(Games * games, game * new_game);

void add_game_to_hash(game * game_node, HashGames * hashtable);
game * hash_lookfor_game(HashGames * hashtable, char * name);

void show_all_games(Games * games, int NL);

void lookfor_game(HashGames * hashtable, int NL);

void sum_win_in_team(char * team_name, HashTeams * hashtable_teams);

void remove_game(Games * games, HashGames * hashtable_games, int NL, HashTeams * hashtable_teams);
void erase_game_node(Games * games, game * game_x, HashGames * hashtable, int h);

void change_game_score(HashGames * hashtable_games, HashTeams * hashtable_teams, int NL);
void change_winner(game * game_x, char * new_winner, HashTeams * hashtable_teams);

void resize_hashtable_games(HashGames * hashtable);
void init_new_slots(Slot * new_slots, int new_cap);
void rehash_games(HashGames * hashtable, Slot * new_slots, Slot * old_slots, int new_cap, int new_size);

#endif
