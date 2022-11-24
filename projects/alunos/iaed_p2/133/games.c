#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*including the funtions tha handle the games*/
#include "games.h"
/*including the functions that are shared in every file*/
#include "shared.h"



/*000000000000000000000000000000000
00000000000000000000000000000000000

    init games
    
00000000000000000000000000000000000
0000000000000000000000000000000000*/

/*initialing the hash of games*/
void init_games(games **lst_games, int size)
{
    int i; 
    /*for every indice of the hash*/
    for(i = 0; i<=size; i++)
    {
        /*pointing them to NULL*/
        lst_games[i] = NULL; 
    }
}



/*00000000000000000000000000000000000
0000000000000000000000000000000000000

    new_game

0000000000000000000000000000000000000
00000000000000000000000000000000000*/

/*creating a new structure and giving it the info that we want*/
games * new_game(games *game, char *name, char *team1, char *team2, int score1, int score2)
{
    game->name = strduplicate(name);
    game->team1 = strduplicate(team1);
    game->team2 = strduplicate(team2);
    game->score1 = score1;
    game->score2 = score2; 
    game->next = NULL;
    return game;
}





/*0000000000000000000000000000000000
000000000000000000000000000000000000

    look_game

000000000000000000000000000000000000
0000000000000000000000000000000000*/

/*check if a given game exists*/
int look_game(games **lst_games, char *name)
{
    /*variables*/
    int i=hash(name);
    games *head = lst_games[i]; 

    /*search in the correct linked list*/
    for(; head!=NULL; head = head->next)
    {
        /*if the name matches up*/
        if(strcmp(head->name, name)==0)
            /*returns 1 if the game already exits*/
            return 1;
    }
    /*returns 0 if it doesn t*/
    return 0;
}





/*00000000000000000000000000000000
0000000000000000000000000000000000

    insert_new_game

0000000000000000000000000000000000
000000000000000000000000000000000*/

/*insert a new game in the hash*/
void insert_new_game(games **lst_games, games *new)
{
    /*variables*/
    games *head; 
    int i = hash(new->name);

    /*insert*/
    head = lst_games[i];
    lst_games[i] = new;
    new->next = head;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    get_game
00000000000000000000000000000000000
000000000000000000000000000000000*/

/*getting the game that has a given name*/
games* get_game(games **lst_games, char *name)
{
    /*variables*/
    int i=hash(name);
    games *head = lst_games[i];

    /*search in the correct list*/
    for(; head!=NULL; head = head->next)
    {
        /*if the name matches up*/
        if(strcmp(head->name, name)==0)
        {
            break;
        }
    }
    /*return the game*/
    return head;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    who_won
    
00000000000000000000000000000000000    
000000000000000000000000000000000*/

/*know wich team won*/
int who_won(int score1, int score2)
{
    if(score1 > score2)
    {
        return 1;/*if team 1 won*/
    }
    else if(score2 > score1)
    {
        return 2;/*if team 2 won*/
    }
    else
        return 0;/*if it was a draw*/
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    remove_game
    
00000000000000000000000000000000000    
000000000000000000000000000000000*/

/*remove a game from the list of games*/
void remove_game(games **lst_games, games *game)
{
    /*variables*/
    int i = hash(game->name);
    games *head = lst_games[i];

    /*if its the first and only game of the list */
    if(strcmp(head->name, game->name)==0 && head->next == NULL)
    {
        lst_games[i]=NULL;
    }
    else
    {
        /*if its the first game of the list, but not the only*/
        if(strcmp(head->name, game->name)==0)
        {
            lst_games[i]=game->next;
        }
        else
        {
            /*for every element of the linked list*/
            for(; head!=NULL; head = head->next)
            {
                /*if the name matches up*/
                if(strcmp((head->next)->name, game->name)==0)
                {
                    break;
                }
            }
            /*eliminating the game of the list*/
            head->next=game->next;
        }
    }
    /*free the memory space of the game and ist info*/
    free(game->name);
    free(game->team1);
    free(game->team2);
    free(game);
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    clear_the_games

00000000000000000000000000000000000    
000000000000000000000000000000000*/

/*free the list of games*/
void clear_the_games(games **lst_games)
{
    games *i, *follow;
    int j;
    /*for the entire hash*/
    for(j=0; j<517; j++)
    {
        /*for every element of the list*/
        for(i=lst_games[j], follow = i; follow!=NULL;)
        {
            i = follow;
            follow = i->next;
            /*free the memory space*/
            free(i->name);
            free(i->team1);
            free(i->team2);
            free(i);
        }
    }
    /*free the list of games*/
    free(lst_games);
}
