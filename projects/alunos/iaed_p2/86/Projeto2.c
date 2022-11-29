#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include "Projeto2.h"


int main()
{   
    /*Inicia a Hash Table para guardar os jogos*/
    gameLink* hashGameTable = InitGameHash(HASH_NUM_GAMES);
    /*Inicia a Hash Table para guardae as equipas*/
    teamLink* hashTeamTable = InitTeamHash(HASH_NUM_TEAMS);
    /*Inicia a Lista de jogos utilizada somente para guardar a ordem de introducao dos jogos*/
    gameLink headGame = NULL;
    gameLink tailGame = NULL;
    /*Variavel que ira guardar o numero de comandos executados*/
    int nrCommand = 0;

    /*Main Loop*/
    while(scanCommand(&nrCommand, hashTeamTable, &headGame, hashGameTable, &tailGame));
    /*Free de toda a memoria alocada*/
    freeTeamHash(hashTeamTable);
    freeGameHash(hashGameTable);
    freeGameList(headGame);
    return 0;
}

