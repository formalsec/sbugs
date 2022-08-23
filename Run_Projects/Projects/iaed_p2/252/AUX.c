#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AUX.h"


/*Funcao que percorre a cria a lista de equipas e mete os valores da hashtable a NULL*/
team_list* AlocaEquipas() 
{
    int i;
    team_list *lista = malloc(sizeof(team_list));
    lista->head = NULL;
    lista->last = NULL;
    lista->hashtable = malloc(sizeof(Equipa) * HASHSIZE);
    for (i = 0; i < HASHSIZE; i++) 
    {
        *(lista->hashtable+i) = NULL;
    }

    return lista;
}

/*Funcao que percorre a cria a lista de jogos e mete os valores da hashtable a NULL*/
game_list* AlocaJogos() 
{
    int i;
    game_list *lista = malloc(sizeof(game_list));
    lista->head = NULL;
    lista->last = NULL;
    lista->hashtable = malloc(sizeof(Jogo) * HASHSIZE);
    for (i = 0; i < HASHSIZE; i++) 
    {
        *(lista->hashtable+i) = NULL;
    }

    return lista;
}


/*Funcao que percorre lista de equipas e liberta a memoria*/
void freeList(team_list* l) 
{
    Equipa* next_team;

    while (l->head != NULL) 
    {
        next_team = l->head->next;
        
        free(l->head->nome);
        free(l->head);

        l->head = next_team;
    }

    free(l->hashtable);
    free(l);

    return;
}

/*Funcao que percorre lista de jogos e liberta a memoria*/
void freeGameList(game_list* l) 
{
    Jogo* next_team;

    while (l->head != NULL) 
    {
        next_team = l->head->next;
        
        free(l->head->nome);
        free(l->head->equipa1);
        free(l->head->equipa2);

        free(l->head);

        l->head = next_team;
    }

    free(l->hashtable);
    free(l);

    return;
}