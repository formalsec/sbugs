#ifndef _EQUIPAS_
#define _EQUIPAS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*nova estrutura : struct equipa */
typedef struct equipa {
    char * nomeEquipa;
    int numVitorias;
} * pEquipa;

/*nova estrutura: struct noEquipa*/
typedef struct noEquipa {
    pEquipa ptrEquipa;
    struct noEquipa * proximo;
} * listaEq;

/*criar nova equipa dado um nome (uma nova equipa comeca com 0 vitorias*/
pEquipa criarEquipa(char * nomeEquipa);

/*free de uma equipa*/
void libertarEquipa(pEquipa equipaFree);

/*imprimir equipa no formato NOME_EQUIPA NUM_VITORIAS*/
void mostrarEquipa(pEquipa equipa, int numINP);

/*cria uma lista de equipas inicialmente vazia*/
listaEq criarListaEquipas();

/*adicionar equipa por ordem alfabetica*/
listaEq adicionarNovaEquipa(pEquipa novaEquipa, listaEq listaEquipas, int numINP);

/*procurar uma equipa dado um nome*/
pEquipa procurarEquipa(listaEq listaEquipas, char * nome);

/*retorna o valor maximo de vitorias*/
int maxVitorias(listaEq listaEquipas);

/*lista as equipas com o maior numero de vitorias*/
void melhoresEquipas(listaEq listaEquipas, int numINP);

/*free em cada no da lista das equipas*/
void libertarListaEquipas(listaEq listaEquipas);


#endif