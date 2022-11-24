#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "main_functions.h"

/*
* Description: initiates the program with no games and no teams.
*/
void init_program(node_games **head_games, node_teams **head_teams, 
                node_games **games_table, node_teams **teams_table){
                    
    int i = 0;

    /*sets the games and teams lists to empty lists*/
    *head_games = NULL;
    *head_teams = NULL;

    /*goes trough each entry (list) of each hash table and sets it to empty*/
    while (i < M){
        games_table[i] = NULL;
        teams_table[i] = NULL;
        i++;
    }
}


/*
* Description: adds a game to the system.
*/
void add_game(node_games **head_games, node_games **games_table, 
            node_teams **teams_table, int l_count){
    
    game new_game;
    node_games node_new_game;
    node_games *p_node_new_game;
    /*winner of the game*/
    node_teams *winner;
    /*flag that tells if the game already exists*/
    int fail_game = 0;
    /*flag that tells if a team doesn't exist*/
    int fail_team = 0;

    /*creates a game based on the input*/
    new_game = create_game(teams_table);
    /*creates a node with the game*/
    node_new_game = create_node_game(new_game);
    /*pointer to that node*/
    p_node_new_game = &node_new_game;

    /*if the game already exists trigger the flag*/
    if (in_table_games(games_table, p_node_new_game) != NULL){
        fail_game = 1;
    }
    
    /*if the team doesn't exist trigger the flag*/
    if (get_t1(p_node_new_game) == NULL){
        fail_team = 1;
    }
    
    /*if the team doesn't exist trigger the flag*/
    if (get_t2(p_node_new_game) == NULL){
        fail_team = 1;
    }

    /*if the game already exists*/
    if(fail_game){
        /*destroy the one given from input*/
        destroy_game(new_game);
        printf("%d Jogo existente.\n", l_count);
        return;
    }

    /*if one of the teams doesn't exist*/
    if (fail_team){
        /*destroy the game given from input*/
        destroy_game(new_game);
        printf("%d Equipa inexistente.\n", l_count);
        return;
    }

    /*gets the winner*/
    winner = get_winner(p_node_new_game);

    /*if it isn't a draw give a win to the winner*/
    if (winner != NULL){
        give_win(winner);
    }

    /*save the game in the list and in the hash table*/
    *head_games = push_game(*head_games, new_game);
    insert_game(games_table, *head_games);
}


/*
* Description: searches a game in the system.
*/
void search_game(node_games **games_table, int l_count){

    node_games *game_found;
    /*gets the game from the hash table*/
    game_found = find_game(games_table);

    /*if it doesn't exist print the error*/
    if (game_found == NULL){
        printf("%d Jogo inexistente.\n", l_count);
    }
    else{
        printf("%d %s %s %s %d %d\n", l_count, 
                                    get_game_name(game_found), 
                                    get_name_t1(game_found), 
                                    get_name_t2(game_found), 
                                    get_score1(game_found), 
                                    get_score2(game_found));
    }
}


/*
* Description: adds a team to the system.
*/
void add_team(node_teams **head_teams, node_teams **teams_table, int l_count){

    team new_team;
    node_teams node_new_team;
    node_teams *p_node_new_team;
    
    /*creates a game based on the input*/
    new_team = create_team();
    /*creates a node with the team*/
    node_new_team = create_node_team(new_team);
    /*pointer to that node*/
    p_node_new_team = &node_new_team;
    
    /*if the team already exists*/
    if (in_table_teams(teams_table, p_node_new_team) != NULL){
        /*destroy the team given from input*/
        destroy_team(new_team);
        printf("%d Equipa existente.\n", l_count);
        return;
    }

    /*save the team in the list and in the hash table*/
    *head_teams = push_team(*head_teams, new_team);
    insert_team(teams_table, *head_teams);
}


/*
* Description: searches a team in the system.
*/
void search_team(node_teams **teams_table, int l_count){

    node_teams *t_found;
    /*gets the team from the hash table*/
    t_found = find_team(teams_table);
    
    /*if the team exists print the team found*/
    if (t_found != NULL){
        printf("%d %s %d\n", l_count, get_team_name(t_found), get_wins(t_found));
        return;
    }
    else{
        printf("%d Equipa inexistente.\n", l_count);
    }
}


