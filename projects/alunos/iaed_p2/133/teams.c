#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*including the functions that handle teams*/
#include "teams.h"
/*including the functions that handle every auxiliary file */
#include "shared.h"




/*000000000000000000000000000000000
00000000000000000000000000000000000

    init_teams

00000000000000000000000000000000000    
00000000000000000000000000000000000*/

void init_teams(teams **lst_teams, int size)
{
    int i;
    /*for the entire hash*/
    for(i = 0; i<size; i++)
    {
        /*initializing every linked list */
        lst_teams[i]=NULL; 
    }
}



/*000000000000000000000000000000000
00000000000000000000000000000000000

    new_team

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*creating the structure of a team*/
teams* new_team(teams* team, char *name)
{
    /*initializing the structure and the game s info*/
    team->name = strduplicate(name);
    team->games_w = 0;
    team->next = NULL;
    return team;
}




/*000000000000000000000000000000000
00000000000000000000000000000000000

    add victory

00000000000000000000000000000000000
0000000000000000000000000000000000*/

/*add s a vistory to a team*/
void add_victory(teams **lst_teams, char* name)
{
    /*getting the team and incrementing the number of games won*/
    teams *team = get_team(lst_teams, name);
    team->games_w++;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    remove_victory

00000000000000000000000000000000000
0000000000000000000000000000000000*/

/*removing a victory from a given team*/
void remove_victory(teams **lst_teams, char *name)
{
    /*getting the team and decrementing the number of games won*/
    teams *team = get_team(lst_teams, name);
    team->games_w--;
}




/*00000000000000000000000000000000000
0000000000000000000000000000000000000

    look_team

0000000000000000000000000000000000000
000000000000000000000000000000000000*/

/*checks if a certain team already exits*/
int look_team(teams **lst_teams, char *name)
{
    /*variables*/
    int i = hash(name);
    teams *head = lst_teams[i];

    /*for the entire linked list*/
    for(; head!=NULL; head = head->next)
    {
        /*if the name matches*/
        if(strcmp(head->name, name)==0)
            /*returns 1 if the name already exits*/
            return 1;
    }
    /*returns 0 if the name doesn't exist*/
    return 0;
}





/*00000000000000000000000000000000000
0000000000000000000000000000000000000

    insert_new_team

0000000000000000000000000000000000000
000000000000000000000000000000000000*/

/*insertion of a new item at the beggining*/
void insert_new_team(teams **lst_teams, teams *new)
{
    /*variables*/
    teams *head;
    int i;

    /*getting the indice*/
    i = hash(new->name);
    head = lst_teams[i];
    /*inserting at the beggining*/
    lst_teams[i] = new;
    new->next = head;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    get_team

00000000000000000000000000000000000
0000000000000000000000000000000000*/

/*getting the team with a given name*/
teams* get_team(teams **lst_teams, char *name)
{
    /*variables*/
    int i=hash(name);
    teams *head = lst_teams[i]; 

    /*search in the correct list*/
    for(; head!=NULL; head = head->next)
    {
        if(strcmp(head->name, name)==0)
        {
            return head;
        }
    }
    /*if no team has that team*/
    return NULL;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    best_teams
    
00000000000000000000000000000000000    
000000000000000000000000000000000*/

/*knowing the highest number of victories*/
int most_wins(teams **lst_teams)
{
    int i=0, best_res=0;
    teams *head;

    /*for the entire hash*/
    for(i=0; i<=517; i++)
    {
        /*for the entire linked list*/
        for(head=lst_teams[i]; head!=NULL; head = head->next)
        {
            /*if the team has more victories than the other teams so far*/
            if(head->games_w > best_res)
            {
                best_res = head->games_w;
            }
        }
    }
    return best_res;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    clear_the_teams
    
00000000000000000000000000000000000    
0000000000000000000000000000000000*/

void clear_the_teams(teams **lst_teams)
{
    teams *i, *follow;
    int j;
    /*for the entire hash*/
    for(j=0; j<517; j++)
    {
        /*for every linked list*/
        for(i=lst_teams[j], follow = i; follow!=NULL;)
        {
            /*free every structure within the list*/
            i = follow;
            follow = i->next;
            free(i->name);
            free(i);
        }
    }
    /*free the list teams*/
    free(lst_teams);
}