#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "main.h"

/* Adds a new team - name */
int comando_A(int counter, Hash_Array *team_hash){
    char *team_name;
    Game *team, *aux;

    /* Get the name */
    team_name = can_fail_malloc(sizeof(char)*STRING_SIZE);
    scanf("%[^:\n]", team_name);   
    team_name = resize_string(team_name);

    /* Check if team already exists */
    aux = hashtable_get(team_hash, team_name); 
    if(aux!=NULL){
        free(team_name);
        printf("%d Equipa existente.\n", counter);
        return 1;
    }

    /* Create the team */
    team = can_fail_malloc(sizeof(Game));
    team->score1 = 0;
    team->team_flag = 1;

    /* Add the team to the hashtable */
    hashtable_insert(team_hash, team_name, team);
    return 1;
}

/* Finds a certain team  */
int comando_P(int counter, Hash_Array *team_hash){
    char team_name[STRING_SIZE];
    Game *output;   
    scanf("%[^:\n]", team_name);   
    output = hashtable_get(team_hash, team_name);
    if(output == NULL){
        printf("%d Equipa inexistente.\n",counter);
        return 1;
    }
    
    printf("%d %s %d\n", counter, team_name, output->score1);

    return 1;
}

/* Adds a game - name:team1:team2:score1:score2 */
Node_ptr comando_a(int counter, Hash_Array *game_hash, Hash_Array *team_hash, Node_ptr top_game_list){
    int score1, score2;
    char *game_name, *team1, *team2;
    Game *game, *aux, *aux1, *winning_team;


    /* Get the info */
    game_name = read_string();
    team1 = read_string();
    team2 = read_string();
    scanf("%d:%d", &score1, &score2);

    /* Check if the game exists */
    aux = hashtable_get(game_hash, game_name); 
    if(aux!=NULL){
        free(game_name);
        free(team1);
        free(team2);
        printf("%d Jogo existente.\n", counter);
        return NULL;
    }

    /* Check if teams exist */
    aux = hashtable_get(team_hash, team1); 
    aux1= hashtable_get(team_hash, team2); 
    if(aux==NULL || aux1==NULL){
        free(team1);
        free(team2);
        free(game_name);
        printf("%d Equipa inexistente.\n", counter);
        return NULL;
    }

    /* Check who won */
    if(score1>score2){
        winning_team = hashtable_get(team_hash, team1);
    }
    if(score1<score2){
        winning_team = hashtable_get(team_hash, team2);
    }
    if(score1==score2){
        winning_team = NULL;
    }
    if(winning_team != NULL){
        winning_team->score1 = winning_team->score1 + 1;
    }

    /* Create the game */
    game = can_fail_malloc(sizeof(Game));
    game->team_flag = 0;
    game->score1 = score1;
    game->score2 = score2;
    game->team1 = team1;
    game->team2 = team2;
    
    /* Add the game to the hashtable */
    hashtable_insert(game_hash, game_name, game);

    /* Add the key to the list */
    top_game_list = push(game_name, top_game_list);
    game->index = &top_game_list->size;
    return top_game_list;

}

/* List all of the games */
int comando_l(int counter, Hash_Array *game_hash, Node_ptr top_game_list){
    Node_ptr list_aux;
    Game *game;
    if(top_game_list == NULL){
        return 0;
    }

    /* If there is only one element */
    list_aux = top_game_list->first;
    if(list_aux==top_game_list){
        game = hashtable_get(game_hash, list_aux->value);
        printf("%d %s %s %s %d %d\n", counter, list_aux->value, game->team1, game->team2, game->score1, game->score2);
        return 0;
    }

    /* When there are multiple elements */
    while(list_aux != NULL){
        game = hashtable_get(game_hash, list_aux->value);
        printf("%d %s %s %s %d %d\n", counter, list_aux->value, game->team1, game->team2, game->score1, game->score2);
        list_aux = list_aux->prev;

    }

    return 0;
}

/* Looks for a game using the name - name */
int comando_p(int counter, Hash_Array *game_hash){
    char game_name[STRING_SIZE];
    Game *game;
    /* Grab the name */
    scanf("%[^:\n]", game_name);

    /* Grab the game */
    game = hashtable_get(game_hash, game_name);

    /* Print the game */
    if(game == NULL){
        printf("%d Jogo inexistente.\n", counter);
        return 1;
    }
    printf("%d %s %s %s %d %d\n", counter, game_name, game->team1, game->team2, game->score1, game->score2);

    return 1;
}

