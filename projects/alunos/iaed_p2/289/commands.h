#ifndef COMMANDS_H
#define COMMANDS_H

#include "abstract.h"
#include "hash_equipas.h"
#include "hash_jogos.h"
#include "lista_jogos.h"

#define MAXNOME 1023   /* Maximo de caracteres no nome de um jogo */
#define MAXEQUIPA 1023 /* Maximo de caracteres no nome de uma equipa */

/* Commando a adiciona um novo jogo a Hash jogos */
void cmd_a(link_jg *heads_jg, link_eq *heads_eq, list *jogos, int M, int m, int NL);

/* Commando l lista os jogos por ordem de input */
void cmd_l(list *jogos, link_jg *heads_jg, int M, int NL);

/* Commando p procura um jogo */
void cmd_p(link_jg *heads_jg, int M, int NL);

/* Commando r remove um jogo */
void cmd_r(link_jg *heads_jg, list *jogos, int M, int NL);

/* Commando s altera o score de um jogo */
void cmd_s(link_jg *heads_jg, int M, int NL);

/* Commando A adiciona uma equipa */
void cmd_A(link_eq *heads_eq, int m, int *numeq, int NL);

/* Commando P procura uma equipa */
void cmd_P(link_eq *heads_eq, int m, int NL);

/* Commando g imprime as equipas com mais vitorias */
void cmd_g(link_eq *heads_eq, int m, int *numeq, int NL);

#endif