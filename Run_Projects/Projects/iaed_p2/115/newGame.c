#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "newGame.h"

/*------------------------------------------------------------------------------------------------*/
int hashU(char *v, int M) {
    int h;

    /* Soma dos caracteres ASCII do input */
    for (h = 0; *v != '\0'; v++)
        h += *v;
    /* Resto de divisao por 31 */
    h= h % M;
    return h;
}

/*------------------------------------------------------------------------------------------------*/
gameNodeP newGame(TeamsHash *HashT, char* name, char* eq1, char* eq2, int score1, int score2) {

    /* Ponteiro para um jogo */
    Game * game;

    /* Ponteiro para um no de equipa */
    teamNodeP x;

    gameNodeP new_game;

    /* Vai buscar os indices da Hash Table de cada equipa */
    int a= hashU(eq1, HashT->size), b=hashU(eq2, HashT->size);

    teamNodeP *headsT = HashT->headsT;

    /* Aloca memoria para um jogo */
    game = (Game*) malloc (sizeof(Game));

    /* Aloca memoria para o nome do jogo */
    game->name = (char*) malloc (sizeof(char)*strlen(name)+1);
    strcpy(game->name, name);

    /*Procura a equipa na hashtable e adiciona ao struct jogo quando a encontrar*/
    for (x = headsT[a]; x != NULL; x = x->next) {

        if (strcmp (x->team->name, eq1) == 0) {
            game->team1 = x->team ;

            /* Acerta as vitorias da equipa vencedora */
            if (score1 > score2) {
                (x->team->wins)++;
            }
        }
    }

    /* Igual mas para a segunda equipa */
    for (x = headsT[b]; x != NULL; x = x->next) {

        if (strcmp (x->team->name, eq2) == 0) {
            game->team2 = x->team ;
            
            if (score2 > score1) {
                (x->team->wins)++;
            }
        }
    }

    /* Atribui os scores a um jogo */
    game->score1 = score1;
    game->score2 = score2;

    new_game = newGameNode(game);

    return new_game;

}

/*------------------------------------------------------------------------------------------------*/
gameNodeP newGameNode(Game* game) {

    /* Aloca memoria para um ponteiro para jogo */
    GameNode *newGame = (GameNode*) malloc (sizeof(GameNode));

    /* Inicializa as variaveis */
    newGame->game = game;
    newGame->nextH = NULL;
    newGame->nextL = NULL;
    newGame->previous = NULL;
    newGame->prevH = NULL;

    return newGame;
}

/*------------------------------------------------------------------------------------------------*/
void removeWin(Game* game) {

    if (game->score1 > game->score2) {
        (game->team1->wins)--;
    }
    else if (game->score1 < game->score2) {
        (game->team2->wins)--;
    }
}

