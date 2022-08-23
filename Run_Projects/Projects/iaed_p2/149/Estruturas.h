#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAMANHO_DE_STRING 1023
#define TABLE_SIZE 31

typedef struct equipa{/*Estrutura para equipa*/
    char *nome;
    struct str_node *next;
    int score;
}equipa;

typedef struct str_node  { /*Estrutura para a linked list*/
        struct str_node *next, *previous;
        struct equipa equipa;
    }str_node;

typedef struct lista{ /*guardar o pointer do primeiro e do ultimo termo*/
    struct str_node *head, *last;
    }lista;

typedef struct lista2{/*guardar o pointer do primeiro e ultimo termo da lista dos jogos*/
    struct str_node_jogo *head, *last;
}lista2;

typedef struct jogo{ /* estrutura para os jogos*/
    char *nome;
    struct str_node *equipa1,*equipa2;
    int score[2];
    struct str_node_jogo *next;
}*jJogo;

typedef struct str_node_jogo{ /* Estrutura para a linked list do jogos*/
    struct str_node_jogo *next, *previous; 
    struct jogo jogo;
}str_node_jogo;

typedef struct hash_table_equipa{ /* Estrutura para a hash table da equipa*/
    str_node **entries;
    int M,N;
}hash_table_equipa;

typedef struct hash_table_jogo{ /* Estrutura para a hash table dos jogos*/
    str_node_jogo **entries;
    int M,N;
}hash_table_jogo;
#endif