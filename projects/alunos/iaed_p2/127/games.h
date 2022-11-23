#ifndef GAMES_H
#define GAMES_H

/*----------------------------GAME STRUCTURES---------------------------*/
/*game - structure that represents a game*/
typedef struct {
    char * name;  /*name of the game*/
    char * team1; /*team1 s name*/
    char * team2; /*team2 s name*/
    int score_t1; /*team1 s score*/
    int score_t2; /*team2 s score*/
}game;

/*link - pointer to the node structure that contains a game pointer*/
typedef struct node{
    game * game; /*game pointer*/
    struct node* prev; /*pointer to the previous node*/
    struct node* next; /*pointer to the next node*/
}* link;

/*--------------Functions to manipulate game structures--------------*/

game *create_game(char* name, char* t1, char* t2, int sc1, int sc2);

/*--------------Functions to manipulate the game list----------------*/

link push(link* borders, game * g);

void delete_el(link* borders, link g);

/*--------------Functions to manipulate the game hash table----------*/

long int table_hash(char *name, long int m);

void table_g_init(link *game_t, long int m);

link *expand_g(link *game_tab, long int *max_len);

link *add_game_to_table(link *game_t, link g, long int *max_len);

void rearrange_tab_g(link *game_tab, long int pointer, long int *max_len);

long int search_aux(char *game_name, link *game_tab, long int m);

link search_g(char *game_name, link *game_tab, long int m);

void destroy_game_st(link *borders);

#endif /* GAMES_H */
