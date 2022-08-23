#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "games.h"
#define MAX_STR_LEN 1024 /*strings maximum length*/


/*--------------Functions to manipulate game structures--------------*/

/*Function to create a new game with the given parameters*/
game *create_game(char *name, char *t1, char *t2, int sc1, int sc2){
    game *new_game;
    new_game = malloc(sizeof(game));
    new_game -> score_t1 = sc1;
    new_game -> score_t2 = sc2;
    new_game -> name = malloc(sizeof(char) * (strlen(name) + 1));
    new_game -> team1 = t1;
    new_game -> team2 = t2;
    strcpy(new_game -> name, name);
    return new_game;
}

/*--------------Functions to manipulate the game list----------------*/

/*Function to push a new game into the game list*/
link push(link* borders, game* g){
    link new_node;
    new_node = malloc(sizeof(struct node));
    new_node -> game = g;
    new_node -> next = *borders;
    new_node -> prev = NULL;
    if (*borders == NULL)
        *(borders + 1) = new_node;
    else
        (*borders) -> prev = new_node;
    *borders = new_node;
    return new_node;
}

/*Function to delete a game from the game list*/
void delete_el(link* borders, link g){
    /*verifies if the game is in the borders of the game list*/
    if (g == *borders){
        if (g == *(borders + 1)){
            *borders = NULL;
            *(borders + 1) = NULL;
        }
        else{
            *borders = g -> next;
            (*borders) -> prev = NULL;
        }
    }
    else if(g == *(borders + 1)){
        *(borders + 1) = g -> prev;
        (*(borders + 1)) -> next = NULL;
    }
    /*middle case*/
    else{
        g -> prev -> next = g -> next;
        g -> next -> prev = g -> prev;
    }
    free(g -> game -> name);
    free(g -> game);
    free(g);

}

/*--------------Functions to manipulate the game hash table----------*/

/*Function that returns the respective hash value of the given string*/
long int table_hash(char *name, long int m){
    long int hash, n1 = 26453, n2 = 12532;

    for(hash = 0; *name != '\0'; name++, n1 = n1 * n2 % (m - 1)){
        hash = (n1 * hash + *name) % m;
    }
    return hash;
}

/*Function to initialize the game hash table*/
void table_g_init(link *game_t, long int m){
    long int i;
    for (i = 0; i < m; i++)
        *(game_t + i) = NULL;
}

/*Function to expand the size of the game hash table */
link *expand_g(link *game_tab, long int *max_len){
    long int i, old_m;
    link *new_tab = malloc(sizeof(link) * (*max_len) * 2);
    old_m = *(max_len);
    (*max_len) = (*max_len) * 2;
    table_g_init(new_tab, *max_len);
    for (i = 0; i < old_m; i++)
        if(*(game_tab + i) != NULL){
            add_game_to_table(new_tab, *(game_tab + i), max_len);
            (*(max_len + 1))--;
        }
    free(game_tab);
    return new_tab;
}

/*Function that adds a game to the game hash table*/
 link *add_game_to_table(link *game_t, link g, long int *max_len){
    long int m = *(max_len), hash;
    hash = table_hash(g -> game -> name, m);
    while(*(game_t + hash) != NULL)
        hash = (hash + 1) % m;
    *(game_t + hash) = g;
    (*(max_len + 1))++;
    /*if the number of elements is bigger then half the size of the
    table, expand it*/
    if (*(max_len + 1) > (m / 2))
        return expand_g(game_t, max_len);
    else
        return game_t;
}

/*Function to rearrange the elements of the game hash table, from the
given position(pointer)*/
void rearrange_tab_g(link *game_tab, long int pointer, long int *max_len){
    long int i, m = *max_len;
    link aux;
    for (i = (pointer + 1) % m; *(game_tab + i) != NULL; i = (i + 1) % m){
        aux = *(game_tab + i);
        *(game_tab + i) = NULL;
        add_game_to_table(game_tab, aux, max_len);
        (*(max_len + 1))--;
    }
}

/*Function that search for a game with the given name and returns
the index of that game in the table*/
long int search_aux(char *game_name, link *game_tab, long int m){
    long int i = table_hash(game_name, m);
    while (*(game_tab + i) != NULL){
        if(strcmp(game_name, (*(game_tab + i)) -> game -> name) == 0)
            return i;
        else
            i = (i + 1) % m;
    }
    /*returns -1 if the element doesn t exist*/
    return -1;
}

/*Function that does the same as search_aux but returns the game pointer
instead of the index*/
link search_g(char *game_name, link *game_tab, long int m){
    long int node_ptr;
    node_ptr = search_aux(game_name, game_tab, m);
    if (node_ptr != -1)
        return *(game_tab + node_ptr);
    else
        return NULL;
}

/*Function that destroy both game list and game hash table*/
void destroy_game_st(link *borders){
    link t = *borders, aux;
    while(t != NULL){
        aux = t -> next;
        free(t -> game -> name);
        free(t -> game);
        free(t);
        t = aux;
    }
}
