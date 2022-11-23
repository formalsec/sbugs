#ifndef EQUIPAS_file
#define EQUIPAS_file

#include "hash_defines.h"

/*estrutura EQUIPA define cada equipa representada por nome 
    e score (numero de vitorias) na hashtable_equipas*/
typedef struct equipa {
    char * nome;
    int score;
    struct equipa * next;
} EQUIPA;

EQUIPA ** init_hash_table();

void add_equipa(EQUIPA ** hashtable_equipas, EQUIPA * nova_equipa);

EQUIPA * procura_equipa(EQUIPA ** hashtable_equipas, char * nome);

void add_score(EQUIPA ** hashtable_equipas, char * nome);

void remove_score(EQUIPA ** hashtable_equipas, char * nome);

int maior_score_equipa(EQUIPA ** hashtable_equipas);

int num_equipas(EQUIPA ** hashtable_equipas, int score);

EQUIPA * cria_equipa(char * nome);

void destroy_hash_equipa(EQUIPA ** hashtable_equipas);

#endif