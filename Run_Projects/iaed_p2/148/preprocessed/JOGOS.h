#ifndef JOGOS_H
#define JOGOS_H

/* ---------------------------------------------------- BIBLIOTECAS -------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------------------------------------------------- */
/* Utilizacao de hashtable com encadeamento externo e uma lista duplamente ligada para organizar os jogos              */
/* ------------------------------------------------------------------------------------------------------------------- */

/* ------------------------------------------------------ JOGOS ------------------------------------------------------ */

/* ---------- ESTRUTURA JOGOS --------- */

/* Os Jogos sao representadas pelo seu nome, por duas equipas e por um resultado, par de inteiros */
struct Jogo 
{
	int score1, score2;
	char *equipa1, *equipa2;
	char *nome;
};

/* ItemJ um pontiero para o Jogo */
typedef struct Jogo *ItemJ;

/* --------- PROTOTIPOS JOGOS --------- */

ItemJ novoJogo(char *nome, char *equipa1, char *equipa2, int score1, int score2); /* aloca memoria e atribui o nome, */
/* as equipas e o resultado */
void freeJogo(ItemJ a); /* libertar memoria */
void imprimeJogo(int nl, ItemJ a); /* imprimir um determinado jogo */

/* ------------------------------------------------- HASHTABLE JOGOS ------------------------------------------------- */

/* ------------ ESTRUTURA NO ----------- */

typedef struct nodeJ 
{
	ItemJ item;
	struct nodeJ *next; 
}*linkJ;

/* ----- PROTOTIPOS HASHTABLE JOGOS ---- */

int funcao_hashJ(char *v); /* funcao que retorna o inteiro correspondente a key para a hashtable */
int chave(char *nome); /* funcao que devolve o inteiro correspondente a key */
void iniciaJ(linkJ headsJ[]); /* inicia a hash */
void inserirJ(ItemJ item, linkJ headsJ[]); /* inserir o jogo na hash */
linkJ inserir_inicioJ(linkJ head, ItemJ a); /* inserir o jogo no inicio da lista */
ItemJ procura_nome(char *nome, linkJ headsJ[]); /* devolve o jogo se este estiver na hash */
ItemJ procura_lista_nome(linkJ head, char *nome); /* devolve o jogo se estiver na lista caso contrario devolve NULL */

/* --------------------------------------------------- LISTA JOGOS --------------------------------------------------- */

/* --------- ESTRUTURA NO LISTA -------- */

typedef struct nodeL *linkL;

struct nodeL 
{
	ItemJ item;
	linkL next;
	linkL prev;
};

/* ---------- ESTRUTURA LISTA ---------- */

typedef struct{
	linkL primeiro;
	linkL ultimo;
}lista;

/* ------- PROTOTIPOS LISTA JOGOS ------ */

lista *cria_lista(); /* criar e inicalizar a lista */
void inserir_fim(lista *l, ItemJ jogo); /* inserir o jogo no fim da lista */
void imprime_jogos(int nl, lista *l); /* imipre todos os jogos presentes na lista */

/* ---------------------------------------------------- APAGA JOGO --------------------------------------------------- */

void apaga_jogo(linkJ headsJ[], lista *l, char *nome, int i); /* a paga o jogo com um determinado nome */
void sair_jogos(lista *l, linkJ headsJ[]); /* libertar a memoria */

#endif



