#include "/home/fmarques/sbugs/projects/alunos/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Projeto2.h"

/*Funcao que recebe todos as variaveis necessarias para executar os comandos. Recebe o primeiro caracter do input
do utilizador e usando um switch chama a funcao correspondente ao comando*/
int scanCommand(int *nrCommand, teamLink *hashTeamTable, gameLink *headGame, gameLink* hashGameTable, gameLink *tailGame){
    char c;
    c = getchar();
    switch (c){
        case 'a':
            (*nrCommand)++;
            newGame(nrCommand, hashTeamTable, headGame, hashGameTable, tailGame);
        break;

        case 'A':
            (*nrCommand)++;
            newTeam(nrCommand, hashTeamTable);
        break;

        case 'l':
            (*nrCommand)++;
            listGames(nrCommand, headGame);
        break;

        case 'p':
            (*nrCommand)++;
            searchGameByName(nrCommand, hashGameTable);
        break;

        case 'P':
            (*nrCommand)++;
            searchTeamByName(nrCommand, hashTeamTable);
        break;

        case 'r':
            (*nrCommand)++;
            deleteGameByName(nrCommand, hashGameTable, headGame);
        break;

        case 's':
            (*nrCommand)++;
            changeScore(nrCommand, hashGameTable);
        break;

        case 'g':
            (*nrCommand)++;
            bestTeams(nrCommand, hashTeamTable);
        break;

        case 'x':
        return FALSE; 
        
    }

    return TRUE;
}

/*Funcao que executa o comando 'A'. Cria uma nova equipa e guarda-a numa Hash Table.*/
void newTeam(int *nrCommand, teamLink *hashTeamTable){
    char buffer[MAX_LEN];
    scanf(" %[^:\n]", buffer);
    if(searchTeamHash(hashTeamTable, buffer) == NULL){
        insertTeamHash(hashTeamTable, buffer);
    }else{
        printf("%d Equipa existente.\n", *nrCommand);
    }
}

/*Funcao que executa o comando 'a'. Cria um novo jogo usando toda a informaccao que ira receber do utilizador.
Guarda este jogo numa Hash Table. Tambem guarda o endereco do novo jogo numa lista a parte de modo a guardar
a ordem de introducao.*/
void newGame(int *nrCommand, teamLink *hashTeamTable, gameLink *headGame, gameLink *hashGameTable, gameLink *tailGame){
    int score1, score2;
    char team1Name[MAX_LEN], team2Name[MAX_LEN], gameName[MAX_LEN];
    teamLink team1, team2;
    Game* newGame;
    scanf(" %[^:]:%[^:]:%[^:]:%d:%d",  gameName, team1Name, team2Name, &score1, &score2);
    if(searchGameHash(hashGameTable, gameName) != NULL) {
        printf("%d Jogo existente.\n", *nrCommand);
        return;
    }
    team1 = searchTeamHash(hashTeamTable, team1Name);
    if (team1==NULL){
        printf("%d Equipa inexistente.\n", *nrCommand);
        return;
    }
    team2 = searchTeamHash(hashTeamTable, team2Name);
    if (team2 == NULL){
        printf("%d Equipa inexistente.\n", *nrCommand);
        return;
    }

    newGame = createGame(gameName, team1, team2, score1, score2);
    /*Insere o jogo na lista ordenada*/
    insertGameEnd(headGame, newGame, tailGame);
    /*Insere o jogo na hash*/
    insertGameHash(hashGameTable, newGame);
    
    /*Atualiza o numero de vitorias das equipas*/
    if(score1>score2){
        team1->gamesWon++;
    }else if(score2>score1){
        team2->gamesWon++;
    }
    
}

/*Funcao que executa o comando 'l'. Lista todos od jogos por ordem de adicao. Para isso usa a lista de jogos 
que se encontra ordenada. Percorre a lista e so nao lista os jogos que ja foram eliminados da hash (estes encontram-se marcados)*/
void listGames(int* nrCommand, gameLink *headGame){
    gameLink t;
    Game* game;
    for(t = *headGame; t != NULL; t = t->next){
        if(!t->deleted){
            game = t->game; 
            printf("%d %s %s %s %d %d\n", *nrCommand, game->name, game->team1->name, game->team2->name, *(game->score), *(game->score+1));
        }
    }
}

/*Funcao que executa o comando 'p'. Procura o jogo com o nome igual a string recebida pelo utilizador.*/
void searchGameByName(int* nrCommand, gameLink *hashGameTable){
    char name[MAX_LEN];
    gameLink gameLink;
    Game* game;
    scanf(" %[^:\n]", name);
    gameLink = searchGameHash(hashGameTable, name);
    if (gameLink == NULL){
        printf("%d Jogo inexistente.\n", *nrCommand);
    }else{
        game = gameLink->game;
        printf("%d %s %s %s %d %d\n", *nrCommand, game->name, game->team1->name, game->team2->name, game->score[0], game->score[1]);
    }
}

