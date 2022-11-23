#ifndef Comandos_H
#define Comandos_H

#include "Estrutura_jogos.h"
#include "Hash_equipas.h"
#include "Hash_jogos.h"

/* Funcao que adiciona um novo jogo a base de dados. */
void comando_a(Jogos *jogos, Jogo_hash *j, Equipas_hash *e, int M, int E, int NL);

/* Funcao que imprime todos os jogos pela ordem em que foram inseridos. */
void comando_l(Jogos *jogos, int NL);

/* Funcao que imprime um certo jogo que foi inserido. */
void comando_p(Jogo_hash *j, int M, int NL);

/* Funcao que elimina um jogo da base de dados e depois liberta essa memoria. */
void comando_r(Jogos *jogos, Jogo_hash *j, Equipas_hash *e, int M, int E, int NL);

/* Funcao que altera o resultado de um jogo que se encontra na base de dados. */
void comando_s(Jogo_hash *j, Equipas_hash *e, int M, int E, int NL);

/* Funcao que adiciona uma nova equipa ao sistema e incrementa o numero total de equipas em 1. */
int comando_A(Equipas_hash *e, int E, int NL, int total_equipas);

/* Funcao que procura uma certa equipa na base de dados. */
void comando_P(Equipas_hash *e, int M, int NL);

/* Funcao auxiliar da funcao comando_g, que compara o nome das equipas. */
int compare(const void *a, const void *b);

/* Funcao que verifica o numero maximo de vitorias e lista as equipas que ganharam esse numero de
 * jogos por ordem lexicografica. */
void comando_g(Equipas_hash *e, int E, int total_equipas, int NL);
#endif