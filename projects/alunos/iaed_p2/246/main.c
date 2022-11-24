#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include "structs.h"

/*##################################################################################################
Projeto 2 IAED 2019/2020

Project description:

Develop, in C language, a management system for a database of friendly football matches.
Interaction with the program should occur through the following commands:

- a name:team1:team2:score1:score2;      Add a new game
- A name;                                Add a new team 
- l;                                     List the games in the order they were entered
- p name;                                Lookup a game
- P name;                                Lookup a team 
- r name;                                Delete a game 
- s name:score1:score2;                  Change the game score
- g                                      Find the teams that won the most games 
- x                                      Ends the program
##################################################################################################*/


/*##################################################################################################
#                       Main function will work as a command selector                              #
##################################################################################################*/
int main(){
    link_game *htable_game = init_j();          /*creating a hashtable for games*/
    link_team *htable_team = init_t();          /*creating a hashtable for teams*/
    link_game_order ordergamelist = NULL;       /*creating a linkedlist for games*/
    link_game auxliar;                          /*creating and auxiliar to command_a*/

    int NL_counter = 1, KeepGoing = 1, score1, score2, mostvictories;
    char command, GameName[MaxSizeName], Team1Name[MaxSizeName],Team2Name[MaxSizeName];
    
    while(KeepGoing)
        {
            command = getchar();
            switch(command) 
            {
                case 'a':
                    getchar();
                    scanf("%[^:\n]:%[^:\n]:%[^:\n]:%d:%d",GameName, Team1Name, Team2Name, &score1, 
                    &score2);
                    auxliar = command_a(htable_game,htable_team, GameName, Team1Name, Team2Name, 
                    score1, score2, NL_counter);
                    if(auxliar != NULL){
                        ordergamelist = insertBegin(ordergamelist, auxliar);
                        }
                    NL_counter++;
                    break;
                case 'A':
                    getchar();
                    scanf("%[^:\n]",Team1Name);
                    command_A(htable_team, Team1Name, NL_counter);
                    NL_counter++;
                    break;
                case 'l':
                    command_l(ordergamelist,NL_counter);
                    NL_counter++;
                    break;
                case 'p':
                    getchar();
                    scanf("%[^:\n]",GameName);
                    command_p(htable_game, GameName, NL_counter);
                    NL_counter++;
                    break;
                case 'P':
                    getchar();
                    scanf("%[^:\n]",Team1Name);
                    command_P(htable_team, Team1Name, NL_counter);
                    NL_counter++;
                    break;
                case 'r':
                    getchar();
                    scanf("%[^:\n]",GameName);
                    ordergamelist = command_r(htable_game,ordergamelist, GameName, NL_counter);
                    NL_counter++;
                    break;
                case 's':
                    getchar();
                    scanf("%[^:\n]:%d:%d", GameName, &score1, &score2);
                    command_s(htable_game, GameName, score1, score2, NL_counter);
                    NL_counter++;
                    break;
                case 'g':
                    mostvictories = Lookup_BiggerNumVictories(htable_team); 
                    if(mostvictories == -1){
                        NL_counter++;
                        break;
                    }
                    printf("%d Melhores %d\n", NL_counter, mostvictories);
                    command_g(htable_team, mostvictories, NL_counter);
                    NL_counter++;
                    break;
                case 'x':
                    freeHTgame(htable_game);
                    freeHTteam(htable_team);
                    freeordergamelist(ordergamelist);
                    KeepGoing = 0;
            }
        }
    return 0;
}
