#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <string.h>

#include "Team2.h"
#include "Game2.h"


#define COMMANDSZ 1025

/* Get the command string */
    void getcmd(char *cmd);


int main(){
    char cmd;
    /* The current line */
    int NL = 0;

    /* Head of the Tree which stores teams */
    BTlink Tree_team = BTinit();
    /* Head of the Tree whcih stores games */
    BGlink Tree_game = BGinit();
    int Game_elem = 0;

    Team team;

    char name[COMMANDSZ];
    char team1[COMMANDSZ];
    char team2[COMMANDSZ];
    int s1;
    int s2;

    getcmd(&cmd);
    NL++;

    /* 'x' command to end program */
    while(cmd != 'x'){
        switch(cmd){
            case 'a':
                scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name, team1, team2, &s1, &s2);
                team = addGame(name, team1, team2, s1, s2, &Tree_game, Tree_team, &Game_elem, NL);
                if (team)
                    TchangeWins(team, 1);
                break;

            case 'l':
                listAllGames(Tree_game, Game_elem, NL);
                break;

            case 'A':
                scanf(" %[^:\n]", name);
                addTeam(name, &Tree_team, NL);
                break;

            case 'p':
                scanf(" %[^:\n]", name);
                searchGame(name, Tree_game, NL);
                break;

            case 'P':
                scanf(" %[^:\n]", name);
                searchTeam(name, Tree_team, NL);
                break;

            case 'r':
                scanf(" %[^:\n]", name);
                team = deleteGame(name, &Tree_game, &Game_elem, NL);
                if (team)
                    TchangeWins(team, -1);
                break;

            case 's':
                scanf(" %[^:\n]:%d:%d", name, &s1, &s2);
                change_scores(name, s1, s2, Tree_game, NL);
                break;
                

            case 'g':
                showwinners(Tree_team, NL);
                break;
        }
        getcmd(&cmd);
        NL++;
    }
    /* Free memory allocations */
    freeAllGames(&Tree_game);
    freeAllTeams(&Tree_team);
    return 0;
}

/* Get the command string */
    void getcmd(char *cmd){
        /*
        Arguments:
            char cmd[] -- string -- string to be destructively modified
        */
        char c;
        while((c = getchar()) < 65 || c > 122);
        *cmd = c;
    }