/*
* Description: lists the games by the order they were created.
*/
void list_games(node_games **head_games, int l_count){
    print_games_in_order(*head_games, l_count);
}


/*
* Description: deletes a game from the system.
*/
void delete_game(node_games **head_games, node_games **games_table, int l_count){

    node_games *game_found;
    /*winner of the game*/
    node_teams *winner;

    /*finds the game from the input*/
    game_found = find_game(games_table);

    /*if the game doesn't exist*/
    if (game_found == NULL){
        printf("%d Jogo inexistente.\n", l_count);
        return;
    }

    /*makes the necessary adjustments in the list and in the table*/
    delete_swaps(head_games, games_table, game_found);

    /*gets the game winner*/
    winner = get_winner(game_found);
    /*if it isn't a draw*/
    if (winner != NULL){
        /*take away a win from the winner*/
        take_win(winner);
    }

    /*deletes the game*/
    free_game(game_found);
}


/*
* Description: changes the score of a game.
*/
void change_score(node_games **games_table, int l_count){

    node_games *game_found;
    /*winner team after the new score being applied and old winner*/
    node_teams *new_winner, *old_winner;
    /*new scores of the game*/
    int new_score1, new_score2;

    /*gets the game*/
    game_found = find_game(games_table);
    /*gets the scores of the game*/
    new_score1 = read_score();
    new_score2 = read_score();

    /*if the game doesn't exist*/
    if (game_found == NULL){
        printf("%d Jogo inexistente.\n", l_count);
        return;
    }

    /*gets the winner before changing score*/
    old_winner = get_winner(game_found);

    /*changes the score*/
    apply_score(game_found, new_score1, new_score2);

    /*gets the winner after the score changed*/
    new_winner = get_winner(game_found);

    /*if the score changes the winner*/
    if(old_winner != new_winner){
        /*if there was a winner before take remove one win from it*/
        if (old_winner != NULL){
            take_win(old_winner);
        }
        /*if the new score isn't a draw give a win to the new winner*/
        if (new_winner != NULL){
            give_win(new_winner);
        }
    }
}


/*
* Description: list the teams with the most wins alphabetically.
*/
void list_most_wins(node_teams **head_teams, int l_count){

    /*array for the teams with most wins*/
    node_teams **winners;
    /*temporaru team*/
    node_teams *tmp;
    
    int i = 0;
    /*number of the most wins a team has and number of teams with those wins*/
    int max_wins = 0, teams_count = 0;

    /*if there aren't any teams*/
    if (*head_teams == NULL){
        return;
    }

    /*goes through the list of teams*/
    tmp = *head_teams;
    while (tmp != NULL){

        /*number of wins of the temporary team*/
        int n_wins;
        n_wins = get_wins(tmp);

        /*if the team has the max number of wins increment the teams count*/
        if (n_wins == max_wins){
            teams_count++;
        }
        /*if the team has more wins than the max seen before*/
        else if (n_wins > max_wins){
            /*set the max number of wins to this value*/
            max_wins = n_wins;
            /*set number of teams with that wins to 1*/
            teams_count = 1;
        }
        tmp = get_prev_team(tmp);
    }

    /*allocate the necessary amount of memory for teams with the most wins*/
    winners = can_fail_malloc(sizeof(node_teams*) * teams_count);
    
    /*goes through the list of teams*/
    tmp = *head_teams;
    while (tmp != NULL){
        /*if the team has the max number of wins*/
        if (get_wins(tmp) == max_wins){
            /*add it tho the winners list*/
            winners[i] = tmp;
            i++;
        }
        tmp = get_prev_team(tmp);
    }

    /*sort the list of the winners team alphabetically*/
    qsort(winners, teams_count, sizeof(node_teams*), compare_names);

    printf("%d Melhores %d\n", l_count, max_wins);
    /*goes through the winners list now sorted and print it*/
    for (i = 0; i < teams_count; i++){
        printf("%d * %s\n", l_count, get_team_name(winners[i]));
    }

    /*free the memory alloc'd to the winners lists*/
    free(winners);
}


/*
* Description: ends the program and frees all memory.
*/
void end_program(node_games **head_games, node_teams **head_teams){

    destroy_games(*head_games);
    destroy_teams(*head_teams);
}