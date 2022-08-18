#ifndef EQUIPA_H
#define EQUIPA_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/*----------------------------------------------------------------------------*/
/*                              CONSTANTES                                    */
/*----------------------------------------------------------------------------*/
/* numero maximo de equipas numa hashtable*/
#define MAX_H_EQUIPAS 499

/*----------------------------------------------------------------------------*/
/*                              ESTRUTURA                                     */
/*----------------------------------------------------------------------------*/
typedef struct equipa{
    /* ponteiro para a string com o nome da equipa*/
    char *nome;
    /* numero de jogos que a equipa ganhou*/
    int vitorias;
}* pequipa;


typedef struct enode{
    /* 'e' e o ponteiro para a equipa*/
    pequipa e;
    /* 'next' e o ponteiro para o no da equipa que precede na lista de equipas*/
    struct enode *next;
}* elink;


typedef struct elist{
    /* 'head' e o ponteiro para o primeiro no de equipas da lista de equipas*/
    elink head;
    /* numero de equipas na lista de equipas*/
    int tamanho;
    /* numero maximo de vitorias das equipas da lista de equipas*/
    int max_vitorias;
    /* numero de equipas que tiveram o numero maximo de vitorias*/
    int cont_equipas_max_vit;
}* lista_equipa;


typedef struct hashtable_equipas{
    /*ponteiro para o primeiro elemento da hashtable de equipas*/
    pequipa* hash_equipas;
    /*tamanho maximo da hashtable*/
    int max;
    /*tamanho atual da hashtable*/
    int atual;
}* ht_equipas;


/*----------------------------------------------------------------------------*/
/*                              FUNCOES                                       */
/*----------------------------------------------------------------------------*/

/* inicia_lista_equipa vai inicializar a lista de equipas a NULL*/
lista_equipa inicia_lista_equipa();

/* vai criar uma nova equipa*/
pequipa nova_equipa(char *buffer);

/*inserir equipa da lista de equipas e atualizar*/
void inserir_equipa(lista_equipa le, char* texto);

/* eliminamos a lista de equipas*/
void eliminar_lista_equipa(lista_equipa le);

/* percorre toda a lista de equipas e procura o numero maximo de vitorias e
 * o numero de equipas que tiveram o numero maximo de vitorias*/
void procura_max_vitorias(lista_equipa le);

/* compara strings pela ordem lexicografica*/
int compara_strings(const void* a, const void* b);

/* vai encontrar as equipas com mais vitorias e imprime o nome delas por
 * ordem lexicografica*/
void encontra_max_vitorias(int cont, lista_equipa le);


/* determina em que posicao da hastable fica o ponteiro para a equipa de
 * acordo com o seu nome*/
int hash(char* v, int M);

/* inicio a estrutura da tabela de equipas*/
ht_equipas iniciar_tabela_equipas();

/* inicio a hashtable de equipas*/
pequipa* iniciar_hash_equipas(int M);

/* eliminar a hashtable de equipas do sistema*/
void eliminar_hash_equipas(pequipa * hash_equipas, int M);

/* expande o tamanho da hashtable de equipas*/
void expandir_hash_equipas(ht_equipas ht_e);

/* coloco o ponteiro da equipa na hashtable de equipas*/
void insere_equipa_hash_equipas(ht_equipas ht_e, pequipa e);

/* procura uma equipa na hashtable de equipas*/
int procura_equipa_hash_equipas(ht_equipas ht_e, char*texto);

#endif
