#ifndef _JOGO_
#define _JOGO_

#include "equipas.h"

/*nova estrutura: jogo*/

typedef struct jogo {
    char * nome;
    pEquipa equipa1;
    pEquipa equipa2;
    int pont1;
    int pont2;
} * pJogo;

/*cria um jogo se existirem as equipas do jogo na lista das equipas*/
pJogo criarJogo(char * nome, char * eq1, char * eq2, int pont1, int pont2, listaEq listaEquipas, int numINP);

/*faz print do jogo no formato NL NOME EQUIPA1 EQUIPA2 PONT1 PONT2*/
void mostrarJogo(pJogo jogo, int numINP);

/*adiciona uma vitoria a equipa do jogo que tem mais golos*/
void adicionaVitoria(pJogo j);

/*retira uma vitoria a equipa do jogo que tem mais golos 
    funcao auxiliar para remover o jogo*/
void retiraVitoria(pJogo j);

/*faz free a estrutura pJogo*/
void libertarJogo(pJogo jogo);

#endif