/* Deletes a game - name */
Node_ptr comando_r(int counter, Hash_Array *game_hash, Hash_Array *team_hash, Node_ptr top_game_list){
    char game_name[STRING_SIZE];
    Game *game, *winning_team;

    /* Read input */
    scanf("%[^:\n]", game_name);

    /* see if game exists */
    game = hashtable_get(game_hash, game_name);
    if(game == NULL){
        printf("%d Jogo inexistente.\n", counter);
        return top_game_list;
    }

    /* Update Scores */
    if(game->score1>game->score2){
        winning_team = hashtable_get(team_hash, game->team1);
    }
    
    if(game->score1<game->score2){
        winning_team = hashtable_get(team_hash, game->team2);
    }
    if(game->score1==game->score2){
        winning_team = NULL;
    }
    if(winning_team != NULL){
        winning_team->score1 = winning_team->score1 - 1;
    }
    
    /* remove from list */
    top_game_list = delete_index(*game->index, top_game_list);

    /* Remove from hashtable */
    hashtable_del(game_hash, game_name);

    /* Return the top of the list */
    return top_game_list;
}

/* Changes the score of a given game - name:score1:score2*/
int comando_s(int counter, Hash_Array *game_hash, Hash_Array *team_hash){
    Game *game, *winning_team, *losing_team;
    char game_name[STRING_SIZE];
    int score1, score2, before, after;
    
    /* Read input */
    scanf("%[^:\n]", game_name);
    scanf(":%d:%d", &score1, &score2);
    
    /* see if game exists */
    game = hashtable_get(game_hash, game_name);
    if(game == NULL){
        printf("%d Jogo inexistente.\n", counter);
        return 1;
    }
    
    /* Check if the winner has changed */
    before = game->score1 - game->score2;
    after = score1 - score2;
    if(before*after>=1 || (before == 0 && after == 0)){
        /* Means the winner has not changed */
        game->score1 = score1;
        game->score2 = score2;
        return 1;
    }
    
    /* Tied before */
    if(game->score1 == game->score2){
        if(score1>score2){
            winning_team = hashtable_get(team_hash, game->team1);
            winning_team->score1 = winning_team->score1 + 1;
            game->score1 = score1;
            game->score2 = score2;
            return 1;
        }
        if(score2>score1){

            winning_team = hashtable_get(team_hash, game->team2);
            winning_team->score1 = winning_team->score1 + 1;
            game->score1 = score1;
            game->score2 = score2;
            return 1;
        }
    }

    /* Tied after */
    if(score1==score2){
        if(game->score1>game->score2){
            winning_team = hashtable_get(team_hash, game->team1);
            winning_team->score1 = winning_team->score1 - 1;
            game->score1 = score1;
            game->score2 = score2;
            return 1; 
        }
        winning_team = hashtable_get(team_hash, game->team2);
        winning_team->score1 = winning_team->score1 - 1;
        game->score1 = score1;
        game->score2 = score2;
        return 1; 
    }

    /* Team1 won after */
    if(score1>score2){
        winning_team = hashtable_get(team_hash,game->team1);
        losing_team = hashtable_get(team_hash,game->team2);
    }

    /* Team2 win after */
    if(score1<score2){
        winning_team = hashtable_get(team_hash,game->team2);
        losing_team = hashtable_get(team_hash,game->team1);
    }

    /* Update the scores */
    winning_team->score1 = winning_team->score1 + 1;
    losing_team->score1 = losing_team->score1 - 1;
    if(losing_team->score1<0){
        losing_team->score1 = 0;
    }
    game->score1 = score1;
    game->score2 = score2;
    return 1;
}

/* Finds the teams with most wins and sorts them by lexicographic order */
int comando_g(int counter, Hash_Array *team_hash){
    
    biggest_wins(counter, team_hash);
    return 0;
}

/* Receives a string and will resize the string in order to save space */
char* resize_string(char *string){
    char *output;
    output = can_fail_malloc(sizeof(char)*strlen(string)+1);
    strcpy(output, string);
    free(string);
    return output;
}

/* Reads string input from user and resizes the array to the size of the string */
char* read_string(){
    char *output;

    output = can_fail_malloc(sizeof(char)*STRING_SIZE);
    
    scanf("%[^:]:", output);

    output = resize_string(output);
    
    return output;
}