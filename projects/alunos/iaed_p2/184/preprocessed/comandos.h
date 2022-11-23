#ifndef COMANDOS_H
#define COMANDOS_H
#include "jogos.h"
#include "equipas.h"
#include "auxiliares.h"


/*O comando 'A' adiciona uma nova equipa.*/
void A(linkE *headEptr, hptr *h1);

/*O comando 'a' adiciona um novo jogo.*/
void a(linkJ *headJptr, linkE headE, hptr *h1);

/*O comando 'p' procura um jogo com um nome dado.*/
void p(linkJ *headJptr, hptr *h1);

/*O comando 'P' procura uma equipa dado um nome.*/
void P(linkE headE, hptr *h1);

/*O comando 'r' apaga um jogo, dado um nome.*/
void r(linkJ *headJptr, hptr *h1, linkE headE);

/*O comando 's' altera o score de um jogo, dado um nome.*/
void s(linkJ *headJptr, hptr *h1, linkE headE);

/*O comando 'l' lista todos os jogos introduzidos.*/
void l(linkJ headJ, hptr *h1);

/*O comando 'g' encontra as equipas que ganharam mais jogos e lista-as 
por ordem lexicografica.*/
void g(linkE headE, hptr *h1);

#endif
