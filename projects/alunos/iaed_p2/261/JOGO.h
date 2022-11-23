#ifndef JOGO_H
#define JOGO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HASHTABLE.h"  /* Ficheiro que contem as funcoes que gerem a hashtable que contem as equipas */
			         
#define MAX	1024 

list* mk_list();

void freeLista(list* l);

jogo* encontrarJogo(list* l, char buffer[MAX]);

void merge(int tab_final[], int start, int mid, int end, char* tab_equipa[EQUIPAHASHMAX]);

void mergeSort(int tab_final[EQUIPAHASHMAX], int start, int end, char* tab_equipa[EQUIPAHASHMAX]);

list* adicionaJogo(list* l, equipaHash** equipaTable, char* buffer, int n);

void listaJogos(list* l, int n);

void procuraJogo(list* l, char buffer[MAX], int n);

list* apagarJogo(list* l, equipaHash** equipaTable, char buffer[MAX], int n);

list* alteraResultado(list* l, equipaHash** equipaTable, char buffer[MAX], int n);

void adicionaEquipa(equipaHash** equipaTable, char buffer[MAX], int n);

void procuraEquipa(equipaHash** equipaTable, char buffer[MAX], int n);

void melhoresEquipas(equipaHash** equipaTable, int n);

#endif