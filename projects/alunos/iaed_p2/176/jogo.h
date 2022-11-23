#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "equipa.h"


/*----------------------------------------------------------------------------*/
/*                              CONSTANTES                                    */
/*----------------------------------------------------------------------------*/
/* numero maximo de jogos numa hashtable*/
#define MAX_J_JOGOS 2143

/*----------------------------------------------------------------------------*/
/*                              ESTRUTURA                                     */
/*----------------------------------------------------------------------------*/
typedef struct jogo{
    /* ponteiro para a string com o nome do jogo*/
    char *nome;
    /* ponteiros para as equipas do jogo*/
    pequipa e1, e2;
    /* score das equipas e1 e e2 respetivamente*/
    int s1, s2;
}*pjogo;


typedef struct jnode{
    /* ponteiro para o jogo j */
    pjogo j;
    /* ponteiro para o proximo jogo na lista de jogos*/
    struct jnode *next;
    /* ponteiro para o jogo anterior na lista de jogos*/
    struct jnode *prev;
}* jlink;


typedef struct jlist{
    /* ponteiros para os nos do primeiro e ultimo jogo da lista de jogos*/
    jlink head, tail;
    /* numero de jogos na lista de jogos*/
    int tamanho;
}* lista_jogos;


typedef struct hashtable_jogos{
    /*ponteiro para o primeiro elemento da hashtable de equipas*/
    jlink* hash_jogos;
    /*tamanho maximo da hashtable*/
    int max;
    /*tamanho atual da hashtable*/
    int atual;
} *ht_jogos;


/*----------------------------------------------------------------------------*/
/*                              FUNCOES                                       */
/*----------------------------------------------------------------------------*/
/* inicio a lista de jogos a NULL*/
lista_jogos inicia_lista_jogos();

/* cria um novo jogo*/
pjogo novo_jogo(char *buffer, pequipa pe1, pequipa pe2, int score1, int score2);

/*insiro jogo da lista de jogos*/
void inserir_jogo(lista_jogos lj, char* texto, pequipa pe1, pequipa pe2,
        int score1, int score2);

/* libertamos o no do jogo*/
void libertar_jogo(jlink x);

/*aumento o numero de vitorias da equipa que tem mais score*/
void aumenta_vitorias(pjogo x);

/* diminui vitorias da equipa que tem mais score*/
void diminui_vitorias(pjogo x);

/* eliminamos jogo da lista de jogos*/
void elimina_jogo_lista_jogos(lista_jogos lj, jlink x);

/* imprimo os jogos da lista de jogos pela ordem em qe foram introduzidos*/
void imprimir_lista_jogos(int cont, lista_jogos lj);

/* eliminamos a lista de jogos*/
void eliminar_lista_jogos(lista_jogos lj);


/* inicio a estrutura da tabela de equipas*/
ht_jogos iniciar_tabela_jogos();

/* inicio a hashtable de jogos*/
jlink* iniciar_hash_jogos(int M);

/* eliminar a hashtable de jogos do sistema*/
void eliminar_hash_jogos(jlink * hash_jogos, int M);

/* expande o tamanho da hashtable de jogos*/
void expandir_hash_jogos (ht_jogos ht_j);

/* coloco o ponteiro do jogo na hashtable de jogos*/
void insere_jogo_hash_jogos(ht_jogos ht_j, jlink x);


/* procura um jogo na hashtable de jogos*/
int procura_jogo_hash_jogos(ht_jogos ht_j, char*texto);

/* elimina jogo da hastable dos jogos*/
void elimina_jogo_hash_jogos(ht_jogos ht_j, int i);

/* altera os scores do jogo*/
void altera_scores(jlink x, int novo_s1, int novo_s2);


#endif