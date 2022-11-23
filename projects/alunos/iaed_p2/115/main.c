#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "newTeam.h"
#include "hashTables.h"
#include "newGame.h"
#include "gamesList.h"

#define MAXINPUT 1024 /* Maximo de caracteres do input*/
#define M 1023 /* Tamanho inicial das HashTables */

/*------------------------------------------------------------------------------------------------------
Chama uma auxiliar para criar um struct equipa e o adiciona a uma Hash Table
--------------------------------------------------------------------------------------------------------*/
TeamsHash* adicionaEquipa(TeamsHash *HashT, int cont) {

    teamNodeP newTNode;
    char nomeEq1[MAXINPUT], *eq1;
    int c, i;

    c=getchar();
    scanf("%1023[^:\n]", nomeEq1);

    eq1= (char*) can_fail_malloc (sizeof(char)*(strlen(nomeEq1)+1));
    strcpy(eq1,nomeEq1);

    /* Verifica se a equipa ja esta no sistema (devolve -1 caso esteja) */
    i = verifyExistentTeam(HashT, eq1);

    if (c > 0 && i == -1) {
        printf("%d Equipa existente.\n", cont);
    }
    else {
        /* Cria um struct equipa */
        newTNode = newTeam(eq1);

        /* Adiciona o struct a Hash Table */
        HashT = addTeam(HashT, i,newTNode);
    }
            
    free (eq1);

    return HashT;
}

/*------------------------------------------------------------------------------------------------------
Chama uma auxiliar que procura uma equipa na Hash Table
--------------------------------------------------------------------------------------------------------*/
void procuraEquipa(TeamsHash *HashT, int cont) {

    char nomeEq1[MAXINPUT], *eq1;
    Team *team;

    scanf(" %1023[^:\n]", nomeEq1);

    eq1= (char*) can_fail_malloc (sizeof(char)*(strlen(nomeEq1)+1));
    strcpy(eq1,nomeEq1);

    /* Procura a equipa na Hash Table (devolve NULL caso nao exista) */
    team = searchTeam(HashT, eq1);

    if (team == NULL) {
        printf("%d Equipa inexistente.\n",cont);
    }
    else {
        printf("%d %s %d\n",cont, team->name, team->wins);
    }

    free (eq1);
}

/*------------------------------------------------------------------------------------------------------
Chama uma auxiliar que cria um struct jogo e adiciona a uma Hash Table e a uma lista duplamente ligada
--------------------------------------------------------------------------------------------------------*/
GamesHash* adicionaJogo(GamesHash *HashG, TeamsHash *HashT, gameListP gameList, int cont) {

    gameNodeP newGNode;
    char nomeJogo[MAXINPUT], nomeEq1[MAXINPUT], nomeEq2[MAXINPUT],*jogo, *eq1, *eq2;
    int score1=0, score2=0, a=0, b=0, d=0;

    scanf(" %1023[^:]:%1023[^:]:%1023[^:]:%d:%d", nomeJogo,nomeEq1,nomeEq2,&score1,&score2);

    jogo = (char*) can_fail_malloc (sizeof(char)*(strlen(nomeJogo)+1));
    strcpy(jogo, nomeJogo);

     /* Verifica se o jogo existe na Hash Table (devolve -1 caso exista) */
    a = verifyExistentGame(HashG, jogo);

    free(jogo);

    if (a == -1) {
        printf("%d Jogo existente.\n", cont);
    }
    else {
        eq1 = (char*) can_fail_malloc (sizeof(char)*strlen(nomeEq1)+1);
        strcpy(eq1, nomeEq1);

        eq2 = (char*) can_fail_malloc (sizeof(char)*strlen(nomeEq2)+1);
        strcpy(eq2, nomeEq2);

        /* Verifica se as equipas existem na Hash Table (devolve -1 caso existam) */
        b = verifyExistentTeam(HashT, eq1);
        d = verifyExistentTeam(HashT, eq2);

        if (b != -1 || d != -1) {
            printf("%d Equipa inexistente.\n", cont);
        }
        else {
            /* Cria um struct jogo */
            newGNode = newGame(HashT, nomeJogo, eq1, eq2, score1, score2);

            /* Adiciona o struct a uma Hash Table */
            HashG = addGameHash(HashG, a, newGNode);

            /* Adiciona o struct a uma lista para manter a ordem*/
            addGameList(gameList, newGNode);

        }

        free(eq1);
        free(eq2);
    }

    return HashG;
}

/*------------------------------------------------------------------------------------------------------
Chama uma auxiliar que procura um jogo numa Hash Table
--------------------------------------------------------------------------------------------------------*/
void procuraJogo(GamesHash *HashG, int cont) {

    Game *game;
    char nomeJogo[MAXINPUT], *jogo;
    
    scanf(" %1023[^:\n]", nomeJogo);

    jogo= (char*) can_fail_malloc (sizeof(char)*(strlen(nomeJogo)+1));
    strcpy(jogo, nomeJogo);

    /* Procura o jogo na Hash Table (devolve NULL caso nao exista) */
    game = searchGame(HashG, jogo);

    if (game == NULL) {
        printf("%d Jogo inexistente.\n", cont);
    }
    else {
        printf("%d %s %s %s %d %d\n",cont, game->name, game->team1->name, game->team2->name, game->score1, game->score2);
    }

    free(jogo);

}

