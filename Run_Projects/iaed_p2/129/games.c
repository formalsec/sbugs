#include "games.h"

/*
* game_table * init_games()
*   
*   Initializes the structure to store the games
*   
*   Output: game_table*         -> pointer for game storing structure
*/
game_table * init_games(){
    int i;

    game_table *games = malloc(sizeof(game_table));

    for(i = 0; i < GAME_TABLE_SLOTS; i++){
        games->table[i] = NULL;
    }

    games->first_game = NULL;
    games->latest_game = NULL;

    return games;
}

/*
* int hash_game(char *name)
*   
*   determines the posiotion in the hash table for the game 
*   
*   Input: char *name           -> games name 
*
*   Output: int                 -> pos in the hash table
*/
int hash_game(char *name){
    int key, i;

    for(key = 0, i = 0; name[i] != '\0'; i++){
        key += (MAX_GAME_NAME_LEN - 1) * name[i];
    }
    key = key % GAME_TABLE_SLOTS;

    return key;
} 

/*
* void push_game(game_table *games, game *game)
*   
*   Stores a game in the table 
*   
*   Input: game_table *games    -> games structure pointer
*          game *game           -> game pointer
*/
void push_game(game_table *games, game *game){
    int pos;
    game_node *taken_node;
    
    game_node *new_node = malloc(sizeof(game_node));
    
    new_node->game = game;
    new_node->next_game = NULL;
    new_node->next_node = NULL;

    pos = hash_game(game->name);
    
    if(games->table[pos] == NULL){
        games->table[pos] = new_node;
        new_node->previous_node = NULL;


    }else{
        taken_node = games->table[pos]; 
        while (taken_node->next_node != NULL){
            taken_node = taken_node->next_node;
        }
        taken_node->next_node = new_node;
        new_node->previous_node = taken_node;
    }

    if (games->latest_game == NULL){
        games->first_game = new_node;
        games->latest_game = new_node;
        new_node->previous_game = NULL;

    }else{
        new_node->previous_game = games->latest_game;
        games->latest_game->next_game = new_node;
        games->latest_game = new_node;
    }

}

/*
* int same_game(game *game_1, game *game_2)
*   
*   Checks if the games are the same
*   
*   Input: game *game_1         -> 1st game pointer
*          game *game_2         -> 2st game pointer  
*
*   Output: int                 -> 1 if games are the same, 0 if not
*/
int same_game(game *game_1, game *game_2){ 
    if(!(strcmp(game_1->name, game_2->name))){
        return 1;
    }
    return 0;
}

/*
* game_node * get_node(game_table *games, game *game)
*   
*   Obtains the pointer for the node of the given game
*   
*   Input: game_table *games    -> games structure pointer
*          char *game           -> game pointer
*
*   Output: game_node *         -> pointer for the game node
*/
game_node * get_node(game_table *games, game *game){
    int key;
    game_node *node;
    
    key = hash_game(game->name);
    node = games->table[key];

    while (!(same_game(node->game, game))){
        node = node->next_node;
    }
    
    return node;
}

/*
* void delete_game(game_table *games, game *game)
*   
*   Deletes a game from the stored games
*   
*   Input: game_table *games    -> games structure pointer
*          char *game           -> game pointer
*/
void delete_game(game_table *games, game *game){
    game_node *node;
    int key;

    key = hash_game(game->name);
    node = games->table[key];

    /*updates hash table line*/
    if(same_game(node->game, game)){
        games->table[key] = node->next_node;

    }else{
        while (!(same_game(node->game, game))){
            node = node->next_node;
        }

        node->previous_node->next_node = node->next_node;
    }

    if(node->next_node != NULL){
        node->next_node->previous_node = node->previous_node;
    }

    
    /*Updates time linked list*/
    if(same_game(games->first_game->game, game)){
        games->first_game = node->next_game;
    }else{
        node->previous_game->next_game = node ->next_game;
    }

    if(same_game(games->latest_game->game, game)){
        games->latest_game = node->previous_game;
    }else{
        node->next_game->previous_game = node->previous_game;
    }
    
    free_game(node->game);
    free(node);
}

