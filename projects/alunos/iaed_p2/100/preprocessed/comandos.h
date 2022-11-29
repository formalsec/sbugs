#ifndef _COMANDOS_
#define _COMANDOS_ 

#include "jogos.h"
#include "equipas.h"

/* Declaracao de prototipos das funcoes comandos e auxiliares */

void hash_init_jogo(link* heads_jogos);
void hash_init_equipa(link_e* heads_equipas);

char* vencedor_f(char* equipa1, char* equipa2,  unsigned int score1, unsigned int score2);
int compare(const void *a, const void *b);

void a(unsigned long contador, link *heads_jogos, link_e *heads_equipas, lst_ptr lista);
void l(unsigned long contador, lst_ptr lista);
void p(unsigned long contador, link *heads_jogos);
void r(unsigned long contador, link *heads_jogos, link_e *heads_equipas, lst_ptr lista);
void s(unsigned long contador, link *heads_jogos, link_e *heads_equipas);
void A(unsigned long contador, link_e *heads_equipas);
void P(unsigned long contador, link_e *heads_equipas);
void g(unsigned long contador, link_e *heads_equipas);



#endif