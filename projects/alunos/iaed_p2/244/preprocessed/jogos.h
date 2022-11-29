#ifndef JOGOS_H
#define JOGOS_H

#define HASHTABLE_JOGO_TAMANHO 509

typedef struct jogo_estrutura{

	char *nome;
	char *eq1;
	char *eq2;
	int pts_1;
	int pts_2;

} jogo_t;


typedef struct htable_entrada_jogo_estrutura{

	struct htable_entrada_jogo_estrutura *next;
	jogo_t *jogo;

} htable_entrada_jogo_t;


typedef struct lista_ligada_jogos{

	struct lista_ligada_jogos *next;
	jogo_t *jogo;

}lista_intruduzidos_t;


htable_entrada_jogo_t **cria_hashtable_jogo();


void adiciona_jogo_a_hashtable(htable_entrada_jogo_t **ht,lista_intruduzidos_t **cabeca, char *nome, char *eq1, char *eq2, int pt1, int pt2);


jogo_t* encontra_jogo(htable_entrada_jogo_t **ht, char* nome);

void destroi_hashtable_jogo(htable_entrada_jogo_t **ht);


void imprime_lista(lista_intruduzidos_t *entrada, int nl);


void remove_jogo(htable_entrada_jogo_t **ht, char *nome);


void destroi_lista(lista_intruduzidos_t *lista);


void retira_da_lista(lista_intruduzidos_t **lista, char *nome );

#endif