#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "game_struct.h"

/*CORE FUNCTIONS*/
/*Initializes an hashtable with n positions.*/
void init_hashtbl(game_item * ht_ptr)
{
    int i;

    for (i = 0; i < MAX; i++)
    {
        ht_ptr[i] = (game_item) can_fail_malloc(sizeof(struct g_item));
        ht_ptr[i]->head = NULL;
    }
}

/*Creates an hashtable and initializes it.*/
void init_games(game_item ** hash_ptr)
{
    *hash_ptr = (game_item*) can_fail_malloc(MAX * sizeof(game_item));
    init_hashtbl(*hash_ptr);
}

/*Frees a given node from the hashtable.*/
void free_node(game_node node)
{
    free_game(node->game);
    free(node);
}

/*Frees all positions and structs stored in the hashtable.*/
void free_games(game_item * ht_ptr)
{
    int i;
    game_node auxiliar_node;

    for (i = 0; i < MAX; i++)
    {
        while (ht_ptr[i]->head != NULL)
        {
            auxiliar_node = ht_ptr[i]->head;
            ht_ptr[i]->head = ht_ptr[i]->head->next;
            free_node(auxiliar_node);
        }
    free(ht_ptr[i]);   
    }
free(ht_ptr);
}

/*Inserts node at a given position on a given hashtable.*/
void node_push(game_node * head, game game, game_node * first, game_node * current)
{
    game_node new_node;

    new_node = (game_node) can_fail_malloc(sizeof(struct g_node));
    new_node->game = game;
    new_node->next = * head;
    new_node->previous = NULL;

    if ((*head) != NULL)
        (*head)->previous = new_node;
    * head = new_node;
    
    new_node->in_next = NULL;
    new_node->in_previous = NULL;
    
    if(* first == NULL)
    {
        * first = new_node;
        * current = new_node;
    }

    *current = new_node;
}

/*Finds the index where the node needs to be inserted in the hashtable and inserts it at the respective postion.*/
void insert_game(game_item * ht_ptr, game game, game_node * first, game_node * current)
{
    int index = hash_function(game->name);
    node_push(&ht_ptr[index]->head, game, first, current);
}

/*Prints a given node from the hashtable.*/
void print_game(game_node node, int NL)
{
    printf("%d %s %s %s %d %d\n", NL, node->game->name, node->game->team_1->name, node->game->team_2->name, node->game->score_1, node->game->score_2);
}

/*ADITIONAL FUNCTIONS*/
/*Searches for a given node in the hashtbale by name.*/
game_node search_game(game_item * ht_ptr, char * name)
{
    int i;
    game_node node;

    i = hash_function(name);
    node = ht_ptr[i]->head;

    while (node != NULL)
    {
        if (strcmp((node->game->name), name) == 0)
            return node;
        node = node->next;
    }
    return NULL;
}

void delete_ordered(game_node * head, game_node node)
{
    if(head == NULL || node == NULL)
        return;
    if(*head == node)
        *head = node->in_next;
    if(node->in_next != NULL)
        node->in_next->in_previous = node->in_previous;
    if(node->in_previous != NULL)
        node->in_previous->in_next = node->in_next;
}

/*Deletes a given node from the hashtable.*/
void delete_game(game_item hashtbl,game_node node)
{
    if (node->previous == NULL && node->next == NULL)
    {
        hashtbl->head = NULL;
        free_node(node);
    }
    else if (node->previous == NULL && node->next != NULL)
    {
        node->next->previous = NULL;
        hashtbl->head = node->next;
        free_node(node);
    }
    else if (node->previous != NULL && node->next != NULL)
    {
        node->previous->next = node->next;
        node->next->previous = node->previous;
        free_node(node);
    }
    else if (node->previous != NULL && node->next == NULL)
    {
        node->previous->next = NULL;
        free_node(node);
    }
}

/*Updates the score of a given game.*/
void update_score(game_node node, int s1, int s2)
{
    int p_s1, p_s2;
    team t1, t2;

    p_s1 = (int)node->game->score_1;
    p_s2 = (int)node->game->score_2;
    t1 = node->game->team_1;
    t2 = node->game->team_2;

    node->game->score_1 = s1;
    node->game->score_2 = s2;

    if(p_s1 > p_s2)
    {
        if(s1 < s2)
        {
            dec_score(t1);
            inc_score(t2);
        }
        if(s1 == s2)
            dec_score(t1);
    }
    if(p_s1 < p_s2)
    {
        if(s1 > s2)
        {
            dec_score(t2);
            inc_score(t1);
        }
        if(s1 == s2)
            dec_score(t2);
    }
    if(p_s1 == p_s2)
    {
        if(s1 > s2)
            inc_score(t1);
        if(s1 < s2)
            inc_score(t2);
    }
}

/*Prints all nodes from the hastable by order of insertion.*/
void insertion_order(game_node node, int NL)
{
    while (node != NULL)
    {
        print_game(node, NL);
        node = node->in_next;
    }
    
}