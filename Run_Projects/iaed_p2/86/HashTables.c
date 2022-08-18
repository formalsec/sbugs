#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Projeto2.h"

/*Funcao que recebe a string e retorna o numero do indice segundo o inteiro m*/
int hashString(char* name, int m) {
    int h, a = 31415, b = 27183;
    for (h = 0; *name != '\0'; name++, a = a*b % (m-1)){
        h = (a*h + *name) % m;
    }
    return h;
}

/*Hash Table dos jogos*/

/*Funcao que inicia a Hash dos jogos, alocando a memoria necessaria para a tabela, no final mete 
todos os seus elementos a NULL. Retorna o endereco do primeiro elemento da tabela.*/
gameLink* InitGameHash(int m) {
    int i;
    gameLink* table;
    table = (gameLink*)malloc(m*sizeof(gameLink));
    for (i = 0; i < m; i++) table[i] = NULL;
    return table;
}

/*Procura um jogo na hash pelo seu nome. Usa o hashString para saber o indice onde esta a lista
com o jogo pedido, usando as funcoes das listas procura nessa lista o jogo com o nome pedido.*/
gameLink searchGameHash(gameLink *table, char* name) {
    int I = hashString(name, HASH_NUM_GAMES);
    return searchGame(table[I], name);
}

/*Insere um jogo na hash. Usa oo jogo hashString para saber o indice onde se encontra a lista, onde quer 
adicionar o jogo. Tendo a head da lista utiliza as funcoes das listas para o adicionar no inicio*/
void insertGameHash(gameLink *table, Game* game) {
    int i = hashString(game->name, HASH_NUM_GAMES);
    insertGameBegin(&table[i], game);
}

/*Remove um jogo na hash pelo seu nome. Usa o hashString para saber o indice onde esta a lista
com o jogo pedido, usando as funcoes das listas remove nessa lista o jogo com o nome pedido.*/
void deleteGameHash(gameLink* table, char* name){
    int i = hashString(name, HASH_NUM_GAMES);
    deleteGame(&table[i], name);
}

/*Liberta toda a memoria alocada pela Hash table dos jogos*/
void freeGameHash(gameLink* table){
    int i;
    gameLink t, next;
    /*Ciclo por todas as heads da hash*/
    for ( i = 0; i < HASH_NUM_GAMES; i++)
    {
        /*Ciclo por todos os nodes da lista*/
        for(t = table[i]; t != NULL;){
            next = t->next;
            FREEgameNode(t);
            t = next;
        }
    }
    free(table);
}

/*Hash Table das equipas*/

/*Funcao que inicia a Hash das equipas, alocando a memoria necessaria para a tabela, no final mete 
todos os seus elementos a NULL. Retorna o endereco do primeiro elemento da tabela.*/
teamLink* InitTeamHash(int m) {
    int i;
    teamLink* table;
    table = (teamLink*)malloc(m*sizeof(teamLink));
    for (i = 0; i < m; i++) table[i] = NULL;
    return table;
}

/*Procura uma equipa na hash pelo seu nome. Usa o hashString para saber o indice onde esta a lista
com a equipa pedida, usando as funcoes das listas procura nessa lista a equipa com o nome pedido.*/
teamLink searchTeamHash(teamLink *table, char* name) {
    int I = hashString(name, HASH_NUM_TEAMS);
    return searchTeam(table[I], name);
}

/*Insere uma equipa na hash. Usa o hashString para saber o indice onde se encontra a lista, onde quer 
adicionar a equipa. Tendo a head da lista utiliza as funcoes das listas para o adicionar no inicio.*/
void insertTeamHash(teamLink *table, char* name) {
    int i = hashString(name, HASH_NUM_TEAMS);
    insertTeam(&table[i], name);
}

/*Liberta toda a memoria alocada pela Hash table das equipas*/
void freeTeamHash(teamLink *table){
    int i;
    teamLink t, next;
    /*Ciclo por todas as heads da hash*/
    for ( i = 0; i < HASH_NUM_TEAMS; i++)
    {
        /*Ciclo por todos os nodes*/
        for(t = table[i]; t != NULL;){
            next = t->next;
            FREEteam(t);
            t = next;
        }
    }
    free(table);
}