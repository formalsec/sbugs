#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include "football_mainfunctions.h"

int main()
{
    /* Pointer to the hashtable containing the games and teams. */
    Game_Link* headsGames;
    Team_Link* headsTeams;
    /* Pointer to the Head and Tail of the linked list 
       containing the games by insertion order.        */
    List_Limits headAndTail;

    int c = 0; /* Variable that reads the command characters. */
    int NL = 0; /* Variable that contains the input line. */
    int exit = 0; /* Flag that determines program exit; 
                     exit == 1 -> exit while cycle.     */

    headsGames = initGameTable();   /* Initializes the games hashtable to NULL. */
    headsTeams = initTeamTable();   /* Initializes the teams hashtable to NULL. */

    /* Initializes the Head and Tail to NULL. */
    headAndTail = can_fail_malloc(sizeof(struct connected_list));
    headAndTail->head = NULL;
    headAndTail->tail = NULL;

    /* While cycle to read the command characters and call the functions. */
    while (exit == 0){
        switch(c = getchar()){
            case 'a':
                NL++;
                c = getchar(); /* Reads spacebar after each case. */
                addGame(NL, headsGames, headAndTail, headsTeams);
                break;
            case 'l':
                NL++;
                listGames(NL, headAndTail);
                break;
            case 'p':
                NL++;
                c = getchar();
                findGame(NL, headsGames);
                break;
            case 'r':
                NL++;
                c = getchar();
                removeGame(NL, headsGames, headAndTail, headsTeams);
                break;
            case 's':
                NL++;
                c = getchar();
                changeScore(NL, headsGames, headsTeams);
                break;
            case 'A':
                NL++;
                c = getchar();
                addTeam(NL, headsTeams);
                break;
            case 'P':
                NL++;
                c = getchar();
                findTeam(NL, headsTeams);
                break;
            case 'g':
                NL++;
                findWinningTeams(NL, headsTeams);
                break;
            case 'x':
                NL++;
                break;
            case EOF:
                exit = 1;   /* Exit case. */
        }
        c = getchar();
    }

    /* Frees the hashtables and the Games list. */
    freeTeams(headsTeams);
    freeGamesList(headAndTail);
    freeGamesTable(headsGames);

    return 0;
}
