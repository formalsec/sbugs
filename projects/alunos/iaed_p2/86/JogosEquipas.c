#include "/home/fmarques/sbugs/Run_Projects/Projects/lib/allocators.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Projeto2.h"

/*Funcoes para as equipas-----------------------------------------------------------------------------*/

/*Funcao que recebe uma string, aloca a memoria suficiente para uma Struct Team e para o seu nome e copia
a string recebida para o endereco onde a mem foi alocada. Retorna o endereco da estrutura criada.*/
teamLink NEWteam(char* buffer) {
    teamLink new = (teamLink)can_fail_malloc(sizeof(struct Team));
    new->name = (char*)can_fail_malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(new->name, buffer);
    new->next = NULL;
    new->gamesWon = 0;
    return new;
}


/*Funcao que insere a Struct Team numa lista*/
void insertTeam(teamLink *head, char* buffer){
    teamLink new = NEWteam(buffer);
    new->next = *head;
    *head = new;
}

/*Funcao que recebe a head de uma lista e usando essa head procura a Team com o mesmo nome dado e retorna
o seu endereco*/
teamLink searchTeam(teamLink head, char* name){
    teamLink t;
    for(t = head;t != NULL; t = t->next){
        if(strcmp(t->name, name) == 0){
            return t;
        }
    }
    return NULL;
}

/*Funcao que liberta a memoria alocada para uma Team*/
void FREEteam(teamLink team){
    free(team->name);
    free(team);
}



/*Funcoes para os jogos-----------------------------------------------------------------------------*/

/*Funcao que recebe todos os dados necessarios para a criacao de um jogo e aloca toda a memoria necessaria
para o mesmo. Retorna o endereco do jogo criado.*/
Game* createGame(char* nameBuffer, teamLink team1, teamLink team2, int score1, int score2){
    Game* new = (Game*)can_fail_malloc(sizeof(Game));
    new->name = (char*)can_fail_malloc(sizeof(char) * (strlen(nameBuffer) + 1));
    strcpy(new->name, nameBuffer);
    new->team1 = team1;
    new->team2 = team2;
    new->score = (int*)can_fail_malloc(sizeof(int)*2);
    new->score[0] = score1;
    new->score[1] = score2;
    return new;
}

/*Funcao que recebe um endereco de um jogo e queria o seu Node, alocando a memoria suficiente para tal. 
Retorna o endereco do novo Node.*/
gameLink NEWgame(Game* game){
    gameLink new = (gameLink)can_fail_malloc(sizeof(struct GameNode));
    new->game = game;
    new->next = NULL;
    new->deleted = FALSE;
    return new;
}

/*Funcao que insere o jogo no inicio da lista dada*/
void insertGameBegin(gameLink *head, Game* game){
    gameLink x = NEWgame(game);
    x->next = *head;
    *head = x;
}

/*Funcao que insere o jogo no fim da lista dada*/
void insertGameEnd(gameLink* head, Game* game, gameLink *tailGame){
    gameLink x;
    if (*head == NULL) {
        x = NEWgame(game);
        *tailGame = x;
        *head = x;
        return;
    }
    x = NEWgame(game);
    (*tailGame)->next = x;
    *tailGame = x;
}

/*Funcao que procura o jogo pelo nome e insere-o na lista dada*/
gameLink searchGame(gameLink head, char* name){
    gameLink t;
    for(t = head;t != NULL; t = t->next){
        if(!t->deleted && strcmp(t->game->name, name) == 0){
            return t;
        }
        
    }
    return NULL;
}

/*Funcao que elimina e liberta a memoria do jogo pedido. O jogo e procurado pelo nome.*/
void deleteGame(gameLink *head, char* name){
    gameLink t, prev;
    for (t = *head, prev = NULL; t != NULL; prev = t, t = t->next){
        if(strcmp(t->game->name, name) == 0){
            if(t == *head){
                *head = t->next;
            }else{
                prev->next = t->next;
            }
            FREEgameNode(t);
            break;
        }
    }
}

/*Funcao que liberta a memoria alocada para um Node de um jogo*/
void FREEgameNode(gameLink gameLink){
    free(gameLink->game->name);
    free(gameLink->game->score);
    free(gameLink->game);
    free(gameLink);
}

/*Funcao que liberta a memoria de uma lista inteira de jogos, porem so liberta a Struct e nao o que ela contem.*/
void freeGameList(gameLink head){
    gameLink t, next;
    for(t = head; t != NULL;){
        next = t->next;
        free(t);
        t = next;
    }  
}