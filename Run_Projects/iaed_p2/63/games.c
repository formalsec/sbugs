#include "games.h"

/*
* Description: reads a single number of the score of a game.
*/
int read_score(){
    int score;
    scanf(":%d", &score);
    return score;
}


/*
* Description: creates a game based on input.
*/
game create_game(node_teams **teams_table){

    game new_game;
    /*auxiliar team nodes for each team*/
    node_teams node_aux_t1, node_aux_t2;
    /*pointers for the auxiliar nodes*/
    node_teams *p_node_aux_t1, *p_node_aux_t2;
    /*arrays for the teams and game names*/
    char name[MAX_CHAR] = {0}, name_t1[MAX_CHAR] = {0}, name_t2[MAX_CHAR] = {0};
    /*scores of the game*/
    int score1, score2;
    
    scanf(" %[^:]:%[^:]:%[^:]:%d:%d", name, name_t1, name_t2, &score1, &score2);

    /*allocates the necessary memory for the name and saves it in the game*/
    new_game.name = malloc((strlen(name)+1)*sizeof(char));
    strcpy(new_game.name, name);

    /*allocates the necessary memory for the name and saves it in the team*/
    node_aux_t1.t.name = malloc((strlen(name_t1)+1)*sizeof(char));
    strcpy(node_aux_t1.t.name, name_t1);
    p_node_aux_t1 = &node_aux_t1;

    /*allocates the necessary memory for the name and saves it in the team*/
    node_aux_t2.t.name = malloc((strlen(name_t2)+1)*sizeof(char));
    strcpy(node_aux_t2.t.name, name_t2);
    p_node_aux_t2 = &node_aux_t2;

    /*saves the game score*/
    new_game.score1 = score1;
    new_game.score2 = score2;

    /*finds the correspondent teams and saves pointers for them*/
    new_game.t_1 = in_table_teams(teams_table, p_node_aux_t1);
    new_game.t_2 = in_table_teams(teams_table, p_node_aux_t2);

    /*frees the memory of the auxiliar nodes*/
    free(node_aux_t1.t.name);
    free(node_aux_t2.t.name);

    return new_game;
}


/*
* Description: frees the memory alloc'd to a game.
*/
void destroy_game(game g){
    free(g.name);
}


/*
* Description: creates a game node with the given name and the pointers to NULL.
*/
node_games create_node_game(game new_game){

    node_games node_new_game;

    node_new_game.g = new_game;
    node_new_game.next = NULL;
    node_new_game.next_in_hash_table = NULL;
    node_new_game.prev = NULL;
    node_new_game.prev_in_hash_table = NULL;

    return node_new_game;
}


/*
* Description: gets the game winner, if it is a draw returns NULL.
*/
node_teams * get_winner(node_games *game){

    /*winner is the first team if it has a bigger score than the second*/
    if (game->g.score1 > game->g.score2){
        return game->g.t_1;
    }
    /*winner is the second team if it has a bigger score than the first*/
    if (game->g.score1 < game->g.score2){
        return game->g.t_2;
    }
    return NULL;
}


/*
* Description: pushes the new game to the list of games.
*/
node_games * push_game(node_games *head, game g){

    /*creates a pointer to a node and allocates memory for a game node*/
    node_games *new = malloc(sizeof(node_games));
    /*atributes the game to the node*/
    new->g = g;
    /*sets the next node in the list to NULL*/
    new->next = NULL;

    /*if the list is empty*/
    if (head == NULL){
        /*sets the previous node to NULL and the head of the list to the new*/
        new->prev = NULL;
        head = new;
        return head;
    }

    /*sets the next node of the head to the new*/
    head->next = new;
    /*and the previous of the new to the head*/
    new->prev = head;

    return new;
}


/*
* Description: frees all memory alloc'd to the game node.
*/
void free_game(node_games *game){
    free(game->g.name);
    free(game);
}


/*
* Description: frees all memory alloc'd to the list of games.
*/
node_games * destroy_games(node_games *head){

    node_games *tmp;
    /*goes through the list and frees the memory alloc'd to the game and node*/
    while (head != NULL){
        tmp = head->prev;
        free_game(head);
        head = tmp;
    }
    return NULL;
}


/*
* Description: finds the game given by the input and returns the pointer of the node
*              that contains it.
*/
node_games * find_game(node_games **games_table){

    game g;
    node_games node_g;
    node_games *p_node_g;
    node_games *head_g;
    char name[MAX_CHAR];

    /*gets the name of the game and saves it in the game to search*/
    scanf(" %[^:\n]", name);
    g.name = malloc((strlen(name)+1)*sizeof(char));
    strcpy(g.name,name);

    /*creates a node with the game to search and a pointer to that node*/
    node_g = create_node_game(g);
    p_node_g = &node_g;

    /*finds the node that contains the game to search*/
    head_g = in_table_games(games_table, p_node_g);

    /*frees the temporary game to search*/
    destroy_game(g);

    return head_g;
}


