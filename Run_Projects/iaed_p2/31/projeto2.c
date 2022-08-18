#include "MAIN_FUNTIONS.h"


/* Reads the commands and executes it and terminates when appears the command x. */
int main(){
    
    char command;

    /* The number of line of command input. */
    int NL = 0;

    /* Hashtable of linked list  of teams. */
    team ** team_hash = NULL;

    /* Hashtable of linked list  of games. */
    Game ** game_hash = NULL;
    

    team_hash = init_team(team_hash);
    
    game_hash = init_game(game_hash);

    while((command = getchar()) != 'x'){

        NL++;
        
        /* In the commands who has getchar, remove the space between command and arguments.
            so the hash dont catch this space. */
        switch(command){
            case 'a':
                getchar();
                add_game(game_hash, team_hash, NL); 
                break;

            case 'l':
                show_list_game(game_hash, NL);
                break;

            case 'p':
                getchar();
                search_game(game_hash, NL);
                break; 

            case 'r':
                getchar();
                delete_game(game_hash, NL);
                break; 
    
            case 's':
                getchar();
                change_score_game(game_hash, NL);
                break;
            
            case 'A':
                getchar();
                add_team(team_hash, NL);
                break;
            
            case 'P':
                getchar();
                team_search(team_hash, NL);
                break;
            
            case 'g':
                most_vitories(team_hash, NL);
                break;
        }

        /* catch \n*/ 
        getchar();
    }
    
    team_hash = destroy_full_team(team_hash);
    game_hash = destroy_full_game(game_hash);
    return 0;
}