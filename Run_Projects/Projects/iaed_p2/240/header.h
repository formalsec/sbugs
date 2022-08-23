#include <stdio.h>
#include <string.h>
#include <stdlib.h>



/**************/
/* Constantes */
/**************/


#define CHARMAX 1024
#define TAMANHO_MAX_HASH 607



/**************/
/* Estruturas */
/**************/


/* estrutura das equipas */

typedef struct estrutura_equipa {
    char * nome_equipa;
    int jogos_ganhos;
} equipa;


/* estrutura do node da hashtable das equipas */

typedef struct node_htable_equipas {
	struct node_htable_equipas *next;
	equipa * equipa;
} node_htable_equipas;


/* estrutura dos jogos */

typedef struct estrutura_jogo {
	char * nome_jogo;
	equipa * equipa1;
	equipa * equipa2;

	int score1;
	int score2;
} jogo;


/* estrutura do node da hashtable dos jogos */

typedef struct node_htable_jogos {
	struct node_htable_jogos *next;
	jogo * jogo;
} node_htable_jogos;


/* estrutura da lista ligada dos jogos */

typedef struct lista_ligada_jogos{
	struct lista_ligada_jogos *next;
	jogo * jogo;
}lista_ligada_jogos;


/* estrutura da lista ligada das equipas */

typedef struct lista_ligada_equipas{
	struct lista_ligada_equipas * next;
	equipa * equipa;
}lista_ligada_equipas;





/**************/
/* Prototipos */
/**************/



/* inicializacoes de estruturas */

int hash(char *v);

node_htable_equipas ** init_hash_equipas();

node_htable_jogos ** init_hash_jogos();

lista_ligada_jogos * init_lista_ligada_j();

lista_ligada_equipas * init_lista_ligada_e();

/* equipas.c */


equipa *cria_equipa(char *nome_equipa);

node_htable_equipas *adiciona_a_lista_equipas(node_htable_equipas *pt_lista, equipa *equipa);

lista_ligada_equipas ** adiciona_a_lista_ligada_e(equipa * equipa_new,
lista_ligada_equipas ** lista_ligada);

void adiciona_equipa(int line_number, node_htable_equipas ** hash_equipas, 
	lista_ligada_equipas ** lista_ligada_e);

node_htable_equipas * encontra_equipa(node_htable_equipas **entrada_hash);

equipa * procura_equipa_aux(char *nome_equipa, node_htable_equipas **entrada_hash);

void procura_equipa(int line_number, node_htable_equipas **entrada_hash);

void lista_melhores_equipas(int line_number, lista_ligada_equipas ** lista_ligada);

void destroi_equipas(node_htable_equipas ** entrada_hash_equipas);



/* jogos.c */


jogo * cria_jogo(char *nome_jogo, char *nome_equipa1, char *nome_equipa2,
	int score1, int score2, node_htable_equipas **entrada_hash_equipas);

node_htable_jogos * adiciona_ao_node_jogos(node_htable_jogos *pt_lista, jogo *jogo_new);

lista_ligada_jogos ** adiciona_a_lista_ligada_j(jogo * jogo_new, 
lista_ligada_jogos ** lista_ligada);

void adiciona_jogo(int NL, node_htable_jogos **entrada_hash_jogos, 
	lista_ligada_jogos ** lista_ligada, node_htable_equipas **entrada_hash_equipas);

void lista_jogos(int NL, lista_ligada_jogos * lista_ligada);

jogo * procura_jogo_aux(char *nome_jogo, node_htable_jogos **entrada_hash);

void procura_jogo(int line_number, node_htable_jogos **entrada_hash);

void apaga_jogo_hashtable(char * nome_jogo, node_htable_jogos ** entrada_hash_jogos);

void apaga_jogo_lista_ligada(char * nome_jogo, lista_ligada_jogos ** lista_ligada);

void apaga_jogo(int NL, node_htable_jogos ** entrada_hash_jogos, 
	lista_ligada_jogos ** lista_ligada);

void altera_score(int line_number,  node_htable_jogos ** entrada_hash_jogos);

void destroi_jogos(node_htable_jogos ** entrada_hash_jogos);


/* fim header.h */
