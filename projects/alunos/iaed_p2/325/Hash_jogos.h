#ifndef Hash_jogos_H
#define Hash_jogos_H

#include "Estrutura_jogos.h"

/* Lista ligada em que cada elemento guarda um ponteiro para um determinado jogo. */
typedef struct str_jogo {
    jogo *ptr_jogo;
    struct str_jogo *next;
} * Jogo_hash;

/* Funcao auxiliar da insert_jogo que aloca memoria para a criacao de um novo jogo, e inicializa as
 * variaveis que estao incluidas nesse jogo. */
Jogo_hash NEW(jogo *res);

/* Funcao auxiliar da insert_jogo que inserte um novo jogo no inicio de uma lista ligada na
 * Hashtable. */
Jogo_hash insertBegin(Jogo_hash head, jogo *res);

/* Funcao que inserte um novo jogo na Hashtable. */
void insert_jogo(Jogo_hash *todos_jogos, jogo *ptr_jogo, int M);

/* Funcao auxiliar da delete_jogo que elimina um certo jogo da Hashtable. */
Jogo_hash delete_node(Jogo_hash head, jogo *res);

/* Funcao que inicializa a Hahstable alocando memoria. */
Jogo_hash *init_j(int M);

/* Funcao que elimina um certo jogo da Hashtable. */
void delete_jogo(Jogo_hash *todos_jogos, jogo *ptr_jogo, int M);

/* Funcao auxiliar da Search que percorre a Hashtable ate encontrar o jogo pretendido. */
jogo *search_list(Jogo_hash head, char *nome);

/* Funcao que retorna um certo jogo que pertence a Hashtable. */
jogo *Search(Jogo_hash *todos_jogos, char *nome, int M);

/* Funcao que elimina todos os jogos armazenados na Hashtable,
e liberta toda a memoria que esta ocupava. */
void destroy_jogos(Jogo_hash *j, int M);

#endif