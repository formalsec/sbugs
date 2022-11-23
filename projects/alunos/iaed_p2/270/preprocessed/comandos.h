#ifndef COMANDOS_H
#define COMANDOS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tabdispercao.h"
#include "listadligada.h"

/* numero maximo de caracteres que um nome de uma equipa ou jogo pode ter
 + 1 ('\0') */
#define MAX_CHAR 1024

/* prototipos das funcoes correspondentes aos comandos que permitem  a
utilizacao do programa a partir do stdin */
void cmd_a(int nl, pLista ls_jg, pTabEquipas ht_eq, pTabJogos ht_jg);
void cmd_A(int nl, pTabEquipas ht_eq);
void cmd_l(int nl, pLista ls_jg);
void cmd_p(int nl, pTabJogos ht_jg);
void cmd_P(int nl, pTabEquipas ht_eq);
void cmd_r(int nl, pLista ls_jg, pTabJogos ht_jg);
void cmd_s(int nl, pTabJogos ht_jg);
void cmd_g(int nl, pTabEquipas ht_eq);

/* funcao auxiliar que aloca memoria dinamicamente para uma string */
char* strdup(const char *s);

/* funcao auxiliar utilizada pelo qsort para ordenar strings lexicograficamente */
int compara(const void *p1, const void *p2);

/* funcao auxiliar que liberta a memoria alocada pelas estruturas de dados*/
void liberta_tudo(pLista ls_jg, pTabEquipas ht_eq, pTabJogos ht_jg);

#endif
