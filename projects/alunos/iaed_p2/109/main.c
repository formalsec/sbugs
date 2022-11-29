#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "allfunctions.h"

/*====================================== MAIN ======================================*/

int main() {

    int cmd;
    int NL = 1;

    /* Initialize both hashtables and games list */
    HashTeam hashteams = tHashInit(INITSIZE);
    HashGame hashgames = gHashInit(INITSIZE);
    GameLink allgames = NULL;


    while ((cmd = getchar()) != EOF) {
        switch (cmd) {

            /*------------ TEAMS ------------*/
            case 'A':
                _addTeam_(&hashteams, NL);
                NL++;
                break;
            case 'P':
                _searchTeam_(hashteams, NL);
                NL++;
                break;

            /*------------ GAMES ------------*/
            case 'a':
                _addGame_(&hashgames, &allgames, hashteams, NL);
                NL++;
                break;
            case 'p':
                _searchGame_(hashgames, NL);
                NL++;
                break;
            case 'r':
                _deleteGame_(hashgames, &allgames, NL);
                NL++;
                break;
            case 'l':
                _listGames_(allgames, NL);
                NL++;
                break;
            case 's':
                _changeScore_(hashgames, NL);
                NL++;
                break;
            case 'g':
                _winningTeams_(hashteams, NL);
                NL++;
                break;

            /*------------- END -------------*/
            case 'x':
                /* Frees all memory allocated */
                tHashFree(hashteams);
                gHashFree(hashgames);
                gListFree(allgames); 
                break;
        }
    }
    return 0;
}
