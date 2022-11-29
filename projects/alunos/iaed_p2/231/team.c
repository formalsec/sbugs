#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "team.h"

int hashTeam(char *name){
    int h = 0, a = 127;
    for (; *name != '\0'; name++)
        h = (a*h + *name) % MT;
    return h;
}


TeamNode* addTeam(TeamNode *head,char *n){
    TeamNode *new;
    new=can_fail_malloc(sizeof(TeamNode));
    new->name=can_fail_malloc(strlen(n)*sizeof(char));
    strcpy(new->name,n);
    new->wins=0;
    new->exists=1;
    if(head!=NULL)
        new->next=head;
    return new;
        
}

TeamNode* searchTeam(TeamNode *head,char *n){
    TeamNode *node,*ret;
    node=head;
    if(head==NULL){
        ret=can_fail_malloc(sizeof(TeamNode));
        ret->exists=0;
        return ret;
    }
    if(strcmp(n,head->name)==0)
        return head;
    while(node->next!=NULL){
        if(strcmp(n,node->name)==0)            
            return node;
        else
            node=node->next;
    }
    ret=can_fail_malloc(sizeof(TeamNode));
    ret->exists=0;
    return ret;
}
