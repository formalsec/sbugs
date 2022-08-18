#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "equipas.h"

typedef struct jogo{
    char * nome;
    char * equipa1;
    char * equipa2;
    int pontos1;
    int pontos2;
    struct jogo * next;
}jogo;

typedef struct hashJ{
    jogo ** entradas;
}hashJ;

int tamanhoLista;
jogo * listaL;


jogo * procuraJogo(hashJ * hash, char * nome);
int adicionaJogo(hashJ * tabelaJogos, hashE * tabelaEquipas, char * nome, char * nomeequipa1, char * nomeequipa2, int resultado1, int resultado2);
hashJ * criaHash();
void imprimeLista(int nl);
void removeLista(char * nome);
void removeJogo(hashJ * lolada, hashE * e, char * nome, int nl);
void alterapontos(hashJ * omega, hashE * e, char * nome, int pontos1, int pontos2, int nl);