/*
* void new_game(game_table *games, char *name, team *team_1, team *team_2, 
* int score_1, int score_2)
*   
*   Creates a new game and stores it
*   
*   Input: game_table *games    -> games structure pointer
*          char *name           -> new games name
*          team *team_1         -> pointer for the 1st team
*          team *team_2         -> pointer for the 2nd team
*          int score_1          -> 1st teams score
*          int score_2          -> 2nd teams score
*/
void new_game(game_table *games, char *name, team *team_1, team *team_2, 
int score_1, int score_2){
    game *new_game = malloc(sizeof(game));
    new_game->name = name;
    new_game->team_1 = team_1;
    new_game->team_2 = team_2;
    new_game->score_team_1 = score_1;
    new_game->score_team_2 = score_2;

    push_game(games, new_game);

}

/*
* game * get_game(game_table *games, char *name)
*   
*   Obtains the pointer for the game with the given name
*   
*   Input: game_table *games    -> games structure pointer
*          char *name           -> game name
*
*   Output: game *              -> pointer for the game or NULL if dont exist
*/
game * get_game(game_table *games, char *name){
    int key;
    game_node *node;

    key = hash_game(name);
    node = games->table[key];

    while(node != NULL){
        if(!(strcmp(node->game->name, name))){
            return node->game;
        }
        
        node = node->next_node;
    }

    return NULL;
}

/*
* void update_score(game *game, int score_1, int score_2)
*   
*   Obtains the pointer for the game with the given name
*   
*   Input: game *game           -> game pointer
*   int score_1                 -> new 1st teams score
*   int score_2                 -> new 2nd teams score
*/
void update_score(game *game, int score_1, int score_2){
    game->score_team_1 = score_1;
    game->score_team_2 = score_2;
}

/*
* game * first_game(game_table *games)
*   
*   Obtains the pointer for the first added game
*   
*   Input: game_table *games    -> games structure pointer
*
*   Output: game *              -> pointer for the game or NULL if dont exist
*/
game * first_game(game_table *games){
    if(games->first_game != NULL){
        return games->first_game->game;
    
    }else{
        return NULL;
    }
}

/*
* game * next_game(game_table *games, game *game)
*   
*   Obtains the pointer for the game added after a given game
*   
*   Input: game_table *games    -> games structure pointer
*          game *game           -> game pointer
*
*   Output: game *              -> pointer for the game or NULL if dont exist
*/
game * next_game(game_table *games, game *game){
    game_node *next_game_node;
    
    next_game_node = get_node(games, game)->next_game;

    if(next_game_node != NULL){
        return next_game_node->game;

    }else{
        return NULL;
    }
}

/*
* team * game_winner(game *game)
*   
*   Obtains the pointer for the tean wich won a given game
*   
*   Input: game *game           -> game pointer
*
*   Output: team *              -> pointer for the winner or NULL if tie
*/
team * game_winner(game *game){
    if(game->score_team_1 > game->score_team_2){
        return game->team_1;

    }else if(game->score_team_1 < game->score_team_2){
        return game->team_2;

    }else{
        return NULL;
    }
}

/*
* void print_game(game *game)
*   
*   Prints game info "<name> <1st team> <2nd team> <1st score> <2nd score>\n" 
*   
*   Input: game *game           -> game pointer
*/
void print_game(game *game){
    printf("%s %s %s %d %d\n", 
        game->name, 
        get_team_name(game->team_1), 
        get_team_name(game->team_2), 
        game->score_team_1,
        game->score_team_2);
}

/*
* void free_game(game *game)
*   
*   Frees a games structure
*   
*   Input: game *game           -> game pointer
*/
void free_game(game *game){
    free(game->name);
    free(game);
}

/*
* void free_games(game_table *games)
*   
*   Frees all game related structures
*   
*   Input: game_table *games    -> games structure pointer
*/
void free_games(game_table *games){
    game_node *node, *tmp;

    node = games->first_game;
    while(node != NULL){
        free_game(node->game);
        tmp = node->next_game;
        free(node);
        node = tmp;
    }

    free(games);
}