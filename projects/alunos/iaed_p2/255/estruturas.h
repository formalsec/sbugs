#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAMANHO_HASHTABLE_MAX 419

/**************
 * Estruturas *
 **************/

/* EQUIPAS */

typedef struct equipa {
	struct equipa * next;
	char * nome;
	int jogos_ganhos;
} EQUIPA;

/* JOGOS */

typedef struct jogo {
	struct jogo * next;
	char * nome;
	EQUIPA * equipa1;
	EQUIPA * equipa2;
	int score1, score2;
} JOGO;

/* Listas Ligadas */

typedef struct lista {
	struct lista * next;
	JOGO * jogo;
} LISTA;

typedef struct lista_eq {
	struct lista_eq * next;
	EQUIPA * equipa;
} LISTA_EQ;


/*************************
 * Prototipos de funcoes *
 *************************/

/* equipas.c */

int funcao_hash(char *v, int M);
EQUIPA ** ht_equipas_init();
LISTA_EQ * lista_equipas_init();
EQUIPA * cria_equipa(char * nome);
LISTA_EQ ** adiciona_eq_lista(LISTA_EQ ** lista, EQUIPA * equipa);
EQUIPA * procura_equipa_aux(char * nome, EQUIPA ** ht);
void destroi_ht_eq(EQUIPA ** ht_eq);
void destroi_lista_eq(LISTA_EQ ** lista);

/* jogos.c */

JOGO ** ht_jogos_init();
LISTA * lista_jogos_init();
JOGO * cria_jogo(char *nome, char *equipa1, char *equipa2, int score1, int score2, EQUIPA **ht);
LISTA ** adiciona_jg_lista(LISTA ** lista, JOGO * jogo);
JOGO * procura_jogo_aux(char * nome, JOGO ** ht);
void apaga_jg_ht(JOGO ** ht_jg, JOGO * jogo);
void apaga_jg_lista(LISTA ** lista, JOGO * jogo);
void destroi_ht_jg(JOGO ** ht_jg);
void destroi_lista_jg(LISTA ** lista);

/* main.c */

void novo_jogo(int contador_input, EQUIPA ** ht_eq, JOGO ** ht_jg, LISTA ** lista);
void nova_equipa(int contador_input, EQUIPA ** ht, LISTA_EQ ** lista);
void lista_todos_jogos(int contador_input, LISTA * lista);
void procura_jogo(int contador_input, JOGO ** ht_jg);
void procura_equipa(int contador_input, EQUIPA ** ht);
void apaga_jogo(int contador_input, JOGO ** ht_jg, LISTA ** lista);
void altera_score(int contador_input, JOGO ** ht_jg);
void top_equipas(int contador_input, LISTA_EQ ** lista);
void liberta_memoria(EQUIPA ** ht_eq, JOGO ** ht_jg, LISTA ** lista_jg, LISTA_EQ ** lista_eq);

/* Fim */