/*------------------------------------------------------------------------------------------------------
Chama uma auxiliar que apaga um jogo da HashTable e da lista
--------------------------------------------------------------------------------------------------------*/
void apagaJogo(GamesHash *HashG, gameListP gameList, int cont) {

    Game *game;
    char nomeJogo[MAXINPUT], *jogo;

    scanf(" %1023[^:\n]", nomeJogo);

    jogo= (char*) can_fail_malloc (sizeof(char)*(strlen(nomeJogo)+1));
    strcpy(jogo, nomeJogo);

    /* Procura o jogo na Hash Table e devolve-o*/
    game = searchGame(HashG, jogo);

    if (game == NULL) {
        printf("%d Jogo inexistente.\n", cont);
    }
    else {

        /* Retira vitorias as equipas se necessario */
        removeWin(game);

        /* Apaga o jogo da Hash Table e da lista*/
        deleteGame(gameList, HashG, jogo);

    }

    free(jogo);

}

/*------------------------------------------------------------------------------------------------------
Chama uma auxiliar que altera o resultado de um jogo e ajusta as vitorias das equipas
--------------------------------------------------------------------------------------------------------*/
void alteraScore(GamesHash *HashG, int cont) {
    int a, score1=0,score2=0;
    char nomeJogo[MAXINPUT], *jogo;

    scanf(" %1023[^:]:%d:%d", nomeJogo,&score1,&score2);

    jogo = (char*) can_fail_malloc (sizeof(char)*(strlen(nomeJogo)+1));
    strcpy(jogo, nomeJogo);

    /* Verifica se o jogo existe na Hash Table */
    a = verifyExistentGame(HashG, jogo);

    if (a != -1) {
        printf("%d Jogo inexistente.\n", cont);
    }
    else {
        /* Altera o score e ajusta as vitorias das equipas */
        changeScores(HashG, jogo, score1, score2);
    }

    free(jogo);
}

/*------------------------------------------------------------------------------------------------------
Chama uma auixilar que percorre a Hash Table das equipas e retorna as com mais vitorias
--------------------------------------------------------------------------------------------------------*/
void vencedores(TeamsHash *HashT, int cont) {
    /* Cria um vetor de ponteiros para equipas */
    Team **winnersTable;
    int max = 500; /* Capacidade maxima inicial do vetor = 500 */

    winnersTable = (Team**) can_fail_malloc (sizeof(Team*)*500);
    /* Retorna os melhores por ordem lexicografica */
    winnersTable= winners(HashT, winnersTable, max, cont);
    free(winnersTable);

}

/*------------------------------------------------------------------------------------------------------
Funcao que liberta memoria alocada antes do final do programa
--------------------------------------------------------------------------------------------------------*/
void destroyAll(GamesHash *HashG, TeamsHash *HashT, gameListP gameList) {

    /* Liberta a memoria alocada para equipas na Hash Table de equipas */
    destroyTeamsHash(HashT);
    /* Liberta a memoria alocada para jogos na Hash Table dos jogos */
    destroyGamesHash(HashG);

    /* Liberta a Hash Table de equipas */
    free (HashT);
    /* Liberta a Hash Table de jogos */
    free (HashG);
    /* Liberta a lista duplamente ligada */
    free (gameList);
}

int main() {

    int c, cont=1;

    /* Lista de ponteiros para jogos */
    gameListP gameList;
    /* Struct Hash Table para equipas */
    TeamsHash *HashT;
    /* Struct Hash Table para jogos */
    GamesHash *HashG;

    /* Inicializacao da Hash para equipas, da Hash para jogos e da lista para jogos */
    HashT = initTeamsHash(M);
    HashG = initGamesHash(M);
    gameList = initGamesList();

    while ((c=getchar()) != 'x') {
        
        if (c == 'A') {
            HashT = adicionaEquipa(HashT, cont);
        }

        else if (c == 'P') {
            procuraEquipa(HashT, cont);
        }

        else if (c == 'a') {
            HashG = adicionaJogo(HashG, HashT, gameList, cont);
        }
        else if (c == 'l') {
            listGames(gameList, cont);
        }

        else if (c == 'p') {
            procuraJogo(HashG, cont);
        }
        else if (c == 'r') {
            apagaJogo(HashG, gameList, cont);
        }
        else if (c == 's') {
            alteraScore(HashG, cont);
        }
        else if (c == 'g') {
            vencedores(HashT, cont);
        }

        cont++;
        c=getchar();}

    /* Libertacao de toda a memoria alocada antes do fim do programa */
    destroyAll(HashG, HashT, gameList);
    
    return 0;

}