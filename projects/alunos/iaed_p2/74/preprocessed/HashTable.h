#ifndef HashTable_h
#define HashTable_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "lists.h"

/*---------------------------Definicao de constantes------------------------*/

#define TABLE_SIZE 25000 /*tamanho da hash table das equipas*/
#define TAM_G 2000 /*tamanho da hash table dos jogos*/


/*---------------------------------------Structs---------------------------------*/
/*Estrutura games, constituida pelo nome, equipa1, equipa2, score1, score2 e o node ponteiro da proxima extrutura*/
typedef struct node
{
    char *game_name;
    char *team1;
    char *team2;
    int score1;
    int score2;
    struct node *next;

}*games; /* pGame e um pointer para uma struct node */

/*Estura pTeam, constituida pelo nome da equipa e o numero de jogos ganhos*/
typedef struct team{
    char *team_name;
    int wins;
}*pTeam; /*pTeam e um pointer para uma struct team*/


/*--------------------------prototipos-------------------------------------*/
int unsigned hash(char *name,int tamanho);

/*funcoes Hash Table games, encadiamento externo*/
/*funcao que inicia a Hash Table*/
void Ginit(void);
/*funcao que insere elementos na hash table*/
void Ginsert(char *name, char *t1, char *t2, int s1, int s2);
/*funcao que encontra elementos na hash table atraves do nome e devolve esse elemento*/
games Gsearch(char *id);
/*funcao que elimina elementos da hash table*/
void Gdelete(char *id);
/*funcao que da free na hash table*/
void Gfree_hash(void);


/*funcoes Hash Tables teamn encadiamento linear*/
/*funcao que inicia a Hash Table*/
void Tinit(void);
/*funcao que insere elementos na hash table*/
void Tinsert(char *name);
/*funcao que devolve um elemento da hash table a partir da sua hash*/
pTeam Thash(int i);
/*funcao que procura elementos na hash table a partir do seu nome*/
pTeam Tsearch(char *id);
/*funcao que devolve o numero maximo de jogos ganhos que existem na hash table*/
int max_wins(void);
/*funcao que  da free na hash table*/
void Tfree_hash(void);

#endif /* HashTable_h */



