#ifndef LISTALIGADAEQUIPA
#define LISTALIGADAEQUIPA

/*
	--------------------- STRUCTS ---------------------
*/

typedef struct equipa {
	char* nome_equipa;
	int vitorias;
} Equipa;

typedef struct noequipa {
	struct noequipa* prox, * ant;
	Equipa* equipa;
	char* chave;
} No_Equipa;

typedef struct {
	No_Equipa* inicio, * ultimo;
} Lista_Ligada_Equipa;

/*  --------------------------------------------------- */

/* Cria uma equipa. */
Equipa* e_criar(char* nome);

/* Cria nova lista vazia. */
Lista_Ligada_Equipa* ll_criar_equipa();

/* Liberta toda a memoria associada ao no. */
void free_no_equipa(No_Equipa* n);

/* Liberta toda a memoria associada a lista. */
void free_lista_ligada_equipa(Lista_Ligada_Equipa* l);

/* Cria um novo no com a memoria necessaria para guardar uma equipa. */
No_Equipa* no_inserir_equipa(Equipa* jogo, char* chave);

/* Adiciona uma equipa como o ultimo elemento da lista. */
void ll_inserir_equipa(Lista_Ligada_Equipa* l, Equipa* equipa, char* chave);

#endif 