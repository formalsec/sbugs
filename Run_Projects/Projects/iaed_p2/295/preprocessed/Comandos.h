#ifndef Comandos
#define Comandos
#include "Estruturas.h"

/* Daqui para baixo encontram se listados os prototipos de todos os comandos */

void comando_A(int nl, lista_equipas *a, lista_equipas_aux *b);

void comando_a(int nl, lista_equipas *a, lista_jogos *b, lista_jogos_aux *c, lista_equipas *g);

void comando_P(int nl, lista_equipas *a);

void comando_p(int nl, lista_jogos *a);

void comando_r(int nl, lista_jogos *a, lista_equipas *b);

void comando_s(int nl, lista_jogos *a, lista_equipas *c);

void comando_l(int nl, lista_jogos *a, lista_jogos_aux *b);

void comando_g(int nl, lista_equipas_aux *b);

void direciona(char e, int nl, lista_equipas *a, lista_equipas_aux *b, lista_jogos *c, lista_jogos_aux *d);

#endif