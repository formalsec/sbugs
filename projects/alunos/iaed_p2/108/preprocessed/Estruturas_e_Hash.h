#ifndef Estruturas_e_Hash_h
#define Estruturas_e_Hash_h 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Define-se as estruturas e faz-se a chamada as funcoes das hashtables*/

/* Inicializo as estruturas */
typedef struct equipa{
    char *nome;
    int jogos_ganhos;
}*p_equipa;

typedef struct jogo{
    char *nome_j;
    p_equipa equipa1;
    p_equipa equipa2;
    int score1;
    int score2;
}*p_jogo;

typedef struct node{
    p_jogo jogo;
    struct node *prev;
    struct node *next;
}*link;

/* Funcao que devolve o numero correspondente a um nome */
int hash(char *nome,int max);


/*Todas as funcoes foram retiradas dos powerpoints menos a jogoInsereLista */

/*Funcao que inicializa todas as posiceos da hashtable equipa a NULL */
void Equipainit(int *max_equipas,int m,p_equipa **p_tab_e);

/*Funcao que aumenta o tamanho da hashtable para aumentar a eficacia */
void Equipaexpande(int *max_equipas,int *n_equipas,p_equipa **p_tab_e);

/*Funcao que guarda equipa na hashtable */
void EquipaInsere(int *max_equipas,int *n_equipas, p_equipa equipa,p_equipa **p_tab_e);

/*Funcao que devolve a equipa que contem o nome dado caso nao exista devolve NULL */
p_equipa EquipaProcura(int *max_equipas,char *nome,p_equipa **p_tab_e);


/*Fazem o mesmo que as funcoes da hashtable equipa mas para a hashtable jogos */
void Jogoinit(int *max_jogos,int m,p_jogo **p_tab_j);

void Jogoexpande(int *max_jogos,int *n_jogos,p_jogo **p_tab_j);

void JogoInsereHash(int *max_jogos,int *n_jogos, p_jogo jogo,p_jogo **p_tab_j);

void Jogoexpande(int *max_jogos,int *n_jogos,p_jogo **p_tab_j);

p_jogo JogoProcura(int *max_jogos,char *nome,p_jogo **p_tab_j);


/*Funcoes que so o jogo tem */

/*Funcao que insere um jogo numa lista duplamente ligada, necessario para a funcao l apenas*/
void JogoInsereLista(p_jogo jogo,link *head,link *tail);

/*Funcao que apaga um Jogo da Hashtable caso ele exista */
void JogoApagaHash(p_jogo jogo,int *max_jogos,int *n_jogos,p_jogo **p_tab_j);

/* Funcao que apaga um jogo caso ele exista de uma lista duplamente ligada*/
void JogoApagaLista(p_jogo jogo, link *head,link *tail);

#endif
