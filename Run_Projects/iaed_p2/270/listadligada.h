#ifndef DLST_H
#define DLST_H
#include "tabdispercao.h"

/* estrutura que representa as caracteristicas de uma lista.d.ligada */
struct lista{
	struct jogo * primeiro, * ultimo;
};

/* abstracao para a estrutura da lista.d.ligada*/
typedef struct lista* pLista;

/*prototipos das funcoes referentes a lista */
pLista cria_lista();
void liberta_lista(pLista l);
void rm_no(pLista l, pJogo n);
void adiciona_fim(pLista l, pJogo n);

#endif