/*Funcao que executa o comando 'P'. Procura a equipa com o nome igual a string recebida pelo utilizador e mostra as vitorias
dessas equipa. As vitorias estao a ser atualizadas sempre que certos comandos sao executados.*/
void searchTeamByName(int* nrCommand, teamLink *hashTeamTable){
    char name[MAX_LEN];
    teamLink team;
    scanf(" %[^:\n]", name);
    team = searchTeamHash(hashTeamTable, name);
    if (team == NULL){
        printf("%d Equipa inexistente.\n", *nrCommand);
    }else{
        printf("%d %s %d\n", *nrCommand, team->name, team->gamesWon);
    }
}

/*Funcao que executa o comando 'r'. Elimina o jogo da HashTable com o nome igual a string dada pelo utilizador e marca
-o como eliminado na lista ordenada.*/
void deleteGameByName(int* nrCommand, gameLink *hashGameTable, gameLink *headGame){
    char name[MAX_LEN];
    gameLink gameLink_, gameLinkList;
    scanf(" %[^:\n]", name);
    gameLink_ = searchGameHash(hashGameTable, name);
    if (gameLink_ == NULL){
        printf("%d Jogo inexistente.\n", *nrCommand);
    }else{
        /*Atualiza as vitorias das equipas*/
        if (gameLink_->game->score[0] > gameLink_->game->score[1]){
            (gameLink_->game->team1->gamesWon)--;
        }else if(gameLink_->game->score[0] < gameLink_->game->score[1]){
            (gameLink_->game->team2->gamesWon)--;
        }

        /*Procura o jogo na lista ordenada e marca-o como eliminado*/
        gameLinkList =  searchGame(*headGame, name);
        gameLinkList->deleted = TRUE;
        /*Elimina o jogo na hash*/
        deleteGameHash(hashGameTable, name);
        
    }
}

/*Funcao que executa o comando 's'. Altera o score de um jogo e atualiza as vitorias das equipas.*/
void changeScore(int *nrCommand, gameLink* hashGameTable){
    char name[MAX_LEN];
    gameLink gameLink;
    Game* game;
    int score1, score2;
    scanf(" %[^:\n]:%d:%d", name, &score1, &score2);
    gameLink = searchGameHash(hashGameTable, name);
    if (gameLink == NULL){
        printf("%d Jogo inexistente.\n", *nrCommand);
    }else{
        game = gameLink->game;
        /*Decrementa a vitoria da equipa, ou nao caso seja empate.*/
        if(game->score[0] > game->score[1]){
            game->team1->gamesWon--;
        }else if(game->score[0] < game->score[1]){
            game->team2->gamesWon--;
        }

        /*Altera o score*/
        game->score[0] = score1;
        game->score[1] = score2;
        
        /*Incrementa a vitoria da nova equipa vencedora.*/
        if(game->score[0] > game->score[1]){
            game->team1->gamesWon++;
        }else if(score2>score1){
            game->team2->gamesWon++;
        }
    }
}

/*Funcao que executa o comando 'g'. Lista as equipas que ganharam mais jogos por ordem lexicografica.*/
void bestTeams(int* nrCommand, teamLink* hashTeamTable){
    int i, max, teamNr, index;
    teamLink t;
    char** bestOnes;
    max = 0;
    teamNr = 0;
    /*Ciclo por toda a hash das equipas com o objetivo de encontrar o maior numero de vitorias que uma equipa tem 
    e guardar o numero de equipas que tem esse numero de vitorias*/
    for ( i = 0; i < HASH_NUM_TEAMS; i++)
    {
        for( t = hashTeamTable[i]; t != NULL; t = t->next){
            if (max < t->gamesWon){
                teamNr = 0;
                max = t->gamesWon;
            }
            if (max == t->gamesWon){
                teamNr++;
            }
        }
    }

    if (teamNr >0){
        index = 0;
        /*Aloca a memoria suficiente para as melhores equipas*/
        bestOnes =(char**)can_fail_malloc(sizeof(char*)*teamNr);
        /*Ciclo por toda a hash das equipas de modo a adicionar todas as equipas com o determinado
        numero de vitorias ao array de strings criado (bestOnes)*/
        for ( i = 0; i < HASH_NUM_TEAMS; i++)
        {
            for( t = hashTeamTable[i]; t != NULL; t = t->next){
                if(t->gamesWon == max){
                    bestOnes[index] = t->name;
                    index++;
                }
            }
        }
        /*Ordena por ordem lexicografica o array com o nome das equipas*/
        qsort(bestOnes,teamNr,sizeof(char *),compare);

        printf("%d Melhores %d\n", *nrCommand, max);
        for(i = 0; i < teamNr; i++){
            printf("%d * %s\n", *nrCommand, bestOnes[i]);
        }
        free(bestOnes);
    }
    
    
}

/*Funcao utilizada para ordenar as equipas no bestTeams. Compara duas strings e verifica qual das 
duas deve vir primeiro*/
int compare(const void *a, const void *b)
{
    const char **pa,**pb;

    pa = (const char **)a;
    pb = (const char **)b;
    return( strcmp(*pa,*pb) );
}