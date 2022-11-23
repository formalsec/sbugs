#ifndef GAME_H
#define GAME_H
typedef struct game_node{       /* lista de jogos para a hashtable */
    struct game_node *next;
    char *name;
    char *team1;
    char *team2;
    int score1;
    int score2;
}*game_link;

typedef struct game_pointers{   /* lista de ponteiros para jogos na ordem de entrada */
    game_link game;
    struct game_pointers *next;
    struct game_pointers *prev;
}*game_list;

void add_game(game_link *games,char buffer[1024], char t1[1024], char t2[1024], char s1[100], char s2[100], game_list *games_sorted);
void print_games(game_link* games);
int existing_game(game_link *hashtable,char buffer[1024]);
game_link get_game(game_link *games,char buffer[1024]);
game_link prev(game_link *games, game_link atual);
void free_game_list(game_link *games);
void free_game_node(game_link n);
void free_ord(game_list n);

#endif