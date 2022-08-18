#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_lists.h"

/*----------functions for ocuppied indexes of ht-----------*/
/* Adiciona um novo no a lista, alocando a memoria necessaria */
indexNode * _add_index_(indexNode * head, int c){

    indexNode * new;

    new = (indexNode *) malloc(sizeof(indexNode));
    new->next = head;
    new->s = c;

    return new;

}

/* Destroi e free de toda a lista de head*/
indexNode * _destroy_list_(indexNode * head){

    indexNode * aux;

    while(head != NULL){
        aux = head;
        head = head->next;
        free(aux);
    }

    return NULL;

}




/*------------functions for list of teams-------------*/
/* Adiciona um novo no de equipa a lista e liga os dados
da equipa a esse no */
nodeTeam * _push_team_(nodeTeam * head, char * name){

    nodeTeam * new;
    Team * team_addr;
    char * team_name;

    new = (nodeTeam *) malloc(sizeof(nodeTeam));
    team_addr = (Team * ) malloc(sizeof(Team));
    team_name = (char * ) malloc(sizeof(char)*(strlen(name)+1));

    strcpy(team_name, name);
    
    team_addr->name = team_name;
    team_addr->wins = 0;
    new->next = head;
    new->team = team_addr;
    head = new;

    return head;

}




/* Destroi toda a lista de nos de equipas e da free 
da memoria alocada para as equipas */
nodeTeam * _destroy_team_(nodeTeam * head){

    nodeTeam * aux;
    while(head != NULL){
        aux = head;
        head = head->next;
        free(aux->team->name);
        free(aux->team);
        free(aux);
    }
    return NULL;

}




/* Verifica a existencia de um jogo. Se existir retorna
o endereco de memoria, senao retorna NULL */
nodeTeam * _is_team_(nodeTeam * head, char * name){

    while(head != NULL){
        if(strcmp(head->team->name, name)==0)
            return head;
        head = head->next;
    }
    return NULL;

}








/*------------functions for list of games-------------*/
/* Adicona um novo no de jogo a lista e aloca a memoria para guardar
a info do jogo com respetivas strings */
nodeGame * _push_game_(nodeGame * head, char * name, int id, int score1, int score2,
                        char * team1, char * team2){

    nodeGame * new;
    Game * game_addr;
    char * game_name;
    char * team1_name;
    char * team2_name;

    new = (nodeGame *) malloc(sizeof(nodeGame));
    game_addr = (Game * ) malloc(sizeof(Game));
    game_name = (char *) malloc(sizeof(char)*(strlen(name)+1));
    team1_name = (char *) malloc(sizeof(char)*(strlen(team1)+1));
    team2_name = (char *) malloc(sizeof(char)*(strlen(team2)+1));

    strcpy(game_name, name);
    strcpy(team1_name, team1);
    strcpy(team2_name, team2);

    game_addr->name = game_name;
    game_addr->id = id;
    game_addr->score1 = score1;
    game_addr->score2 = score2;
    game_addr->team1 = team1_name;
    game_addr->team2 = team2_name;
    new->next = head;
    new->game = game_addr;

    return new;

}


/* Elimina o jogo name da lista de head. Retorn a nova head*/
nodeGame * _del_game_(nodeGame * head, char * name){


    nodeGame * temp, * aux;
    temp = head;
    
    /*caso da lista vazia*/
    if(temp == NULL)
        return NULL;

    /*caso em que o jogo a eliminar eh imediatamente o primeiro da lista*/
    if((temp != NULL) && (strcmp(temp->game->name, name)==0)){

        aux = temp->next;
        free(temp->game->name);
        free(temp->game->team1);
        free(temp->game->team2);
        free(temp->game);
        free(temp);
    
        return aux;

    }
    
    /*percorre a lista ate que temp seja o elemento imediatamente anterior
    ao jogo que sera eliminado*/
    while((temp != NULL) && (strcmp(temp->next->game->name, name)!=0)){

        temp = temp->next;

    }

    /*aux guarda o endereco de jogo a eliminar*/
    aux = temp->next;

    /*a lista deixa de incluir o jogo*/
    temp->next = temp->next->next;

    free(aux->game->name);
    free(aux->game->team1);
    free(aux->game->team2);
    free(aux->game);
    free(aux);

    return head;

}


/* Verifica a existencia de um jogo. Se existir retorna
o endereco de memoria, senao retorna NULL */
nodeGame * _is_game_(nodeGame * head, char * name){

    while(head != NULL){

        if(!strcmp(head->game->name, name))
            return head;

        head = head->next;

    }

    return NULL;
}


/* Destroi uma lista de nos de jogos e da free das estruturas
de jogos que lhe estao associadas*/
nodeGame * _destroy_game_(nodeGame * head){

    nodeGame * aux;

    while(head != NULL){

        aux = head->next;
        free(head->game->name);
        free(head->game->team1);
        free(head->game->team2);
        free(head->game);
        free(head);
        head = aux;

    }

    return NULL;

}