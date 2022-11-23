#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gamesList.h"

/*-----------------------------------------------------------------------------------*/
gameListP initGamesList() {

    gameListP gameList;

    /* Aloca memoria para uma lista de ponteiros para jogos */
    gameList = (List*) can_fail_malloc (sizeof(List));

    /* Inicializa a cabeca e a cauda a NULL */
    gameList->head = NULL;
    gameList->last = NULL;

    return gameList;
}

/*----------------------------------------------------------------------------------*/
void addGameList(gameListP gameList, gameNodeP game) {

    /* Se a lista for vazia, define a head e o last como o elemento */
    if (gameList->head == NULL) {
        gameList->head = game;
        gameList->last = game;
    }
    /* Se nao, adiciona o elemento no inicio da lista e nao mexe no last*/
    else {
        game->nextL= gameList->head;
        gameList->head->previous =game;
        gameList->head = game;
    }

}

/*----------------------------------------------------------------------------------*/
void listGames(gameListP gameList, int cont) {

    gameNodeP x;

    /* Se existir algum jogo na lista */
    if (gameList->head != NULL) {

        /* Percorre a lista e imprime a informacao sobre o jogo */
        for (x= gameList->last; x != NULL ; x = x->previous) {
            printf("%d %s %s %s %d %d\n", cont, x->game->name, x->game->team1->name, x->game->team2->name, x->game->score1, x->game->score2);
        }
    }

}

