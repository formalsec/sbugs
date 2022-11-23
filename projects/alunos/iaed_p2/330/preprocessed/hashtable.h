#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef HASHTABLE_H
#define HASHTABLE_H
/*Definicao de constantes*/
#define MAX_NAME 1024
#define MAX_TABLE 1501

/*Estrutura de equipas*/
typedef struct equipa{
	char *nome;
	int vitorias;
	struct equipa *proximo;
} Equipa;

/*Estrutura de jogos*/
typedef struct jogo{
	char *nome;
	char *equipa1;
	char *equipa2;
	int pontos1;
	int pontos2;
	struct jogo *anterior;
	struct jogo *proximo;
} Jogo;

/*Estrutura do No das equipas*/
typedef struct no_equipas{
	Equipa *aponta_equipa;
	struct no_equipas *proximo;
}NodeE;

/*Estrutura do No dos jogos*/
typedef struct no_jogos{
	Jogo *aponta_jogo;
	struct no_jogos *anterior;
	struct no_jogos *proximo;
}NodeJ;

/*Estrutura de uma lista de jogos*/
typedef struct cabeca_cauda{
	Jogo *cabeca;
	Jogo *cauda;
}Cabeca_cauda;

/*Estrutura da Hashtable das Equipas*/
typedef struct hashequipas{
	NodeE **cabecas;
	size_t capacidade;
}Hequipas;

/*Estrutura da Hashtable dos jogos*/
typedef struct hashjogos{
	NodeJ **cabecas;
	size_t capacidade;
}Hjogos;

/*Declaracao de prototipos*/
void free_listaE(Equipa *c);
void free_listaJ(Cabeca_cauda *c);
void free_Hequipas(Hequipas *t);
void free_Hjogos(Hjogos *t);
size_t hash(char *v, size_t M);
Hequipas *init_hashE();
Equipa *hash_insertE(Hequipas *h_eq, Equipa *e, char *buffer);
int procuraE(Hequipas *h_eq, char *nome);
Hjogos *init_hashJ();
void hash_insertJ(Hjogos *h_j,Cabeca_cauda *extremos_lista_jogos, char *buffer, char *equipa1_aux, char *equipa2_aux, int pontos1, int pontos2);
int procuraJ(Hjogos *h_j, char *nome);

#endif