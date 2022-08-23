#ifndef EQUIPA_H
#define EQUIPA_H

#define HASHTABLE_TAMANHO 509
#define MAX_STRING 1023

typedef struct equipa_estrutura{

	char *nome;
	int numero_de_jogos;

} equipa_t;



typedef struct htable_entrada_estrutura{

	struct htable_entrada_estrutura *next;
	equipa_t *equipa;

} htable_entrada_t;



typedef struct lista_ligada_equipas{

	struct lista_ligada_equipas *next;
	equipa_t *equipa;

}lista_equipas_intruduzidas_t;


htable_entrada_t **cria_hashtable();


void adiciona_equipa_a_hashtable(htable_entrada_t **ht, lista_equipas_intruduzidas_t **cabeca, char *nome);


equipa_t* encontra_equipa(htable_entrada_t **ht, char* nome);


void destroi_hashtable(htable_entrada_t **ht);


int max_jogos_ganhos(lista_equipas_intruduzidas_t *lista);


void imprime_melhores_equipas(lista_equipas_intruduzidas_t *lista, int n, int nl);


void destroi_lista_equipas(lista_equipas_intruduzidas_t *lista);

#endif