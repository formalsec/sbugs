#include <string.h>

#define TAB_SIZE 1009

/* Devolve um indice para a tabela de jogos, dado um nome */
unsigned int hash_jogo(char* name);

/* Devolve um indice para a tabela de equipas, dado um nome */
unsigned int hash_equipa(char* name);
