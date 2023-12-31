#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "primary_functions.h"


int main(){
    unsigned int ln = 1;
    char opt;

    game_table *games = init_games();
    team_table *teams = init_teams();
    
    while((opt = getchar()) != 'x'){
        switch (opt){

        case 'a':       
            add_game(ln, games, teams);

            break;
        
        case 'l':
            list_games(ln, games);

            break;
        
        case 'p':
            find_game(ln, games);

            break;
        
        case 'r':
            remove_game(ln, games);

            break;
            
        case 's':
            change_game_score(ln, games);

            break;
        
        case 'A':
            add_team(ln, teams);

            break;
        
        case 'P':
            find_team(ln, teams);

            break;
        
        case 'g':
            list_top_winners(ln, teams);

            break;
        } 
        ln++; 
    }

    free_all(games, teams);
    return 0;
}