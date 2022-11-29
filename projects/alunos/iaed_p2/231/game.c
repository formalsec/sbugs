#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "game.h"


int hashGame(char *name){
    int h = 0, a = 127;
    for (; *name != '\0'; name++)
        h = (a*h + *name) % MG;
    return h;
}

GameNode* addGame(GameNode *head,char *n,TeamNode *t1,TeamNode *t2,int s1,int s2,int gameNumber){
    GameNode *new;
    new=can_fail_malloc(sizeof(GameNode));
    new->name=can_fail_malloc(strlen(n)*sizeof(char));
    strcpy(new->name,n);
    new->team1=t1;
    new->team2=t2;
    new->score1=s1;
    new->score2=s2;
    new->id=gameNumber;
    if(s1>s2)
        t1->wins++;
    else
        t2->wins++;
    
    /*if it's not the first game, put it in the beggining*/
    if(head!=NULL)
        new->next=head;
    return new;
}

GameNode* searchGame(GameNode *head,char *n){
    GameNode *node,*ret;
    node=head;
    if(strcmp(n,head->name)==0)
        return head;
    while(node->next!=NULL){
        if(strcmp(n,node->name)==0)            
            return node;
        else
            node=node->next;
    }
    ret=can_fail_malloc(sizeof(GameNode));
    ret->id=0;
    return ret;
}

/*function that returns the head of a new list without game in it*/
GameNode* deleteGame(GameNode *head,GameNode *game){
    GameNode *node;
    node=head;
    if(game->score1>game->score2)
        game->team1->wins--;
    else
        game->team2->wins--;
    
    /*verifies if the target is the head,then remove it*/
    if(strcmp(game->name,head->name)==0){
        /*if the head isnt the only game, make the next game head*/
        if(head->next!=NULL)
            node=head->next;
        free(head);
        return node;
    }
    /*if the target wasnt the first one, */
    while(node->next!=NULL){
        if(strcmp(node->next->name,game->name)==0){
            if(node->next->next!=NULL)
                node->next = node->next->next;
            free(game);
            return head;
        }
        else{
            node=node->next;
        }
    }
    return head;

}

void changeScore(GameNode *game,int s1, int s2){
    /* "refreshes" the winner of that game*/
    if(game->score1 > game->score2)
        game->team1->wins--;
    else
        game->team2->wins--;
    if(s1>s2)
        game->team1->wins++;
    else
        game->team2->wins++;

    game->score1=s1;
    game->score2=s2;
}
