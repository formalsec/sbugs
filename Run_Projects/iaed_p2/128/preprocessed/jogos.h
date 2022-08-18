#ifndef _LISTA_JOGOS_
#define _LISTA_JOGOS_

#define HEADS_JOGOS 977

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"

/*estrutura do jogo*/

typedef struct jogo{
    Equipa *equipa1,*equipa2;
    char *nome;
    int score1,score2;
    
}Jogo;

/*nos de uma lista duplamente ligada de jogos*/
typedef struct lista_jogos{
    Jogo *jogo;
    struct lista_jogos *next;
    struct lista_jogos *prev;
}Lista_jogos;


typedef struct no{
    Jogo *jogo;
    struct no *next;
}No;
typedef Lista_jogos* link_lista;

/*estrutura para colocar os limites de uma lista duplamente ligada*/
/*estrutura usada para colocar os jogos por ordem de insercao*/
typedef struct{
    link_lista head,last;
}limites_lista;

typedef No* link_jogo;



link_jogo* inicializa_hash_jogo(int m);
link_jogo novo_jogo(link* heads,char*buffer,char *equipa1,char *equipa2,int score1,int score2);
link_jogo insere_jogo(limites_lista* lista,link* heads,link_jogo head,char*buffer,char *equipa1,char *equipa2,int score1,int score2);
int existe_jogo(link_jogo* heads_jogos,char *nome);
void insere_jogo_hash(limites_lista* lista,link* heads,link_jogo* heads_jogo,char *nome,char *equipa1,char *equipa2,int score1,int score2);
limites_lista* nova_lista();
void adiciona_fim(limites_lista* lista,Jogo* jogo);
Jogo* procura_jogo(link_jogo*heads,char *nome);
Jogo* encontra_jogo(link_jogo head,char* nome);
void destroi_lista_jogos(limites_lista* lista);
void destroi_hash_jogos(link_jogo* heads_jogos,int M);
void apaga_jogo_hash(link_jogo*heads,char* nome);
void apaga_jogo_lista(limites_lista*lista,char*nome);


#endif

