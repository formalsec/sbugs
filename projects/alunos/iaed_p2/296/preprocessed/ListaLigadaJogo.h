#ifndef LISTALIGADAJOGO
#define LISTALIGADAJOGO
#include "ListaLigadaEquipa.h"

/*
	--------------------- STRUCTS ---------------------
*/

typedef struct jogo {
	Equipa* equipa_1;
	Equipa* equipa_2;
	int score_equipa_1;
	int score_equipa_2;
} Jogo;

typedef struct nojogo {
	struct nojogo* prox, * ant;
	Jogo* jogo;
	char* chave;
} No_Jogo;

typedef struct {
	No_Jogo* inicio, * ultimo;
} Lista_Ligada_Jogo;

/*  --------------------------------------------------- */

/* Cria um jogo. */
Jogo* j_criar(Equipa* equipa_1, Equipa* equipa_2, int score_equipa_1, int score_equipa_2);

/* Verifica qual eh a equipa vencedora de um jogo. */
Equipa* vencedor(Jogo* jogo);

/* Cria nova lista vazia. */
Lista_Ligada_Jogo* ll_criar_jogo();

/* Liberta toda a memoria associada ao no. */
void free_no_jogo(No_Jogo* n);

/* Liberta toda a memoria associada a lista. */
void free_lista_ligada_jogo(Lista_Ligada_Jogo* l);

/* Cria um novo no com a memoria necessaria para guardar um jogo. */
No_Jogo* no_inserir_jogo(Jogo* jogo, char* chave);

/* Adiciona uma equipa como o ultimo elemento da lista. */
void ll_inserir_jogo(Lista_Ligada_Jogo* l, Jogo* jogo, char* chave);

/* Deleta um no da lista ligada. */
void ll_deletar_no(Lista_Ligada_Jogo* l, No_Jogo* n);

/* Deleta um no dado uma chave. */
void ll_deletar_jogo(Lista_Ligada_Jogo* l, char* chave);

#endif 