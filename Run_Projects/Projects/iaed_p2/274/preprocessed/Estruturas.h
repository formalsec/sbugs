#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#define MAXHASH 2497


/* Estruturas relativas aos jogos */

/* Um jogo e constituido por um nome e duas equipas (ponteiros para char),
 dois resultados relativos as equipas (inteiros) e ponteiros para os jogos
 tanto anterior como seguinte*/
typedef struct jogo_struct {
	char *nome;
	char *equipa_1;
	char *equipa_2;
	int resultado_1;
	int resultado_2;
	struct jogo_struct *anterior, *seguinte;
} jogo;


/* Listas de jogos que contem o ponteiro para o jogo inicial
 e final apontando assim para o inicio e final da lista */
typedef struct lista_jogos { 
	jogo *inicio; 
	jogo *fim; 
} lista;


/* Estrutura da hashtable, contem um ponteiro para
 um jogo e um outro para o seguinte */
typedef struct hashtable_entrada {
    jogo *item;
    struct hashtable_entrada *seguinte;
} hashtable;


/* Extruta que contem um vetor de hashtables */
typedef struct tabela_jogos {
    hashtable *vet[MAXHASH];
} tabela;


/* Estruturas relativas as equipas */

/* Uma equipa e constituida por um nome (ponteiro para char), um
 valor (inteiro) correspondente as vitorias da respetiva
 equipa e ponteiros para tanto a equipa anterior como seguinte*/
typedef struct equipas {
	int vitorias;
	char *nome;
	struct equipas *anterior, *seguinte;
} equipa;


/* Listas de equipas que contem o ponteiro para a equipa inicial
 e final */
typedef struct lista_equipas {
	equipa *inicio;
	equipa *fim;
}lista_das_equipas;


/* Estrutura da hashtable, contem um ponteiro para
 uma equipa e um outro para a seguinte */
typedef struct hashtable_equipas {
	equipa *item;
	struct hashtable_equipas *seguinte;
} hash_equipas;

/* Extruta que contem um vetor de hashtables */
typedef struct tabela_equipas {
	hash_equipas *vet[MAXHASH];
} tabela_e;


#endif
