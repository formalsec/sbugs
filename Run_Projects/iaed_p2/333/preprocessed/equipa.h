#ifndef ex_h
#define ex_h

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


#define MAX 1024
#define CAP 1997


typedef struct s_hash_node_equipa2 { 
    struct s_hash_node_equipa2 * next;
    char * equipa1;
    size_t vitorias;
   
} hash_node_equipa;

typedef struct {
    hash_node_equipa ** tb; 
    size_t capacidade_equipa;
} hash_table_equipa;


hash_table_equipa * cria_hash_table_equipa();

int hash(char *v, int M);

int verificaExiste(hash_table_equipa* t, char * word);

char *aloca_memoria(const char *s);

hash_node_equipa * constroiNo_equipa(char * nome_equipa, hash_node_equipa * inicio);

void adiciona_equipa(hash_table_equipa * HashEquipa, int * Nr_linha);

void procura_equipa(hash_table_equipa * eq, int * Nr_linha);

int compara_palavras(const void *a, const void *b);

void printa_melhores(char **vetor, size_t comp, int *Nr_linha, int maior);

void maisGanhos(hash_table_equipa * eq, int *Nr_linha);

void free_hash_table(hash_table_equipa * t);

#endif