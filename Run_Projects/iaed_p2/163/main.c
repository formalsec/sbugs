#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hashtable-structs.h"
#include "commands.h"

int main(){

    int hashtable_size = 11;
    char comando;
    int nl_counter = 0;

    link* hashtable_games = NULL;
    team_ptr list_teams = NULL;
    link list_games = NULL;


    hashtable_games = Init(hashtable_games, hashtable_size);

    /*input loop*/
    while((comando = getchar()) != 'x'){
        
        switch(comando){
            case 'a':
                nl_counter++;
                list_games = a(hashtable_games, hashtable_size
                            , list_teams, list_games, nl_counter);
                break;
            case 'A':
                nl_counter++;
                list_teams = A(list_teams, nl_counter);
                break;
            case 'p':
                nl_counter++;
                p(hashtable_games, hashtable_size, nl_counter);
                break;
            case 'P':
                nl_counter++;
                P(list_teams, nl_counter);
                break;
            case 'l':
                nl_counter++;
                l(hashtable_games, hashtable_size,list_games, nl_counter);
                break;
            case 'r':
                nl_counter++;
                list_games = r(hashtable_games, hashtable_size
                                , list_games, list_teams, nl_counter);
                break;
            case 's':
                nl_counter++;
                list_games = s(hashtable_games, hashtable_size, list_games, list_teams, nl_counter);
                break;
            case 'g':
                nl_counter++;
                g(list_teams, nl_counter);
                break;
            case '\n':
                break;
            default:
                break;
        }
    }

    /*free heap before ending program*/
    freeLink(list_games);
    freeTeamList(list_teams);
    DeleteHashtable(hashtable_games, hashtable_size);
    
    return 0;
}