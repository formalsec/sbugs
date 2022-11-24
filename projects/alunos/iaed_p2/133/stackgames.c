#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*including the functions of that handle the games*/
#include "games.h"
/*including the functions that handle the stack of games*/
#include "stackgames.h"
/*including the functions that are shared ftom every auxiliary file*/
#include "shared.h"





/*000000000000000000000000000000000
00000000000000000000000000000000000

    create_game_stack

00000000000000000000000000000000000
0000000000000000000000000000000000*/

/*creating the node of the stocj*/
stacks* create_game_stack(char *name)
{
    stacks *new = (stacks*)can_fail_malloc(sizeof(stacks));
    new->name = strduplicate(name);
    new->next = NULL;
    return new;
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    insert_game_stack

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*insert a game in the stack*/
void insert_game_stack(char *name, stacks **stack, stacks **head_stack)
{
    /*variables*/ 
    stacks *new = create_game_stack(name);

    /*if the stack is empty*/
    if(*stack == NULL)
    {
        /*updating the stack and head*/
        *stack = new; 
        *head_stack = new;
    }
    /*if the stack is not empty*/
    else
    {
        /*updating the head of the stack*/
        (*head_stack)->next = new;
        *head_stack = new;
    }
}





/*000000000000000000000000000000000
00000000000000000000000000000000000

    remove_game_stack

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*remove a game from the stack*/
void remove_game_stack(stacks **stack, games *game, stacks **head)
{
    /*variables*/
    stacks *i = *stack;  
    stacks *follow = i->next;

    /*if its in the first position*/
    if(strcmp(i->name, game->name) == 0)
    {
        /*free the node*/
        *stack = i->next;
        free(i->name);
        free(i);
    }
    /*if its not in the first position*/
    else
    {
        /*reaching the spot where the game is in*/
        for(; follow!=NULL; i = i->next, follow = follow->next)
        {
            /*if the following is what we want*/
            if(strcmp(follow->name,game->name) == 0)
            {
                /*removing the game from the linked list*/
                i->next = follow->next; 
                break;
            }
        }
        if(strcmp(follow->name, (*head)->name)==0)
        {
            *head = i;
        }
        /*free the node*/
        free(follow->name);
        free(follow);
    }
}






/*000000000000000000000000000000000
00000000000000000000000000000000000

    print_stack

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*print the stack games*/
void print_stack(games **lst_games, stacks **stack, int nl)
{
    /*variables*/
    stacks *i = *stack;
    games *read;
    /*if the stack isnt empty*/
    if(*stack != NULL)
    {
        /*for every element*/
        for(; i!=NULL; i = i->next)
        {
            /*get the game*/
            read = get_game(lst_games, i->name);
            /*print the games info*/
            printf("%d %s %s %s %d %d\n", nl, read->name, read->team1, read->team2,
                                        read->score1, read->score2);
        }
    }
    /*if the stack is empty, doesnt do nothing*/
}






/*000000000000000000000000000000000
00000000000000000000000000000000000

    free_stack_games

00000000000000000000000000000000000
000000000000000000000000000000000*/

/*free the stack games*/
void free_stack_games(stacks **stack, stacks **head)
{
    stacks *i = *stack;
    stacks *follow = i;
    /*for every element in the stack*/
    for(; follow!=NULL;)
    {
        i = follow;
        follow = i->next;
        /*free the node*/
        free(i->name);
        free(i);
    }
    /*free the head*/
    free(head);
    /*free the stack*/
    free(stack);
    
}
