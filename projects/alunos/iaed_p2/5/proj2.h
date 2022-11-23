#ifndef PROJ_H
#define PROJ_H

#include "Equipas.h"
#include "Jogos.h"

#define TAM_HASH 401 /* Tamanho das HashTables. */
#define CAR_MAX 1024 /* Tamanho maximo dos nomes das equipas e dos jogos. */

/* Um estrutura que guarda o numero de comandos inseridos ate o momento. */
typedef struct Dados
{
    int NL;
} Dados;

typedef char Key;  /* Tipo da chave */
#define key(a) (a->nome) /* Define a chave utilizada nas funcoes de hash. */

char *strdup(const char *src);
int calc_hash(char *v, int M);
void clean_memory(Hash_equipa *hash_eq, Hash_jogo *hash_jg);

/* DECLARACAO DE FUNCOES */
void func_a(Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL);
void func_A(Hash_equipa *hash_eq, int NL);
void func_l(int NL);
void func_p(Hash_jogo *hash_jg, int NL);
void func_P(Hash_equipa *hash_eq, int NL);
void func_r(Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL);
void func_s(Hash_jogo *hash_jg, Hash_equipa *hash_eq, int NL);
void func_g(Hash_equipa *hash_eq, int NL);

#endif
