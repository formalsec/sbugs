#ifndef _GAMES_
#define _GAMES_
#include "teams.h"

/* Node struct containing a game's name, the teams that 
participated in that game and their respective scores, 
as well as a pointer to the next and previous games */
struct GameNode
{
    char *game_name, *team1, *team2;
    int score1, score2;
    struct GameNode *ht_next, *ht_previous, *table_next, *table_previous;
};
typedef struct GameNode *GameLink;

/* Game hash table wich countains an associated team hash table,
a pointer to an array of GameLinks that serve as headers to double linked lists, 
its size (number of headers) and the number of games currently stored within */
typedef struct GameHT
{
    TeamHT *team_ht_ptr;
    GameLink *ht_header;
    GameLink table_head, table_tail;
    int size, items_num;
} GameHT;

/**************************** Function prototypes ****************************/
GameHT game_ht_init(TeamHT *team_ht_ptr, int size);
GameLink game_ht_search(GameHT game_ht, char *game_name);
void game_ht_search_print(GameHT game_ht, char *game_name, unsigned long int NL);
void game_ht_insert(GameHT *game_ht_ptr, char *game_name, char *team1,
                    char *team2, int score1, int score2, unsigned long int NL);
void game_ht_delete(GameHT *game_ht_ptr, char *game_name, unsigned long int NL);
void game_ht_change_score(GameHT game_ht_ptr, char *game_name, int score1,
                          int score2, unsigned long int NL);
void game_ht_print_order(GameHT game_ht, unsigned long int NL);
void game_ht_free(GameHT game_ht);

#endif