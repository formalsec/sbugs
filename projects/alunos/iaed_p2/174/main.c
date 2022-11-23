#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include "btteam.h"
#include "btgame.h"
#include "commands.h"

int main() {
    /* Avore binaria que armazena todas as equipas. */
    BTTeam *teams = newBTTeam();
    /* Avore binaria que armazena todos os jogos. */
    BTGame *games = newBTGame();

    int nl = 0;        /* Numero da linha. */
    int c = getchar(); /* Letra do comando. */

    while (c != EOF && c != 'x') {
        nl++; /* Incrementar numero de linha. */

        if (c == 'a')
            /* Adiciona um novo jogo. */
            createGameCmd(nl, teams, &games);
        else if (c == 'l')
            /* Lista todos os jogos pela ordem em que foram introduzidos. */
            listAllGamesCmd(nl, games);
        else if (c == 'p')
            /* Procura um jogo. */
            searchGameCmd(nl, games);
        else if (c == 'r')
            /* Apaga um jogo. */
            deleteGameCmd(nl, &games);
        else if (c == 's')
            /* Altera a pontuacao de um jogo. */
            changeGameScoresCmd(nl, games);
        else if (c == 'A')
            /* Adiciona uma nova equipa. */
            createTeamCmd(nl, &teams);
        else if (c == 'P')
            /* Procura uma equipa. */
            searchTeamCmd(nl, teams);
        else if (c == 'g')
            /* Encontra as equipas que venceram mais jogos. */
            bestTeamsCmd(nl, teams);
        else if (c != '\n') {
            printf("Comando inexistente: '%c'.\n", c);
        }

        /* Ignorar ateh proximo caracter de nova linha ou fim de ficheiro. */
        while (c != EOF && c != '\n') {
            c = getchar();
        }

        c = getchar();
    }

    /* Libertar a memoria dos jogos, equipas e arvores binarias. */
    freeBTGame(games);
    freeBTTeam(teams);

    return 0;
}
