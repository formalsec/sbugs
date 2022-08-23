#ifndef EQUIPAS_H
#define EQUIPAS_H

/* ---------------------------------------------------- BIBLIOTECAS -------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------------------------------------------------------------------------------------------------------------- */
/* Utilizacao de hashtable com encadeamento externo para organizar as equipas                                          */
/* ------------------------------------------------------------------------------------------------------------------- */

/* ----------------------------------------------------- EQUIPAS ----------------------------------------------------- */

/* --------- ESTRUTURA EQUIPAS -------- */

/* As Equipas sao representadas pelo seu nome e pelo numero de vitorias inicalmente a zero */
struct Equipas 
{
	int vitorias;
	char *equipa;
};

/* ItemE um pontiero para as Equipas */
typedef struct Equipas *ItemE;

/* -------- PROTOTIPOS EQUIPAS -------- */

ItemE novaEquipa(char *equipa, int vitorias); /* aloca memoria e atribui o nome e o numero de vitorias, inicalmente 0 */
void freeEquipa(ItemE a); /* libertar memoria */
void imprimeEquipa(ItemE a); /* imprimir uma determinada equipa */

/* ------------------------------------------------ HASHTABLE EQUIPAS ------------------------------------------------ */

/* ----------- ESTRUTURA NO ----------- */

typedef struct nodeE 
{
	ItemE item;
	struct nodeE *next; 

}*linkE;

/* --- PROTOTIPOS HASHTABLE EQUIPAS --- */

int funcao_hashE(char *v); /* funcao que retorna o inteiro correspondente a key para a hashtable */
void iniciaE(linkE headsE[]); /* inicia a hash */
void inserirE(ItemE item, linkE headsE[]); /* inserir a equipa na hash */
linkE inserir_inicioE(linkE head, ItemE a); /* inserir a equipa no inicio da lista */
ItemE procura_equipa(char *nome, linkE headsE[]); /* devolve a equipa se esta estiver na hash */
ItemE procura_lista_equipa(linkE head, char *nome);/* devolve a equipa se estiver na lista caso contrario devolve NULL */
int numero_vitorias(linkE headsE[]); /* devolve o numero maximo de equipas */
void nome_equipas(int vitorias, int nl, int contadorequipas, linkE headsE[]); /* lista as equipas com mais vitorias */
void sair_hashE(linkE headsE[]); /* liberta a memoria */

/* ----------------------------------------------------- ORDENAR ----------------------------------------------------- */

/* -------- PROTOTIPOS ORDENAR -------- */

int compara(const void *a, const void *b); /* funcao que premite ordenar de acordo com o lexicografismo */

#endif