#include "linked_list.h"

/* ------ Games linked lists functions ------ */

nodeGame pushGame(nodeGame head, Game pgame){
    nodeGame n = malloc(sizeof(struct node_game));
    n->next = head;
    n->ptr = pgame;
    return n;
}

nodeGame popGame(nodeGame head, char *game_name){
    nodeGame aux, prev;
    
    for(aux = head, prev = NULL; aux != NULL; prev = aux, aux = aux->next){
        if(strcmp(aux->ptr->name, game_name) == 0){
            if(aux == head)
                head = aux->next;
            else
                prev->next = aux->next;
            /* No free in the game */
            free(aux);
            break;
        }
    }

    aux = NULL;
    prev = NULL;
    return head;
}

nodeGame destroyLinkedGames(nodeGame head){
    nodeGame aux;

    while(head != NULL){
        aux = head->next;
        free(head);
        head = aux;
    }
    aux = NULL;

    return NULL;
}


/* ------ Teams linked lists functions ------ */

nodeTeam pushTeam(nodeTeam head, Team pteam){
    nodeTeam n = malloc(sizeof(struct node_team));
    n->next = head;
    n->ptr = pteam;

    return n;
}

nodeTeam destroyLinkedTeams(nodeTeam head){
    nodeTeam aux;
    while(head != NULL){
        aux = head->next;
        free(head);
        head = aux;
    }
    aux = NULL;

    return NULL;
}
