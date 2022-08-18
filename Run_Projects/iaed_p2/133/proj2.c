#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*include funcitons for handling teams*/
#include "teams.h"
/*include functions for handling games*/
#include "games.h"
/*include funtions for the stack games*/
#include "stackgames.h"
/*include functions for handling the nest teams*/
#include "besteams.h"
/*include functions that are used in this file and all of the other auxilary files*/
#include "shared.h"




/*00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

    functions

0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000*/


/*00000000000000000000000000000000000
0000000000000000000000000000000000000

    add_team
    
0000000000000000000000000000000000000    
00000000000000000000000000000000000*/

void add_team(teams **lst_teams, int nl)
{
    /*variables*/
    char name_aux[1024];

    /*read the name from input*/
    scanf(" %[^:\n]", name_aux);

    /*error: if the team already exits*/
    if(look_team(lst_teams, name_aux)==1)
        printf("%d Equipa existente.\n", nl);
    
    /*add the new team to the list*/
    else
    {
        /*variables*/
        teams *team = (teams*)malloc(sizeof(teams));
        
        /*insert*/
        team = new_team(team, name_aux);
        insert_new_team(lst_teams, team);
    }
    
}



/*0000000000000000000000000000000000
000000000000000000000000000000000000

    add_game

000000000000000000000000000000000000
0000000000000000000000000000000000*/

void add_game(games **lst_games, teams **lst_teams, int nl, stacks **stack, stacks **head_stack)
{
    /*variables*/
    int score1, score2; 
    char name_aux[1024], team1_aux[1024], team2_aux[1024]; 
    
    /*read from input*/
    scanf(" %[^:\n]:%[^:\n]:%[^:\n]:%d:%d", name_aux, team1_aux, team2_aux, &score1, &score2);

    /*if the game already exists*/
    if(look_game(lst_games, name_aux)==1)
        printf("%d Jogo existente.\n", nl);
    
    /*if the first team doesnt exist*/
    else if(look_team(lst_teams, team1_aux)==0)
        printf("%d Equipa inexistente.\n", nl);
    
    /*if the second team doesnt exist*/
    else if(look_team(lst_teams, team2_aux)==0)
        printf("%d Equipa inexistente.\n", nl);
    

    /*if everythings ok*/
    else
    {
        /*variables*/
        games * game = (games*)malloc(sizeof(games));

        /*creating the structure*/
        game = new_game(game, name_aux, team1_aux, team2_aux, score1, score2);
        /*inserting the game in the hash*/
        insert_new_game(lst_games, game);
        /*inserting the game in the stack*/
        insert_game_stack(name_aux, stack, head_stack);

        /*if first team won*/
        if(who_won(score1, score2)==1)
        {
            /*adds victory to team1*/
            add_victory(lst_teams, team1_aux);
        }
        else if(who_won(score1, score2)==2)
        {
            /*adds victory to team2*/
            add_victory(lst_teams, team2_aux);
        }
    }
}



/*0000000000000000000000000000000000
000000000000000000000000000000000000

    search_game

0000000000000000000000000000000000
00000000000000000000000000000000*/

void search_game(games **lst_games, int nl)
{
    /*variables*/
    char name_aux[1024];

    /*get the name from the input*/
    scanf(" %[^:\n]", name_aux);
    
    /*if the game doesnt exist*/
    if(look_game(lst_games, name_aux)==0)
    {
        printf("%d Jogo inexistente.\n", nl);
    }
    /*if the game exits*/
    else
    {
        /*getting the game*/
        games *game = get_game(lst_games, name_aux);
        /*printing the game info*/
        printf("%d %s %s %s %d %d\n", nl, game->name, game->team1, game->team2,
                                    game->score1, game->score2);
    }
}



/*0000000000000000000000000000000000
000000000000000000000000000000000000

    search_team

000000000000000000000000000000000000
0000000000000000000000000000000000*/

void search_team(teams ** lst_teams, int nl)
{
    /*variables*/
    char  name_aux[1024];

    /*get the name from the input*/
    scanf(" %[^:\n]", name_aux);
    
    /*if the team doesnt exist*/
    if(look_team(lst_teams, name_aux)==0)
    {
        printf("%d Equipa inexistente.\n", nl);
    }
    /*if the team exits*/
    else
    {
        /*getting the team*/
        teams *team = get_team(lst_teams, name_aux);
        /*printing the team s info*/
        printf("%d %s %d\n", nl, team->name, team->games_w);
    }
}



/*000000000000000000000000000000000
00000000000000000000000000000000000

    change_score

00000000000000000000000000000000000
00000000000000000000000000000000*/

void change_score(games **lst_games, teams **lst_teams, int nl)
{
    /*variables*/
    char name_aux[1024];
    int score1, score2; 

    /*read from the input*/
    scanf(" %[^:\n]:%d:%d", name_aux, &score1, &score2);

    if(look_game(lst_games, name_aux)==0)
    {
        printf("%d Jogo inexistente.\n", nl);
    }
    else
    {
        /*getting the game*/
        games *game = get_game(lst_games, name_aux);
        /*know who won previously*/
        int old = who_won(game->score1, game->score2);/*0 = draw, 1=team1 won, 2=team2 won*/
        /*know who actually won*/
        int new = who_won(score1, score2);/*0 = draw, 1=team1 won, 2=team2 won*/

        if(old != new)
        {
            /*change to draw*/
            if(new == 0)
            {
                if(old == 1)
                    /*remove the victory from team1*/
                    remove_victory(lst_teams, game->team1);

                else
                    /*remove the victory from team2*/
                    remove_victory(lst_teams, game->team2);
            }
            /*if someone actually won, and it was a draw */
            else if(old==0)
            {
                if(new == 1)
                    /*add a victory to team 1*/
                    add_victory(lst_teams, game->team1);
                else
                    /*add a victory to team 2*/
                    add_victory(lst_teams, game->team2);
            }
            /*different winner*/
            else
            {
                /*if the actual winner is team1*/
                if(new == 1)
                {
                    /*remove victory to team2 and add one to team1*/
                    remove_victory(lst_teams, game->team2);
                    add_victory(lst_teams, game->team1);
                }
                else
                {
                    /*remove victory to team 1 and add one to team2*/
                    remove_victory(lst_teams, game->team1);
                    add_victory(lst_teams, game->team2);
                }
            }
        }
        /*updating the score*/
        game->score1=score1;
        game->score2=score2;
    }
}