/*
* Description: applies a given score to a game.
*/
void apply_score(node_games *game, int score1, int score2){
    game->g.score1 = score1;
    game->g.score2 = score2;
}


/*
* Description: gets the pointer to the first team of the game.
*/
node_teams * get_t1(node_games *game){
    return game->g.t_1;
}


/*
* Description: gets the pointer to the second team of the game.
*/
node_teams * get_t2(node_games *game){
    return game->g.t_2;
}


/*
* Description: gets the name of the game.
*/
char * get_game_name(node_games *game){
    return game->g.name;
}


/*
* Description: gets the name of the first team of the game.
*/
char * get_name_t1(node_games *game){
    return game->g.t_1->t.name;
}


/*
* Description: gets the name of the second team of the game.
*/
char * get_name_t2(node_games *game){
    return game->g.t_2->t.name;
}


/*
* Description: gets the score of the first team of the game.
*/
int get_score1(node_games *game){
    return game->g.score1;
}


/*
* Description: gets the score of the second team of the game.
*/
int get_score2(node_games *game){
    return game->g.score2;
}


/*
* Description: gets the next node of the games list.
*/
node_games * get_next_list(node_games *node){
    return node->next;
}


/*
* Description: gets the previous node of the games list.
*/
node_games * get_prev_list(node_games *node){
    return node->prev;
}


/*
* Description: gets the next node of the list in the hahs_table.
*/
node_games * get_next_table(node_games *node){
    return node->next_in_hash_table;
}


/*
* Description: gets the previous node of the list in the hahs_table.
*/
node_games * get_prev_table(node_games *node){
    return node->prev_in_hash_table;
}


/*
* Description: prints the games in the order they were created.
*/
void print_games_in_order(node_games *head, int line_counter){

    node_games *tmp;

    /*if there aren't any games don't do anything*/
    if(head == NULL){
        return;
    }

    /*goes to the first element of the list*/
    for (tmp = head; tmp->prev != NULL; tmp = tmp->prev);

    /*prints the games from first to last*/
    while(tmp != NULL){
        printf("%d %s %s %s %d %d\n", line_counter,
                                    get_game_name(tmp), 
                                    get_name_t1(tmp), 
                                    get_name_t2(tmp), 
                                    get_score1(tmp), 
                                    get_score2(tmp));
        tmp = tmp->next;
    }
}


/*
* Description: performs the necessary swaps around the node that is going to be 
*              deleted.
*/
void delete_swaps(node_games **head_games, node_games **games_table, 
                node_games *game_found){
    
    /*pointers to adjacent nodes both in the list and the hashtable*/
    node_games *game_next_l, *game_prev_l, *game_next_t, *game_prev_t;
    /*index of the hashtable*/
    int index;

    /*gets the index*/
    index = hash_game(game_found);

    /*get all the adjacent nodes*/
    game_next_l = get_next_list(game_found);
    game_prev_l = get_prev_list(game_found);
    game_next_t = get_next_table(game_found);
    game_prev_t = get_prev_table(game_found);

    /*the game is the only game in the list*/
    if ((game_next_l == NULL) && (game_prev_l == NULL)){
        *head_games = NULL;
    }

    /*the game was the last to be added to the list*/
    else if ((game_next_l == NULL) && (game_prev_l != NULL)){
        game_prev_l->next = NULL;
        *head_games = game_prev_l;
    }

    /*the game is not the only nor the last game of the list*/
    else{
        game_next_l->prev = game_prev_l;
        /*the game is not the first of the list*/
        if (game_prev_l != NULL){
            game_prev_l->next = game_next_l;
        }
    }

    /*the game is the only game in the list in the index of the table*/
    if ((game_next_t == NULL) && (game_prev_t == NULL)){
        games_table[index] = NULL;
    }

    /*the game was the last to be added to the list in the index of the table*/
    else if ((game_next_t == NULL) && (game_prev_t != NULL)){
        game_prev_t->next_in_hash_table = NULL;
        games_table[index] = game_prev_t;
    }

    /*the game is not the only nor the last game of the list 
    in the index of the table*/
    else{
        game_next_t->prev_in_hash_table = game_prev_t;
        /*the game is not the first of the list in the index of the table*/
        if (game_prev_t != NULL){
            game_prev_t->next_in_hash_table = game_next_t;
        }
    }
}