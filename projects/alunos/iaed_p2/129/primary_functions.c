#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "primary_functions.h"


/*
* void add_game(unsigned int ln, game_table *games, team_table *teams)
*   
*   Adds a new game if all the parameter are ok, else prints error
*   
*   Input: unsigned int ln      -> input line number
*          game_table *games    -> stored games 
*          team_table *teams    -> stored teams
*/
void add_game(unsigned int ln, game_table *games, team_table *teams){
    char *game_name, *team_name_1, *team_name_2;
    int score_1, score_2;
    team *team_1, *team_2;

    getchar();
    game_name = get_string_until(':');
    team_name_1 = get_string_until(':');
    team_name_2 = get_string_until(':');
    scanf("%d:%d", 
        &score_1, 
        &score_2);
    getchar();


    if (get_game(games, game_name) != NULL){
        printf("%d Jogo existente.\n", ln);
        free(game_name);              

    }else if ((team_1 = get_team(teams, team_name_1)) == NULL ||
    (team_2 = get_team(teams, team_name_2)) == NULL){
        printf("%d Equipa inexistente.\n", ln);
        free(game_name);      

    }else{
        
        new_game(games, game_name, team_1, team_2, score_1, score_2);
        
        if(score_1 > score_2){
            update_team_wins(team_1, 1);
        
        }else if(score_1 < score_2){
            update_team_wins(team_2, 1);
        }
    }

    free(team_name_1);
    free(team_name_2);
}

/*
* void add_team(unsigned int ln, team_table *teams)
*   
*   Adds a new team if a team with same doesnt already exist, else prints error
*   
*   Input: unsigned int ln      -> input line number
*          team_table *teams    -> stored teams

*/
void add_team(unsigned int ln, team_table *teams){
    char *name;

    getchar();
    name = get_string_until('\n');

    if (get_team(teams, name) != NULL){
        printf("%d Equipa existente.\n", ln);
        free(name);

    }else{
        new_team(teams, name);
    }
}

/*
* void change_game_score(unsigned int ln, game_table *games)
*   
*   Changes a games score if game exists, else prints error
*   
*   Input: unsigned int ln      -> input line number
*          game_table *games    -> stored games
*/
void change_game_score(unsigned int ln, game_table *games){
    char *name;
    int score_1, score_2;
    game *game;
    team *winner, *new_winner;

    getchar();
    name = get_string_until(':');
    scanf("%d:%d", 
        &score_1, 
        &score_2);
    getchar();

    if((game = get_game(games, name)) == NULL){
        printf("%d Jogo inexistente.\n", ln);
        

    }else{
        winner = game_winner(game);
        update_score(game, score_1, score_2);
        new_winner = game_winner(game);
        
        if(winner != NULL && new_winner != NULL){
            if(!(same_team(winner, new_winner))){
                update_team_wins(winner, -1);
                update_team_wins(new_winner, 1);
            }

        }else if(winner != NULL){
            update_team_wins(winner, -1);

        }else if(new_winner != NULL){
            update_team_wins(new_winner, 1);
        }
    }

    free(name);
}

/*
* void find_game(unsigned int ln, game_table *games)
*   
*   Prints a games info if name correspondes to a game, else prints error
*   
*   Input: unsigned int ln      -> input line number
*          game_table *games    -> stored games
*/
void find_game(unsigned int ln, game_table *games){
    char *name;
    game *game;

    getchar();
    name = get_string_until('\n');
    
    if((game = get_game(games, name)) == NULL){
        printf("%d Jogo inexistente.\n", ln);


    }else{
        printf("%d ", ln);
        print_game(game);
    }
    
    free(name);
}

/*
* void find_team(unsigned int ln, team_table *teams)
*   
*   Prints a teams info if name correspondes to a team, else prints error
*   
*   Input: unsigned int ln      -> input line number
*          team_table *team     -> stored teams
*/
void find_team(unsigned int ln, team_table *teams){
    char *name;
    team *team;

    getchar();
    name = get_string_until('\n');
    
    if((team = get_team(teams, name)) == NULL){
        printf("%d Equipa inexistente.\n", ln);

    }else{
        printf("%d ", ln);
        print_team(team);   
    }
    free(name);
}

/*
* void list_games(unsigned int ln, game_table *games)
*   
*   Prints all stored games info or nothing if no games have been added
*   
*   Input: unsigned int ln      -> input line number
*          game_table *games    -> stored games
*/
void list_games(unsigned int ln, game_table *games){
    game *game;

    getchar();

    game = first_game(games);

    while (game != NULL){
        printf("%d ", ln);
        print_game(game);

        game = next_game(games, game);
    }
}

/*
* void list_top_winners(unsigned int ln, team_table *teams)
*   
*   Prints the names of the teams that won the most games
*   
*   Input: unsigned int ln      -> input line number
*          team_table *teams    -> stored teams
*/
void list_top_winners(unsigned int ln, team_table *teams){
    int i;
    char **team_names;

    getchar();

    team_names = get_top_winners_names(teams);

    if (team_names[0] != NULL){    
        printf("%d Melhores %d\n", 
            ln, 
            get_max_win_number(teams));
        
        for(i = 0; team_names[i] != NULL; i++){
            printf("%d * %s\n", 
                ln, 
                team_names[i]);
        } 
    }
}

/*
* void remove_game(unsigned int ln, game_table *games)
*   
*   Removes a game from the stored games, prints error if game doenst exist
*   
*   Input: unsigned int ln      -> input line number
*          game_table *games    -> stored games

*/
void remove_game(unsigned int ln, game_table *games){
    char *name;
    game *game;
    team *winner;

    getchar();
    name = get_string_until('\n');

    if((game = get_game(games, name)) == NULL){
        printf("%d Jogo inexistente.\n", ln);

    }else{
        winner = game_winner(game);
        
        if(winner != NULL){
            update_team_wins(winner, -1);
        }

        delete_game(games, game);
    }
    free(name);
}

/*
* void free_all(game_table * games, team_table *teams)
*   
*   Frees all the game and team related items
*   
*   Input: game_table *games    -> stored games
*          team_table *teams    -> stored teams
*/
void free_all(game_table * games, team_table *teams){
    free_games(games);
    free_teams(teams);
}

/*
* char * get_string_until(char stop_char)
*   
*   Reads and stores a string until a given char is found
*   
*   Input: char stop_char       -> char that when found stops read
*
*   Output: char*               -> pointer for 1st string pos
*/
char * get_string_until(char stop_char){
    int i;
    char c, buffer[MAX_STRING_LEN + 1], *string;

    for(i = 0; (c = getchar()) != stop_char && i < MAX_STRING_LEN; i++){
        buffer[i] = c;
    }
    buffer[i] = '\0';

    string = can_fail_malloc((i+1) * sizeof(char));
    strcpy(string, buffer);

    return string;
}