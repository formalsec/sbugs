#include "equipa.h"

typedef struct str_NodeEq{
	struct str_NodeEq* seguinte;
	Equipa equipa;
} NodeEq;

typedef struct str_LstEq{
	NodeEq* head;
	int n_eqs;
} LstEqs;

/* Devolve um ponteiro para uma nova lista de equipas */
LstEqs* novaListaEqs();

/* Devolve um ponteiro para um no que contem a Equipa eq */
NodeEq* novoNodeEq(Equipa eq);

/* Adiciona a Equipa dada ao inicio da lista dada */
void pushEq(Equipa eq, LstEqs* lst);

/* Retira a primeira equipa da lista lst */
void popEq(LstEqs* lst);

/* Devolve um ponteiro para a Equipa com o nome dado na lista dada, caso nao exista devolve NULL */
Equipa* procuraEq(LstEqs* lst, char* nome);

/* Copia os elementos da lista dada para um array, e devolve esse array */
Equipa* copiaLstEq(LstEqs* lst);

/* Liberta a memoria reservada pela lista toda */
void destroiLstEq(LstEqs* lst);
