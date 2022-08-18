#ifndef PROCESSOS_H
#define PROCESSOS_H

#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#include "equipa.h"


/* Adiciona um novo jogo */
void adicionaNovoJogo(pJogo *tabJ, pEquipa *tabE, int maxJ, int maxE, int nComandos, DLinkedList list);
/* Adiciona uma nova equipa */
void adicionaNovaEquipa(pEquipa *tab, int max, int nComandos);
/* Lista todos os jogos pela ordem em que foram introduzidos */
void listaJogosPelaOrdemIntroduzidos(DLinkedList list, int nComandos);
/* Procura um jogo */
void procuraUmJogo(pJogo *tabJ, int max, int nComandos);
/* Procura uma equipa */
void procuraUmaEquipa(pEquipa *tab, int max, int nComandos);
/* Apaga um jogo */
void apagaUmJogo(pJogo *tabJ, pEquipa *tabE, int maxJ, int maxE, DLinkedList list, int nComandos);
/* Altera a pontuacao (score) de um jogo */
void alteraScoreDeUmJogo(pJogo *tabJ, pEquipa *tabE, int maxJ, int maxE,  int nComandos);
/* Encontra as equipas que venceram mais jogos*/
void encontraAsEquipasVencedores(pEquipa *tab, int max, int nComandos);
/* liberta memoria alugada */
void sair(pEquipa *tabE, pJogo *tabJ, DLinkedList listJ,int maxE, int maxJ);
/* liberta lista*/
void destoryList(DLinkedList list);
/* liberta HashTable do jogo*/
void destroyHashJogo(pJogo *tabJ, int maxJ);
/* liberta HashTable da Equipa*/
void destroyHashEquipa(pEquipa *tabE, int maxE);

#endif
