#ifndef jogos_h
#define jogos_h

#define TAM_HASHTABLE_JOGOS 997

#include <stdio.h>
#include <stdio.h>
#include "equipas.h"



struct jogo{
    char* nome; /* string nao vazia */
    char* equipa1; /* string nao vazia */
    char* equipa2; /* string nao vazia */
    int score_e1; /* string nao vazia */
    int score_e2; /* string nao vazia */
};

typedef struct jogo* Jogo; /* pointer para um jogo */


typedef struct node_jogo{
    Jogo jogo;
    struct node_jogo * next;
}*link_jogo; /* link usado nas cadeias da hashtable dos jogos*/

typedef struct node_jogo_ls{
    Jogo jogo;
    struct node_jogo_ls *next, *prev;
}*link_jogo_ls;   /* link usado na lista duplamente ligada dos jogos */

typedef struct lista_jogos{
    link_jogo_ls cabeca;
    link_jogo_ls ultimo;
}* Lista_jogos; /* identificador da lista duplamente ligada dos jogos */


link_jogo * init_tab_jogos(void);
void insere_tab_jogo(Jogo jogo,link_jogo *jogos);
void apaga_tab_jogo(link_jogo * jogos,Key nome);
Jogo procura_tab_jogo(Key v,link_jogo *jogos);
void apaga_tab_jogos(link_jogo * jogos);


link_jogo insere_jogo_cadeia(link_jogo equi_slot,Jogo jogo);
Jogo procura_jogo_cadeia(link_jogo equi_slot,Key v);
link_jogo remove_jogo_cadeia(link_equi equi_slot,Jogo equipa);





Lista_jogos inicia_ls(void);

Lista_jogos apaga_jogo_ls(Jogo jogo, Lista_jogos l);

Lista_jogos adiciona_jogo_ls(Jogo jogo,Lista_jogos l);
void apaga_ls_jogos(Lista_jogos l);



Jogo novo_jogo(char * nome,char * e1,char * e2, int s1, int s2);
void apaga_jogo(Jogo jogo);


#endif /* jogos_h */


