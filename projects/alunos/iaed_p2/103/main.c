#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include "games.h"
#include "teams.h"

int main(){
    char command;
    int line = 0;
    list_games *lgptr = makeListGames();
    list_games **hash_games = makeHashGames();
    team_node **hash_teams = makeHashTeams();
    while ((command = getchar()) != 'x'){
        if (command == '\n'){
            continue;
        }
        line++;
        switch (command){
        case 'a':
            addGame(lgptr, hash_games, hash_teams, line);
            break;
        case 'A':
            addTeam(hash_teams, line);
            break;
        case 'l':
            listGames(lgptr, line);
            break;
        case 'p':
            searchGame(hash_games, line);
            break;
        case 'P':
            searchTeam(hash_teams, line);
            break; 
        case 'r':
            deleteGame(lgptr, hash_games, hash_teams, line);
            break;
        case 's':
            changeScore(hash_games, hash_teams, line);
            break;
        case 'g':
            findChampions(hash_teams, line);
            break;
        }
    }
    freeAllMemoryGames(lgptr, hash_games);
    freeAllMemoryTeams(hash_teams);
    return 0;
}