/*0000000000000000000000000000000
000000000000000000000000000000000

    delete_game

00000000000000000000000000000000    
000000000000000000000000000000*/

void delete_game(games **lst_games, teams **lst_teams, int nl, stacks **stack, stacks **head_stack)
{
    /*variables*/
    char name_aux[1024];

    /*read the name from input*/
    scanf(" %[^:\n]", name_aux);

    /*if the game doesnt exist*/
    if(look_game(lst_games, name_aux)==0)
    {
        printf("%d Jogo inexistente.\n", nl);
    }
    else
    {
        /*variables*/
        games *game;

        /*get the game*/ 
        game = get_game(lst_games, name_aux);
        
        /*if the first team won*/
        if(who_won(game->score1, game->score2)==1)
        {
            /*remove victory from team 1*/
            remove_victory(lst_teams, game->team1);
        }

        /*if the second team won*/
        else if(who_won(game->score1, game->score2)==2)
        {
            /*remove victpry from team 2*/
            remove_victory(lst_teams, game->team2);
        }

        /*remove game from the games list and stack*/
        remove_game_stack(stack, game, head_stack);
        remove_game(lst_games, game);
    }
}



/*00000000000000000000000000000
0000000000000000000000000000000

    the_best_teams
    
000000000000000000000000000000    
0000000000000000000000000000*/

void the_best_teams(teams **lst_teams, char **best_teams, int nl)
{
    int max;
    /*maximum number of victories per team*/
    max = most_wins(lst_teams);
    /*add the teams that have such numbers to the list*/
    search_and_add_teams_list(lst_teams, best_teams, max);
    /*sorting the list based on the lexicographic*/
    sort_the_list(best_teams);
    /*printing accordingly*/
    print_best_teams(best_teams, nl, max);
    /*clear the list, for the next time*/
    clear_list_teams(best_teams, 100);
}

/*00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000

    main

000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000*/

int main()
{
    /*variables*/
    char caracter;/*know the operation to do*/
    int nl=0;/*counter of lines*/
    teams ** lst_teams;/*hash of the teams*/
    games ** lst_games;/*hash of the games*/
    stacks **stack;/*stack for the games*/
    stacks **head_stack;/*auxiliary pointer to the head of the stack*/
    char **best_teams;/*list of strings, names of the best qualifiyng teams*/
    lst_teams = (teams **)malloc(sizeof(teams)*517);/*initializing main list of teams*/
    lst_games = (games **)malloc(sizeof(games)*517);/*initializing main list of games*/
    stack = (stacks **)malloc(sizeof(stacks));/*initializing the stack*/
    head_stack = (stacks **)malloc(sizeof(stacks));/*initializing the head of the stack*/
    best_teams = (char **)malloc(sizeof(char *)*100);/*initializing the list of strings*/
    init_teams(lst_teams, 517);/*all the lists pointing NULL*/
    init_games(lst_games, 517);/*all the lists pointing NULL*/
    *stack = NULL;/*stack begins in NULL*/
    *head_stack = NULL;/*head of the stack starts at NULL*/
    init_list_teams(best_teams, 100);/*initializing the list of names*/
    
    /*switch*/
    do
    {
        switch(caracter=getchar())
        {
            /*add game*/
            case 'a':
                nl++;
                add_game(lst_games, lst_teams, nl, stack, head_stack);
                break;
            
            /*add team*/
            case 'A':
                nl++;
                add_team(lst_teams, nl);
                break;
            
            /*list games in the order of introduction*/
            case 'l':
                nl++;
                print_stack(lst_games, stack, nl);
                break;
        
            /*look for a game*/
            case 'p':
                nl++;
                search_game(lst_games, nl);
                break;
            
            /*look for a team and the number of won games*/
            case 'P':
                nl++;
                search_team(lst_teams, nl);
                break;
        
            /*delete a certain game*/
            case 'r':
                nl++;
                delete_game(lst_games, lst_teams, nl, stack, head_stack);
                break;
            
            /*changing the score of a given game*/
            case 's':
                nl++;
                change_score(lst_games, lst_teams, nl);
                break;
        
            /*list the games in order of won games*/
            case 'g':
                nl++;
                the_best_teams(lst_teams, best_teams, nl);
                break;
            /*if the caracter pressed isnt any of the cases above*/
            default:
                break;  
    }   
    } while (caracter!='x');/*until the caracter is equal to 'x'*/
    /*free the stack*/
    free_stack_games(stack, head_stack);
    /*free the list of games*/
    clear_the_games(lst_games);
    clear_the_teams(lst_teams);
    /*free the list of teams*/
    free_list_teams(best_teams);
    return 0;
}

